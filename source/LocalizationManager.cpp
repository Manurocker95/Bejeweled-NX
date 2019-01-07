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

#include "LocalizationManager.hpp"
#include "Filepaths.h"
#include <cstring>
#include <string>

LocalizationManager::LocalizationManager()
{

	Result rc = setInitialize();

	if (R_SUCCEEDED(rc))
	{
		this->m_languageCode = 0;
		this->m_gotSystemLanguage = true;

		//Get system language.
		rc = setGetSystemLanguage(&this->m_languageCode);
		if (R_SUCCEEDED(rc))
		{
			ParseTexts();
		}
		else
		{
			this->m_gotSystemLanguage = false;
			this->m_canParse = false;
		}
	}
	else
	{
		this->m_gotSystemLanguage = false;
		this->m_canParse = false;
	}
}

LocalizationManager::~LocalizationManager()
{
	setExit();
}

bool LocalizationManager::Initialized()
{
	return this->m_gotSystemLanguage && this->m_canParse;
}

void LocalizationManager::ParseTexts()
{
	this->m_gotSystemLanguage = true;
	this->m_canParse = false;
	m_currentLanguage = std::string((char*)&this->m_languageCode);

	std::ifstream langFile((std::string(LOCALIZATION_TEXT_FOLDER)+m_currentLanguage+std::string(LOCALIZATION_TEXT_FILE_EXTENSION)).c_str());
	if (langFile)
	{
		this->m_canParse = true;
		langFile >> this->m_json;
	}
	else
	{
		std::ifstream myReadFile(LOCALIZATION_TEXT_FILE);

		if (myReadFile)
		{
			this->m_canParse = true;
			myReadFile >> this->m_json;
		}
	}
}

const char * LocalizationManager::GetText(char * _key)
{	
	return this->m_json.at(_key).get<std::string>().c_str();
}