/* This file is part of Manurocker95's Template!

this is made for my tutorial: https://gbatemp.net/threads/tutorial-setting-up-visual-studio-2017-environment-for-nintendo-switch-homebrew-development.525977/#post-8439059

Copyright (C) 2018/2019 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/

#include "GameScreen.hpp"
#include "SceneManager.hpp"
#include "Filepaths.h"
#include "Colors.h"
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>
// swap algorithm example (C++98)
#include <iostream>     // std::cout


GameScreen::GameScreen(Settings * _settings) : Scene(_settings)
{
	this->m_settings = _settings;
	this->m_changeScene = false;
	this->m_tokenSize = _settings->m_tokenSize;
	this->m_score = 0;
	srand(time(NULL));
	
}

GameScreen::~GameScreen()
{
	this->m_music->End(this->m_helper);
	delete(this->m_music);

	this->m_buttonTapSFX->End(this->m_helper);
	delete(this->m_buttonTapSFX);

	this->m_background->End(this->m_helper);
	delete(this->m_background);

	this->m_scoreText->End(this->m_helper);
	delete(this->m_scoreText);	
	
	this->m_debugText->End(this->m_helper);
	delete(this->m_debugText);

	this->m_helper->SDL_DestroyTexture(this->m_gemTexture);
}

void GameScreen::Start(SDL_Helper * helper)
{
	
	this->m_helper = helper;

	this->m_helper->SDL_LoadImage(&this->m_gemTexture, IMG_GEMS);

	this->m_background = new Sprite(0, 0, helper, IMG_BACKGROUND, 1, 1, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, 0, 0, false, false, 1);
	this->m_cursor = new Sprite(0, 0, helper, IMG_CURSOR, 1, 1, 48, 52, 0, 0, false, false, 1);

	this->m_scoreText = new Text(helper, std::string(SceneManager::Instance()->GetText("scoreText")) + std::to_string(this->m_score), 1000, 30, 30, true, FONT_NORMAL, C_WHITE);
	this->m_debugText = new Text(helper, "DEBUG TEXT", 30, 630, 15, true, FONT_NORMAL, C_WHITE);


	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			this->m_grid[i][j].kind = rand() % 3;
			this->m_grid[i][j].col = j;
			this->m_grid[i][j].row = i;
			this->m_grid[i][j].x = j * this->m_tokenSize;
			this->m_grid[i][j].y = i * this->m_tokenSize;
		}
	}

	this->m_buttonTapSFX = new SfxSound(this->m_helper, SND_SFX_TAP, false, 2);
	this->m_pointSFX = new SfxSound(this->m_helper, SND_SFX_POINT, false, 2);
	this->m_music = new MusicSound(this->m_helper, SND_BGM_GAME, true, 1);
	this->m_music->Play(this->m_helper);
	
	if (this->m_settings->m_muted)
		this->m_helper->SDL_PauseMusic();

}

void GameScreen::Draw()
{
	this->m_background->Draw(this->m_helper);

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			piece p = this->m_grid[i][j];
			p.x += this->m_offsetX - this->m_tokenSize;
			p.y += this->m_offsetY - this->m_tokenSize;
			this->m_helper->SDL_DrawImageRectOpacity(this->m_gemTexture, p.x, p.y, p.kind * 49, 0, 49, 49, p.alpha);
		}
	}

	this->m_cursor->Draw(this->m_helper);
	this->m_scoreText->Draw(this->m_helper);

	if (this->m_debugMode)
		this->m_debugText->Draw(this->m_helper);
}

void GameScreen::Update()
{	
	if (this->m_changeScene)
	{
		NextScene();
	}
	else
	{
		//Match finding
		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
			{
				if (this->m_grid[i][j].kind == this->m_grid[i + 1][j].kind)
				{
					if (this->m_grid[i][j].kind == this->m_grid[i - 1][j].kind)
					{
						for (int n = -1; n <= 1; n++)
						{
							this->m_grid[i + n][j].match++;
						}
					}					
				}
				
				if (this->m_grid[i][j].kind == this->m_grid[i][j + 1].kind)
				{
					if (this->m_grid[i][j].kind == this->m_grid[i][j - 1].kind)
					{
						for (int n = -1; n <= 1; n++)
						{
							this->m_grid[i][j + n].match++;
						}
					}
				}					
			}
		}


		//Moving animation
		this->m_isMoving = false;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				piece &p = this->m_grid[i][j];
				int dx, dy;
				for (int n = 0; n<4; n++)   // 4 - speed
				{
					dx = p.x - p.col*this->m_tokenSize;
					dy = p.y - p.row*this->m_tokenSize;
					if (dx) p.x -= dx / abs(dx);
					if (dy) p.y -= dy / abs(dy);
				}
				if (dx || dy) 
					this->m_isMoving = 1;
			}

		//Deleting amimation
		if (!this->m_isMoving)
		{
			for (int i = 1; i <= 8; i++)
			{
				for (int j = 1; j <= 8; j++)
				{
					if (this->m_grid[i][j].match)
					{
						if (this->m_grid[i][j].alpha > 10)
						{ 
							this->m_grid[i][j].alpha -= 10;
							this->m_isMoving = true;
						}
						else
						{
							AddScore();
						}
					}
				}
			}
				
		}
			
		//Get score
		int score = 0;
		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
			{
				score += this->m_grid[i][j].match;
			}
		}

		//Second swap if no match
		if (this->m_isSwap && !this->m_isMoving)
		{
			if (score == 0)
				SwapPieces(this->m_grid[this->m_y0][this->m_x0], this->m_grid[this->m_y][this->m_x]);	

			this->m_isSwap = false;
		}

		//Update grid
		if (!this->m_isMoving)
		{
			for (int i = 8; i > 0; i--)
			{
				for (int j = 1; j <= 8; j++)
				{
					if (this->m_grid[i][j].match)
					{
						for (int n = i; n > 0; n--)
						{
							if (!this->m_grid[n][j].match)
							{
								SwapPieces(this->m_grid[n][j], this->m_grid[i][j]);
								break;
							}
						}
					}
				}
			}
				
			for (int j = 1; j <= 8; j++)
			{
				for (int i = 8, n = 0; i > 0; i--)
				{
					if (this->m_grid[i][j].match)
					{
						this->m_grid[i][j].kind = rand() % 7;
						this->m_grid[i][j].y = -this->m_tokenSize * n++;
						this->m_grid[i][j].match = 0;
						this->m_grid[i][j].alpha = 255;
					}
				}
			}
		}
	}	
}

void GameScreen::CheckInputs(u64 kDown, u64 kHeld, u64 kUp)
{
	if (kDown & KEY_TOUCH)
	{
		u32 i;
		hidTouchRead(&touch, i);

		this->m_posX = touch.px - this->m_offsetX;
		this->m_posY = touch.py - this->m_offsetY;

		if (!this->m_isSwap && !this->m_isMoving) 
			this->m_click++;
	}

	// mouse click
	if (this->m_click == 1)
	{
		this->m_x0 = this->m_posX / this->m_tokenSize + 1;
		this->m_y0 = this->m_posY / this->m_tokenSize + 1;
		this->m_cursor->SetActive(true);
		this->m_cursor->SetX(this->m_grid[this->m_y0][this->m_x0].x-8);
		this->m_cursor->SetY(this->m_grid[this->m_y0][this->m_x0].y-28);
	}
	else if (this->m_click == 2)
	{
		this->m_x = this->m_posX / this->m_tokenSize + 1;
		this->m_y = this->m_posY / this->m_tokenSize + 1;
		if (abs(this->m_x - this->m_x0) + abs(this->m_y - this->m_y0) == 1)
		{
			SwapPieces(this->m_grid[this->m_y0][this->m_x0], this->m_grid[this->m_y][this->m_x]);
			this->m_isSwap = true;
			this->m_click = 0;
			this->m_cursor->SetActive(false);
		}
		else
		{
			this->m_click = 1;
		}
	}

	if (kDown & KEY_R && kDown & KEY_L)
	{
		this->m_debugMode = !this->m_debugMode;
	}

	if (kDown & KEY_PLUS)
	{
		this->m_changeScene = true;
	}

	if (kDown & KEY_MINUS)
	{
		AddScore();
	}
}

void GameScreen::AddScore()
{
	++this->m_score;
	this->m_scoreText->SetText(std::string(SceneManager::Instance()->GetText("scoreText")) + std::to_string(this->m_score));

	if (!this->m_muted)
		m_pointSFX->Play(this->m_helper);
}

// * We go to the next scene = GameScreen
void GameScreen::NextScene()
{
	this->m_settings->m_debugMode = this->m_debugMode;
	SceneManager::Instance()->SaveData(this->m_score);
	SceneManager::Instance()->LoadScene(SceneManager::TITLE);
}

void GameScreen::SwapPieces(piece p1, piece p2)
{
	std::swap(p1.col, p2.col);
	std::swap(p1.row, p2.row);

	this->m_grid[p1.row][p1.col] = p1;
	this->m_grid[p2.row][p2.col] = p2;
}
