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

#include "Toggle.hpp"

Toggle::Toggle(bool _defaultValue, int _x, int _y, SDL_Helper * _helper, char * _sprite, char * _offSprite, bool _interactable, bool _animated, int _numFramesX, int _numFramesY, int _sizePerFrameX, int _sizePerFrameY, int _multipleFrames, int _currentFrameX, int _currentFrameY) : Sprite(_x, _y, _helper, _sprite, _numFramesX, _numFramesY, _sizePerFrameX, _sizePerFrameY, _currentFrameX, _currentFrameY, _multipleFrames, _animated, 1)
{
	_helper->SDL_LoadImage(&this->m_spriteOff, _offSprite);
	this->m_valueChanged = false;
	this->m_interactable = _interactable;
	this->m_isPressed = false;
	this->m_isOn = _defaultValue;
}

void Toggle::Draw(SDL_Helper * _helper)
{
	if (this->m_active)
	{
		if (this->m_multipleFrames)
			if (this->m_isOn)
				_helper->SDL_DrawImageRect(this->m_sprite, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX, this->m_currentFrameY * this->m_sizePerFrameY, this->m_sizePerFrameX, this->m_sizePerFrameY);
			else
				_helper->SDL_DrawImageRect(this->m_spriteOff, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX, this->m_currentFrameY * this->m_sizePerFrameY, this->m_sizePerFrameX, this->m_sizePerFrameY);
		else
			if (this->m_isOn)
				_helper->SDL_DrawImage(this->m_sprite, this->m_x, this->m_y);
			else
				_helper->SDL_DrawImage(this->m_spriteOff, this->m_x, this->m_y);
	}
}

void Toggle::End(SDL_Helper * _helper)
{
	Sprite::End(_helper);
	_helper->SDL_DestroyTexture(this->m_spriteOff);
}

void Toggle::CheckIsPressed(touchPosition * _touch)
{
	if (!this->m_interactable)
		return;

	if (!this->m_isPressed)
	{
		this->m_isPressed = Sprite::Touched(_touch);
		if (this->m_isPressed)
		{
			OnValueChange();
		}
	}
}

void Toggle::OnValueChange()
{
	this->m_valueChanged = true;
	this->m_isOn = !this->m_isOn;
}

bool Toggle::IsOn()
{
	return this->m_isOn;
}

void Toggle::ResetChangeValue()
{
	this->m_valueChanged = false;
	this->m_isPressed = false;
}

bool Toggle::ValueChanged()
{
	return this->m_valueChanged;
}

void Toggle::SetPressed(bool _value)
{
	this->m_isPressed = _value;
}