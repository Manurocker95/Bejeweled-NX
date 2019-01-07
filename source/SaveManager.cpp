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

#include "SaveManager.hpp"
#include "Filepaths.h"

SaveManager::SaveManager()
{
	this->m_data = new SaveData();
	ParseData();
}

SaveManager::~SaveManager()
{
	delete(this->m_data);
}

Settings * SaveManager::GetSettings()
{
	return this->m_data->m_settings;
}

void SaveManager::ParseData()
{
	std::ifstream myReadFile(DATA_FILE);
	
	if (myReadFile)
	{
		myReadFile >> this->m_json;
		this->m_data->m_settings->m_muted = this->m_json["muted"];
		this->m_data->m_settings->m_debugMode = this->m_json["debugMode"];
		this->m_data->m_bestScore = this->m_json["bestScore"];
	}
	else
	{
		this->m_json =
		{
			{ "muted", false },
			{ "debugMode", false },
			{ "bestScore", 0 },
		};

		std::ofstream outfile(DATA_FILE);
		outfile << this->m_json;
		outfile.close();

	}
}

void SaveManager::Save(int _score)
{
	if (this->m_data->m_bestScore < _score)
	{
		this->m_json["bestScore"] = _score;
	}
	
	this->m_json["muted"] = this->m_data->m_settings->m_muted;
	this->m_json["debugMode"] = this->m_data->m_settings->m_debugMode;

	std::ofstream outfile(DATA_FILE);
	outfile << this->m_json;
	outfile.close();
}