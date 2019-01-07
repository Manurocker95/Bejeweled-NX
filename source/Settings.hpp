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
#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#define SWITCH_SCREEN_WIDTH 1280
#define SWITCH_SCREEN_HEIGHT 720

#include <string>

class Settings
{
public:
	
	std::string m_projectName;

	double m_version;
	int m_loadingDelay;
	int m_deltaTimeReduction;// HALF TIME -> SDL_TICKS/(100*reduction)
	int m_maxTime; // in minutes
	int m_tokenSize;
	int m_yTokens;
	int m_xTokens;

	bool m_debugMode;
	bool m_muted;
	bool m_paused;

public:

	Settings() 
	{
		this->m_projectName = "Fifteen NX";
		this->m_version = 1.0;
		this->m_loadingDelay = 2;
		this->m_deltaTimeReduction = 2;
		this->m_xTokens = 10;
		this->m_yTokens = 10;
		this->m_tokenSize = 54;
		this->m_muted = false;
		this->m_debugMode = false;
		this->m_paused = false;
	}

	void SetMute(bool _value)
	{
		this->m_debugMode = _value;
	}

	void ToggleMute()
	{
		this->m_muted = !this->m_muted;
	}
	
	void TogglePause()
	{
		this->m_paused = !this->m_paused;
	}
};
#endif