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
#include "MusicSound.hpp"

MusicSound::MusicSound(SDL_Helper * _helper, char * _file, bool _inLoop, int _channel) : Sound(SOUND_TYPE::MUSIC, _inLoop, _channel)
{
	LoadAudio(_helper, _file);
}


MusicSound::~MusicSound()
{

}

Mix_Music * MusicSound::GetAudio()
{
	return this->m_music;
}

void MusicSound::SetAudio(Mix_Music * _audio)
{
	this->m_music = _audio;
}

void MusicSound::LoadAudio(SDL_Helper * _helper, char * _file)
{
	_helper->SDL_LoadMusicAudio(&this->m_music, _file);
}

void MusicSound::End(SDL_Helper * _helper)
{
	_helper->SDL_PauseMusic();
	_helper->SDL_DestroyMusicAudio(this->m_music);
}

void MusicSound::Play(SDL_Helper * _helper)
{
	_helper->SDL_PlayMusicAudio(this->m_music, this->m_channel, this->m_inLoop);
}

void MusicSound::Resume(SDL_Helper * _helper)
{
	_helper->SDL_ResumeMusic();
}

void MusicSound::Pause(SDL_Helper * _helper)
{
	_helper->SDL_PauseMusic();
}