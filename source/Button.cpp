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
#include "Button.hpp"

Button::Button(int _x, int _y, SDL_Helper * _helper, char * _sprite, char * _notInteractableTexture, char * _pressedTexture, bool _interactable, bool _animated, int _numFramesX, int _numFramesY, int _sizePerFrameX, int _sizePerFrameY, int _multipleFrames, int _currentFrameX, int _currentFrameY) : Sprite (_x, _y, _helper, _sprite, _numFramesX, _numFramesY, _sizePerFrameX, _sizePerFrameY, _currentFrameX, _currentFrameY, _multipleFrames, _animated, 1)
{
	_helper->SDL_LoadImage(&this->m_notInteractableSprite,_notInteractableTexture);
	_helper->SDL_LoadImage(&this->m_pressedSprite, _pressedTexture);

	this->m_interactable = _interactable;
	this->m_isPressed = false;
}

void Button::Draw(SDL_Helper * _helper)
{
	if (this->m_active)
	{
		if (!m_interactable)
		{
			if (this->m_multipleFrames)
				_helper->SDL_DrawImageRect(this->m_notInteractableSprite, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX, this->m_currentFrameY * this->m_sizePerFrameY, this->m_sizePerFrameX, this->m_sizePerFrameY);
			else
				_helper->SDL_DrawImage(this->m_notInteractableSprite, this->m_x, this->m_y);
		}
		else if (m_interactable && m_isPressed)
		{
			if (this->m_multipleFrames)
				_helper->SDL_DrawImageRect(this->m_pressedSprite, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX, this->m_currentFrameY * this->m_sizePerFrameY, this->m_sizePerFrameX, this->m_sizePerFrameY);
			else
				_helper->SDL_DrawImage(this->m_pressedSprite, this->m_x, this->m_y);
		}
		else
		{
			// We can call parent for default draw function
			Sprite::Draw(_helper);
		}
	}	
}

void Button::End(SDL_Helper * _helper)
{
	Sprite::End(_helper);
	_helper->SDL_DestroyTexture(this->m_notInteractableSprite);
	_helper->SDL_DestroyTexture(this->m_pressedSprite);
}

bool Button::IsPressed(touchPosition * _touch)
{
	if (!this->m_interactable)
		return false;

	this->m_isPressed = Sprite::Touched(_touch);
	return this->m_isPressed;
}

void Button::SetPressed(bool _value)
{
	this->m_isPressed = _value;
}

bool Button::IsInteractable()
{
	return this->m_interactable;
}

void Button::SetInteractable(bool _value)
{
	this->m_interactable = _value;
}

bool Button::GetPressed()
{
	return this->m_isPressed;
}