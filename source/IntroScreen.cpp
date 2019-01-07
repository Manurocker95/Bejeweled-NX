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

#include "IntroScreen.hpp"
#include "SceneManager.hpp"
#include "Colors.h"
#include "Filepaths.h"

// * Constructor 
IntroScreen::IntroScreen(Settings * settings) : Scene(settings)
{
	this->m_goToGame = false;
}

// * Destructor
IntroScreen::~IntroScreen()
{
	this->m_introBG->End(this->m_helper);
	delete(this->m_introBG);

	this->m_SFX->End(this->m_helper);
	delete(this->m_SFX);
}

// * Start - We initialize the variables
void IntroScreen::Start(SDL_Helper * helper)
{
	this->m_helper = helper;
	this->m_introBG = new Sprite(0, 0, helper, IMG_CINEMATIC_INTRO, 4, 4, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, 0, 0, true, true, 1);
	this->m_introBG->SetInLoop(false);
	this->m_SFX = new SfxSound(this->m_helper, SND_SFX_SPLASH, false, 2);
}

// * Draw the images every frame
void IntroScreen::Draw()
{
	this->m_introBG->Draw(this->m_helper);
}

// * Update game stuff (SplashScreen opacity)
void IntroScreen::Update()
{
	this->m_introBG->Update();

	if (!this->m_introBG->IsAnimated())
		this->m_changeScene = true;

	if (this->m_changeScene)
	{
		NextScene();
	}

}

// * We go to the next scene = TitleScreen
void IntroScreen::NextScene()
{
	//SceneManager::Instance()->SetActualScene(SceneManager::GAME);
	SceneManager::Instance()->LoadScene(SceneManager::GAME, 1);
}

// * We check the inputs
void IntroScreen::CheckInputs(u64 kDown, u64 kHeld, u64 kUp)
{

	if (kDown & KEY_A || kDown & KEY_TOUCH)
	{
		if (this->m_muted)
			this->m_SFX->Play(this->m_helper);

		this->m_changeScene = true;
	}

}