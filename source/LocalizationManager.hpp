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
#ifndef _LOCALIZATION_MANAGER_HPP_
#define _LOCALIZATION_MANAGER_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <nlohmann\json.hpp>
#include <switch.h>
#include <map>
#include <iostream>

#pragma once
class LocalizationManager
{

private:
	nlohmann::json m_json;
	u64 m_languageCode;
	std::string m_currentLanguage;
	bool m_canParse;
	bool m_gotSystemLanguage;

public:
	LocalizationManager();
	~LocalizationManager();

	void ParseTexts();
	const char * GetText(char * _key);
	bool GotSystemLang() { return this->m_gotSystemLanguage; }
	bool CanParse() { return this->m_canParse; }
	bool Initialized();
};
#endif