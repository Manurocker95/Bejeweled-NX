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

#include "Sprite.hpp"
#include "Filepaths.h"
#include "Settings.hpp"

Sprite::Sprite(int _x, int _y, SDL_Helper * _helper, char * _sprite, int _numFramesX, int _numFramesY, int _sizePerFrameX, int _sizePerFrameY, int _currentFrameX, int _currentFrameY, bool _multipleFrames, bool _animated, int _deltaTimeReduction, bool _drawOpacity, bool _draggable, int _ox, int _oy, bool _limitedInScreen)
{
	this->m_opacity = 255;
	this->m_active = true;
	this->m_updateYFrame = false;
	this->m_inLoop = true;
	this->m_dragging = false;
	this->m_x = _x;
	this->m_y = _y;
	this->m_ox = _ox;
	this->m_oy = _oy;
	this->m_animated = _animated;
	this->m_sizePerFrameX = _sizePerFrameX;
	this->m_sizePerFrameY = _sizePerFrameY;
	this->m_multipleFrames = _multipleFrames;
	this->m_currentFrameX = _currentFrameX;
	this->m_currentFrameY = _currentFrameY;
	this->m_numFramesX = _numFramesX;
	this->m_numFramesY = _numFramesY;
	this->m_drawOpacity = _drawOpacity;
	this->m_draggable = _draggable;
	this->m_limitedInScreen = _limitedInScreen;
	this->m_deltaTimeReduction = _deltaTimeReduction;
	_helper->SDL_LoadImage(&this->m_sprite, _sprite);
}

void Sprite::Draw(SDL_Helper * _helper)
{
	if (this->m_active)
	{
		if (this->m_drawOpacity)
		{
			if (this->m_multipleFrames)
				_helper->SDL_DrawImageRectOpacity(this->m_sprite, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX + this->m_ox, this->m_currentFrameY * this->m_sizePerFrameY + this->m_oy, this->m_sizePerFrameX, this->m_sizePerFrameY, this->m_opacity);
			else
				_helper->SDL_DrawImageOpacity(this->m_sprite, this->m_x, this->m_y, this->m_opacity);
		}
		else
		{
			if (this->m_multipleFrames)
				_helper->SDL_DrawImageRect(this->m_sprite, this->m_x, this->m_y, this->m_currentFrameX * this->m_sizePerFrameX + this->m_ox, this->m_currentFrameY * this->m_sizePerFrameY + this->m_oy, this->m_sizePerFrameX, this->m_sizePerFrameY);
			else
				_helper->SDL_DrawImage(this->m_sprite, this->m_x, this->m_y);
		}
	}
}

void Sprite::Update()
{
	if (this->m_active)
	{
		if (this->m_animated && this->m_multipleFrames)
		{
			Uint32 ticks = SDL_GetTicks();
			this->m_currentFrameX = (ticks / (100 * this->m_deltaTimeReduction)) % this->m_numFramesX;

			if (this->m_numFramesY > 1)
			{
				if (this->m_currentFrameX > 0 && !this->m_updateYFrame)
					this->m_updateYFrame = true;
				else if (this->m_currentFrameX == 0 && this->m_updateYFrame)
				{
					this->m_updateYFrame = false;
					++this->m_currentFrameY;

					if (this->m_currentFrameY >= this->m_numFramesY)
						this->m_currentFrameY = 0;
				}
			}

			if (!this->m_inLoop)
			{
				if (this->m_currentFrameX == this->m_numFramesX - 1 && this->m_currentFrameY == this->m_numFramesY - 1)
					this->m_animated = false;
			}
		}
	}
}

void Sprite::MoveToCoord(int _x, int _y)
{
	this->m_x = _x;
	this->m_y = _y;
}

void Sprite::MoveX(int _value)
{
	if (!this->m_active)
		return;

	if (this->m_limitedInScreen)
	{
		if ((_value > 0 && this->m_x + _value <= SWITCH_SCREEN_WIDTH - this->m_sizePerFrameX) || (_value < 0 && this->m_x + _value >= 0))
			this->m_x += _value;
	}
	else
	{
		this->m_x += _value;
	}
}

void Sprite::MoveY(int _value)
{
	if (!this->m_active)
		return;

	if (this->m_limitedInScreen)
	{
		if ((_value > 0 && this->m_y + _value <= SWITCH_SCREEN_HEIGHT - this->m_sizePerFrameY) || (_value < 0 && this->m_y + _value >= 0))
			this->m_y += _value;
	}
	else
	{
		this->m_y += _value;
	}
}

SDL_Texture * Sprite::GetSprite()
{
	return this->m_sprite;
}

void Sprite::SetSprite(SDL_Texture * _sprite)
{
	this->m_sprite = _sprite;
}

void Sprite::SetOX(int _value)
{
	this->m_ox = _value;
}

int Sprite::GetOX()
{
	return this->m_ox;
}

