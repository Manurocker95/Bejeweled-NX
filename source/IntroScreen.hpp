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
#pragma once
#ifndef _INTRO_SCREEN_H_
#define _INTRO_SCREEN_H_

#include "Scene.hpp"
#include "Sprite.hpp"
#include "SfxSound.hpp"

class IntroScreen : public Scene
{

private:

	bool m_goToGame;

	Sprite * m_introBG;
	SfxSound * m_SFX;

public:

	IntroScreen(Settings * settings);						// Constructor
	~IntroScreen();

	void Start(SDL_Helper * helper) override;
	void Draw() override;
	void CheckInputs(u64 kDown, u64 kHeld, u64 kUp) override;
	void Update() override;
	void NextScene() override;
};

#endif