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

#include "SceneManager.hpp"
#include "SplashScreen.hpp"
#include "TitleScreen.hpp"
#include "GameScreen.hpp"
#include "LoadingScreen.hpp"
#include "IntroScreen.hpp"
#include "Colors.h"
#include "Filepaths.h"

SceneManager * SceneManager::instance = NULL;

SceneManager * SceneManager::Instance()
{
	if (instance == NULL)
		instance = new SceneManager;

	return instance;
}

// Scene Manager Data initialization
void SceneManager::Start(SDL_Helper * helper)
{
	this->m_saveManager = new SaveManager();
	this->m_LocalizationManager = new LocalizationManager();
	this->m_helper = helper;
	this->m_out = (this->m_LocalizationManager->Initialized()) ? false : true;
	ReadData();
}

// We read the data from our .sav
void SceneManager::ReadData()
{
	this->m_settings = this->m_saveManager->GetSettings();
	this->m_actualScene = new SplashScreen(this->m_settings);
	this->m_actualScene->Start(this->m_helper);
}

// We set the new scene
void SceneManager::SetActualScene(SCENES _scene)
{
	// We delete the pointer of the actual scene
	delete (this->m_actualScene);

	// We set the new scene
	switch (_scene)
	{
	case SPLASH:
		this->m_actualScene = new SplashScreen(this->m_settings);
		break;
	case INTRO:
		this->m_actualScene = new IntroScreen(this->m_settings);
		break;
	case TITLE:
		this->m_actualScene = new TitleScreen(this->m_settings);
		break;
	case GAME:
		m_actualScene = new GameScreen(this->m_settings);
		break;
	}

	this->m_actualScene->Start(m_helper);
}

void SceneManager::LoadScene(SCENES _scene, int _delayTime)
{
	if (_delayTime == -1)
		_delayTime = this->m_settings->m_loadingDelay;

	// We delete the pointer of the actual scene
	if (this->m_actualScene != NULL)
		delete (this->m_actualScene);

	this->m_actualScene = new LoadingScreen(_scene, this->m_settings, _delayTime);
	this->m_actualScene->Start(m_helper);
}

// We call every function needed: Check User inputs, Update the game, and of course, paint everything
void SceneManager::Update()
{
	this->CheckInputs();
	this->m_actualScene->Update();
	this->Draw();
}

// We check if we are exiting
bool SceneManager::IsOut()
{
	return this->m_out;
}

// Simple exiting
void SceneManager::ExitGame(int _score)
{
	SaveData(_score);
	this->m_out = true;
}

void SceneManager::Draw()
{
	this->m_actualScene->Draw();
}
void SceneManager::CheckInputs()
{
	// Scan all the inputs. This should be done once for each frame
	hidScanInput();

	// hidKeysDown returns information about which buttons have been
	// just pressed in this frame compared to the previous one
	u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
	// hidKeysHeld returns information about which buttons are being held
	u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

	u64 kUp = hidKeysUp(CONTROLLER_P1_AUTO);

	this->m_actualScene->CheckInputs(kDown, kHeld, kUp);
}

void SceneManager::Exit()
{
	delete(this->m_actualScene);
	delete(this->m_LocalizationManager);
	delete(this->m_saveManager);
	//delete(instance);
}

SDL_Helper * SceneManager::GetHelper()
{
	return this->m_helper;
}

void SceneManager::SaveData(int _value)
{
	this->m_saveManager->Save(_value);
}

const char * SceneManager::GetText(char * _key)
{
	return this->m_LocalizationManager->GetText(_key);
}