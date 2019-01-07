/* This file is part of T-Rekt NX!

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


#include "SplashScreen.hpp"
#include "SceneManager.hpp"
#include "Colors.h"
#include "Filepaths.h"

// * Constructor 
SplashScreen::SplashScreen(Settings * settings) : Scene(settings)
{
	this->m_splashOpeningState = OPENING;
	this->m_scTimer = 0;
	this->m_splashOpacity = 0;
	this->m_sfxSplash = false;
}

// * Destructor
SplashScreen::~SplashScreen()
{
	this->m_splash->End(this->m_helper);
	delete(this->m_splash);

	this->m_SFX->End(this->m_helper);
	delete(this->m_SFX);
}

// * Start - We initialize the variables
void SplashScreen::Start(SDL_Helper * helper)
{
	this->m_helper = helper;
	this->m_splash = new Sprite(0, 0, helper, IMG_SPLASHSCREEN, 1, 1, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, 0, 0, false, false, 1, true);
	this->m_SFX = new SfxSound(this->m_helper, SND_SFX_SPLASH, false, 2);
}

// * Draw the images every frame
void SplashScreen::Draw()
{
	this->m_splash->Draw(this->m_helper);
}

// * Update game stuff (SplashScreen opacity)
void SplashScreen::Update()
{
	switch (this->m_splashOpeningState)
	{
	case OPENING:

		this->m_splashOpacity += 3;

		if (this->m_splashOpacity >= 255)
		{
			this->m_splashOpacity = 255;
			this->m_splashOpeningState = STAY;

			if (!this->m_sfxSplash)
			{
				this->m_sfxSplash = true;

				if (!this->m_settings->m_muted)
					this->m_SFX->Play(m_helper);
			}
		}

		break;
	case STAY:

		this->m_scTimer += 5;

		if (this->m_scTimer >= 300)
		{
			this->m_splashOpeningState = ENDING;
		}

		break;
	case ENDING:

		this->m_splashOpacity -= 3;

		if (this->m_splashOpacity <= 0)
		{
			this->m_changeScene = true;
		}
		break;
	}

	this->m_splash->SetOpacity(this->m_splashOpacity);

	if (this->m_changeScene)
	{
		NextScene();
	}

}

// * We go to the next scene = TitleScreen
void SplashScreen::NextScene()
{
	SceneManager::Instance()->LoadScene(SceneManager::TITLE);
}

// * We check the inputs
void SplashScreen::CheckInputs(u64 kDown, u64 kHeld, u64 kUp)
{
	
	if (kDown & KEY_A || kDown & KEY_TOUCH)
	{
		this->m_changeScene = true;
	}
	
}