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

#include "Text.hpp"
#include "Settings.hpp"

Text::Text(SDL_Helper * _helper, std::string _text, int _x, int _y, int _size, bool _customFont, char * _font, SDL_Color _color)
{
	this->m_active = true;
	this->m_text = _text;
	this->m_x = _x;
	this->m_y = _y;
	this->m_size = _size;
	this->m_textColor = _color;
	this->m_customFont = _customFont;
	SetCustomFont(_customFont, _font, _helper);
}

Text::~Text()
{

}

void Text::LoadFont(SDL_Helper * _helper, char * _font)
{
	_helper->SDL_LoadCustomFont(&this->m_font, _font, this->m_size, this->m_textColor);
}

void Text::Draw(SDL_Helper * _helper)
{
	if (this->m_active)
	{
		if (this->m_customFont)
			_helper->SDL_DrawTextWithFont(this->m_font, this->m_x, this->m_y, this->m_textColor, this->m_text.c_str());
		else
			_helper->SDL_DrawText(this->m_x, this->m_y, this->m_size, this->m_textColor, this->m_text.c_str());
	}
}

void Text::End(SDL_Helper * _helper)
{
	if (this->m_customFont)
		_helper->SDL_DestroyFont(this->m_font);
}

void Text::SetText(std::string _text)
{
	this->m_text = _text;
}

void Text::SetFont(FC_Font *_font)
{
	this->m_font = _font;
}

FC_Font * Text::GetFont()
{
	return this->m_font;
}

void Text::SetCustomFont(bool _value, char * _newFont, SDL_Helper * _helper)
{
	this->m_customFont = _value;

	if (_value)
		LoadFont(_helper, _newFont);
}
bool Text::GetCustomFont()
{
	return this->m_customFont;
}

bool Text::IsActive()
{
	return this->m_active;
}

void Text::SetActive(bool _value)
{
	this->m_active = _value;
}

void Text::SetColor(SDL_Color _color)
{
	this->m_textColor = _color;
}


void Text::MoveToCoord(int _x, int _y)
{
	this->m_x = _x;
	this->m_y = _y;
}

void Text::MoveX(int _value)
{
	if (!this->m_active)
		return;

	this->m_x += _value;
}

void Text::MoveY(int _value)
{
	if (!this->m_active)
		return;

	this->m_y += _value;
}

void Text::SetX(int _value)
{
	this->m_x = _value;
}

int Text::GetX()
{
	return this->m_x;
}

void Text::SetY(int _value)
{
	this->m_y = _value;
}

int Text::GetY()
{
	return this->m_y;
}