void Sprite::SetOY(int _value)
{
	this->m_oy = _value;
}

int Sprite::GetOY()
{
	return this->m_oy;
}

void Sprite::SetX(int _value)
{
	this->m_x = _value;
}

int Sprite::GetX()
{
	return this->m_x;
}

void Sprite::SetY(int _value)
{
	this->m_y = _value;
}

int Sprite::GetY()
{
	return this->m_y;
}

void Sprite::End(SDL_Helper * _helper)
{
	if (this->m_sprite != NULL)
		_helper->SDL_DestroyTexture(this->m_sprite);
}

void Sprite::SetNumFramesX(int _value)
{
	this->m_numFramesX = _value;
	this->m_currentFrameX = 0;
}

void Sprite::SetCurrentFrameX(int _value)
{
	this->m_currentFrameX = _value;
}

void Sprite::SetCurrentFrameY(int _value)
{
	this->m_currentFrameY = _value;
}

int  Sprite::GetCurrentFrameX()
{
	return this->m_currentFrameX;
}

int  Sprite::GetCurrentFrameY()
{
	return this->m_currentFrameY;
}

void Sprite::SetNumFramesY(int _value)
{
	this->m_numFramesY = _value;
	this->m_currentFrameX = 0;
}

int Sprite::GetNumFramesX()
{
	return this->m_numFramesX;
}

int Sprite::GetNumFramesY()
{
	return this->m_numFramesY;
}

void Sprite::SetFrameSize(int _value, bool _xAxis)
{
	if (_xAxis)
		this->m_sizePerFrameX = _value;
	else
		this->m_sizePerFrameY = _value;
}

int Sprite::GetFrameSize(bool _xAxis)
{
	if (_xAxis)
		return this->m_sizePerFrameX;
	else
		return this->m_sizePerFrameY;
}

bool Sprite::Touched(touchPosition * _touch)
{
	return (_touch->px > this->m_x && _touch->px < this->m_x + this->m_sizePerFrameX) && (_touch->py > this->m_y && _touch->py < this->m_y + this->m_sizePerFrameY);
}


bool Sprite::IsActive()
{
	return this->m_active;
}

void Sprite::SetActive(bool _value)
{
	this->m_active = _value;
}


void Sprite::SetOpacity(int _value)
{
	this->m_opacity = _value;
}

void Sprite::SetOpacityMode(bool _value)
{
	this->m_drawOpacity = _value;
}

bool Sprite::CheckOverlap(Sprite * _other)
{
	if (!this->m_active || !_other->IsActive())
		return false;

	int x = _other->GetX() + _other->GetOX();
	int y = _other->GetY() + _other->GetOY();
	int width = _other->GetFrameSize(true) - _other->GetOX();
	int height = _other->GetFrameSize(false) - _other->GetOY();

	return (((x > this->m_x + this->m_ox && x < (this->m_x + this->m_ox) + (this->m_sizePerFrameX - this->m_ox)) && (y >(this->m_y + this->m_oy) && y < (this->m_y + this->m_oy) + (this->m_sizePerFrameY - this->m_oy)))
		|| ((this->m_x + this->m_ox > x && this->m_x + this->m_ox < x + width) && (this->m_y + this->m_oy > y && this->m_y + this->m_oy < y + height)));
}

bool Sprite::IsLoop()
{
	return this->m_inLoop;
}

void Sprite::SetInLoop(bool _value)
{
	this->m_inLoop = _value;
}

bool Sprite::IsAnimated()
{
	return this->m_animated;
}


void Sprite::UpdateDrag(touchPosition * _pos)
{
	if (!this->m_active || !this->m_draggable)
	{
		return;
	}
	this->m_x = _pos->px - (m_sizePerFrameX / 2);
	this->m_y = _pos->py - (m_sizePerFrameY / 2);
}

void Sprite::OnDrag(touchPosition  *_pos)
{
	if (!this->m_active || !this->m_draggable)
	{
		return;
	}
	this->m_x = _pos->px - (m_sizePerFrameX / 2);
	this->m_y = _pos->py - (m_sizePerFrameX / 2);
}

void  Sprite::OnDrop()
{
	if (!this->m_active || !this->m_draggable)
	{
		return;
	}
	this->m_dragging = false;
}

bool Sprite::IsLimited()
{
	return this->m_limitedInScreen;
}

void Sprite::SetIsLimited(bool _value)
{
	this->m_limitedInScreen = _value;
}

int Sprite::GetOpacity()
{
	return this->m_opacity;
}

void Sprite::AddOpacity(int _value)
{
	this->m_opacity += _value;
}

void Sprite::LoadNewSprite(SDL_Helper * _helper, char * _img)
{
	if (this->m_sprite != NULL)
		_helper->SDL_DestroyTexture(this->m_sprite);

	_helper->SDL_LoadImage(&this->m_sprite, _img);
}