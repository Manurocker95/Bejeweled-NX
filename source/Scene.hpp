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
#ifndef _SCENE_HPP_
#define _SCENE_HPP_
		
#include "SDL_Helper.hpp"
#include "Settings.hpp"
#include <switch.h>
#include <string>

// Base Class.
class Scene
{

protected:
	SDL_Helper * m_helper;
	Settings * m_settings;
	touchPosition touch;
	bool m_changeScene;
	bool m_muted;
	bool m_debugMode;
	bool m_paused;
public:
	Scene(Settings * _settings)											 // Constructor
	{ 
		this->m_settings = _settings; 
		this->m_debugMode = _settings->m_debugMode;
		this->m_muted = _settings->m_muted;
		this->m_paused = _settings->m_paused;
		this->m_changeScene = false;

	};		

	~Scene() { };														// Destructor
	virtual void Start(SDL_Helper * m_helper) {};						// initialize
	virtual void Draw() { };											// Draw
	virtual void CheckInputs(u64 kDown, u64 kHeld, u64 kUp) {};			// CheckInput
	virtual void Update() {};											// Update
	virtual void NextScene() {};										// NextScene
	virtual void Mute()
	{
		this->m_settings->ToggleMute();
		this->m_muted = this->m_settings->m_muted;

		if (this->m_muted)
		{
			this->m_helper->SDL_PauseMusic();
		}
		else
		{
			this->m_helper->SDL_ResumeMusic();
		}
	}
};

#endif