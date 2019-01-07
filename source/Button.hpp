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
#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include "Sprite.hpp"

class Button : public Sprite
{
private:
	bool m_interactable;
	bool m_isPressed;
	SDL_Texture * m_notInteractableSprite;
	SDL_Texture * m_pressedSprite;

public:
	Button(int _x, int _y, SDL_Helper * _helper, char * _sprite, char * _notInteractableTexture, char * _pressedTexture, bool _interactable, bool _animated, int _numFramesX, int _numFramesY,int _sizePerFrameX, int _sizePerFrameY, int _multipleFrames, int _currentFrameX, int _currentFrameY);
	
	// Sprite methods
	void Draw(SDL_Helper * _helper) override;
	void End(SDL_Helper * _helper) override;

	// Button methods
	bool IsPressed(touchPosition * _touch);
	bool GetPressed();
	void SetPressed(bool _value);
	bool IsInteractable();
	void SetInteractable(bool _value);

};
#endif