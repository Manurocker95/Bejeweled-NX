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
#ifndef _SOUND_HPP_
#define _SOUND_HPP_

#include "SDL_Helper.hpp"

class Sound
{
public:

	enum SOUND_TYPE
	{
		MUSIC,
		SFX
	};

protected:
	SOUND_TYPE m_type;
	int m_channel;
	bool m_inLoop;

public:
	Sound(SOUND_TYPE _type, bool _inLoop, int _channel);
	~Sound();

	virtual void End(SDL_Helper * _helper);

	virtual void Play(SDL_Helper * _helper);
	virtual void Resume(SDL_Helper * _helper);
	virtual void Pause(SDL_Helper * _helper);

	virtual void SetInLoop(bool _value);
	virtual bool InLoop();

	virtual void SetType(SOUND_TYPE _value);
	virtual SOUND_TYPE GetType();

	virtual void SetChannel(int _value);
	virtual int GetChannel();

	virtual void LoadAudio(SDL_Helper * _helper, char * _file);
};
#endif