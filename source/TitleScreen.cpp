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

#include "TitleScreen.hpp"
#include "SceneManager.hpp"
#include "Filepaths.h"
#include "Settings.hpp"
#include "Colors.h"

TitleScreen::TitleScreen(Settings * _settings) : Scene(_settings)
{
	this->m_settings = _settings;
	this->m_changeScene = false;
}

TitleScreen::~TitleScreen()
{
	this->m_music->End(this->m_helper);
	delete(this->m_music);

	this->m_buttonTapSFX->End(this->m_helper);
	delete(this->m_buttonTapSFX);

	this->m_playButton->End(this->m_helper);
	delete(this-> m_playButton);

	this->m_background->End(this->m_helper);
	delete(this->m_background);

	this->m_creatorText->End(this->m_helper);
	delete(this->m_creatorText);
}

void TitleScreen::Start(SDL_Helper * helper)
{
	this->m_helper = helper;
	this->m_background = new Sprite(0, 0, helper, IMG_BACKGROUND_TITLE, 1, 1, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, 0, 0, false, false, 1);
	
	this->m_soundToggle = new Toggle(!this->m_muted, 30, 30, this->m_helper, IMG_TOGGLE_SOUND, IMG_TOGGLE_NO_SOUND, true, false, 1, 1, 125, 116, false, 0, 0);

	this->m_creatorText = new Text(helper, "Manurocker95 (C) 2019", 465, 670, 35, true, FONT_NORMAL, C_BLACK);

	this->m_playButton = new Button(520, 380, helper, IMG_BTN_PLAY, IMG_BTN_PLAY_NON_INTERACTABLE, IMG_BTN_PLAY_PRESSED,true,false,1,1, 208, 116, false, 0, 0);

	this->m_buttonTapSFX = new SfxSound(this->m_helper, SND_SFX_TAP, false, 2);
	this->m_music = new MusicSound(this->m_helper, SND_BGM_TITLE, true, 1);
	this->m_music->Play(this->m_helper);

	if (this->m_settings->m_muted)
		this->m_helper->SDL_PauseMusic();
}

void TitleScreen::Draw()
{
	// BG
	this->m_background->Draw(this->m_helper);

	// Draw Button
	this->m_playButton->Draw(this->m_helper);

	this->m_soundToggle->Draw(this->m_helper);

	this->m_creatorText->Draw(this->m_helper);	
}

void TitleScreen::Update()
{
	if (this->m_changeScene)
		NextScene();
}

void TitleScreen::CheckInputs(u64 kDown, u64 kHeld, u64 kUp)
{
	if (kHeld & KEY_TOUCH)
	{
		u32 j;
		hidTouchRead(&touch, j);
		
		if (this->m_playButton->IsPressed(&touch))
		{
			//
		}
		
	}
	else if (kUp & KEY_TOUCH)
	{
		if (this->m_playButton->GetPressed())
		{
			if (!this->m_settings->m_muted)
				this->m_buttonTapSFX->Play(this->m_helper);

			this->m_changeScene = true;
			return;
		}

		this->m_soundToggle->CheckIsPressed(&touch);

		if (this->m_soundToggle->ValueChanged())
		{
			this->m_soundToggle->ResetChangeValue();
			Mute();

			if (!this->m_settings->m_muted)
				this->m_buttonTapSFX->Play(this->m_helper);

			return;
		}
	}

	if (kDown & KEY_A)
	{
		this->m_changeScene = true;

		if (!this->m_settings->m_muted)
			this->m_buttonTapSFX->Play(this->m_helper);

		return;
	}
	
	if (kDown & KEY_PLUS)
	{
		SceneManager::Instance()->ExitGame();
	}
}

// * We go to the next scene = GameScreen
void TitleScreen::NextScene()
{
	SceneManager::Instance()->LoadScene(SceneManager::GAME);
}

