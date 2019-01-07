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
#ifndef _MUSIC_SOUND_HPP_
#define _MUSIC_SOUND_HPP_

#include "Sound.hpp"

class MusicSound : public Sound
{
	Mix_Music * m_music;

public:
	MusicSound(SDL_Helper * _helper, char * _file, bool _inLoop, int _channel);
	~MusicSound();

	Mix_Music * GetAudio();
	void SetAudio(Mix_Music * _audio);
	void LoadAudio(SDL_Helper * _helper, char * _file) override;

	void End(SDL_Helper * _helper) override;

	void Play(SDL_Helper * _helper) override;
	void Resume(SDL_Helper * _helper) override;
	void Pause(SDL_Helper * _helper) override;
};

#endif