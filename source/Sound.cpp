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
#include "Sound.hpp"

Sound::Sound(SOUND_TYPE _type, bool _inLoop, int _channel)
{
	this->m_type = _type;
	this->m_inLoop = _inLoop;
	this->m_channel = _channel;
}

Sound::~Sound()
{
}

void Sound::End(SDL_Helper * _helper)
{
	// need to be override
}

void Sound::Play(SDL_Helper * _helper)
{
	// need to be override
}

void Sound::Resume(SDL_Helper * _helper)
{
	// need to be override
}

void Sound::Pause(SDL_Helper * _helper)
{
	// need to be override
}

void Sound::SetInLoop(bool _value)
{
	this->m_inLoop = _value;
}

bool Sound::InLoop()
{
	return this->m_inLoop;
}

void Sound::SetType(SOUND_TYPE _value)
{
	this->m_type = _value;
}

Sound::SOUND_TYPE Sound::GetType()
{
	return this->m_type;
}

void Sound::SetChannel(int _value)
{
	this->m_channel = _value;
}

int Sound::GetChannel()
{
	return this->m_channel;
}

void Sound::LoadAudio(SDL_Helper * _helper, char * _file)
{

}