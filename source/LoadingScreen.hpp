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

#pragma once
#ifndef _LOADING_SCREEN_HPP_
#define _LOADING_SCREEN_HPP_

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "Text.hpp"

class LoadingScreen : public Scene
{
private:
	SDL_Texture * m_loadingBG;
	SDL_Texture * m_animatedImg;
	
	Text * m_loadingText;

	SceneManager::SCENES m_nextScene;

private:
	unsigned int m_lastTime;
	unsigned int m_currentTime;
	bool m_loading;
	int m_delay;
public:

	LoadingScreen(SceneManager::SCENES  _nextScene, Settings * settings, int _delayTime);						// Constructor
	~LoadingScreen();																							// Destructor
	void Start(SDL_Helper * helper) override;																	// initialize
	void Draw() override;																						// Draw
	void CheckInputs(u64 kDown, u64 kHeld, u64 kUp) override;													// CheckInput
	void Update() override;																						// Update
	void NextScene() override;
};

#endif