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
#ifndef _SPLASH_SCREEN_H_
#define _SPLASH_SCREEN_H_

#include "Scene.hpp"
#include "Sprite.hpp"
#include "SfxSound.hpp"

class SplashScreen : public Scene
{
public:

	enum SPLASH_STATE 
	{ 
		OPENING, 
		STAY, 
		ENDING 
	};

private:

	int m_splashOpacity, m_scTimer;
	bool m_sfxSplash;

	Sprite * m_splash;
	SfxSound * m_SFX;
	SPLASH_STATE m_splashOpeningState;

public:

	SplashScreen(Settings * settings);						// Constructor
	~SplashScreen();

	void Start(SDL_Helper * helper) override;
	void Draw() override;
	void CheckInputs(u64 kDown, u64 kHeld, u64 kUp) override;
	void Update() override;
	void NextScene() override;
};

#endif