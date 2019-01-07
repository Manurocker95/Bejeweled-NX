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
#ifndef _SDL_HELPER_HPP_
#define _SDL_HELPER_HPP_
#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_FontCache.h"

class SDL_Helper
{
private:
	bool m_initialized;
	SDL_Renderer * m_renderer;
	SDL_Window * m_window;
	FC_Font * Roboto, *Roboto_large, *Roboto_small, *Roboto_OSK;
	PlFontData fontData, fontExtData;

public:
	SDL_Helper();
	SDL_Renderer *SDL_GetMainRenderer(void);
	SDL_Window *SDL_GetMainWindow(void);
	Result SDL_HelperInit(void);
	FC_Font * GetFont(int size);
	bool SDL_IsInitialized(void);
	void SDL_Exit(void);
	void SDL_ClearScreen(SDL_Color colour);
	void SDL_DrawRect(int x, int y, int w, int h, SDL_Color colour);
	void SDL_DrawCircle(int x, int y, int r, SDL_Color colour);
	void SDL_DrawText(int x, int y, int size, SDL_Color colour, const char *text);
	void SDL_DrawTextWithFont(FC_Font * font, int x, int y, SDL_Color colour, const char *text);
	void SDL_LoadCustomFont(FC_Font ** font, char * fontPath, int size, SDL_Color color);
	void SDL_DrawTextf(int x, int y, int size, SDL_Color colour, const char* text, ...);
	void SDL_GetTextDimensions(int size, const char *text, u32 *width, u32 *height);
	void SDL_LoadImage(SDL_Texture **texture, char *path);
	void SDL_LoadImageBuf(SDL_Texture **texture, void *mem, int size);
	void SDL_DrawImageOpacity(SDL_Texture *texture, int x, int y, int alpha);
	void SDL_DrawImageRotatedOpacity(SDL_Texture *texture, int x, int y, int alpha, double angle, SDL_Point center, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SDL_DrawImageScaleOpacity(SDL_Texture *texture, int x, int y, int w, int h, int alpha);
	void SDL_DrawImageRotatedScaleOpacity(SDL_Texture *texture, int x, int y, int w, int h, int alpha, double angle, SDL_Point center, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SDL_DrawImage(SDL_Texture *texture, int x, int y);
	void SDL_DrawImageRotated(SDL_Texture *texture, int x, int y, double angle, SDL_Point center, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SDL_DrawImageRect(SDL_Texture * texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h);
	void SDL_DrawImageRotatedRect(SDL_Texture * texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, double angle, SDL_Point center, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SDL_DrawImageRectOpacity(SDL_Texture * texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, int opacity);
	void SDL_DrawImageRotatedRectOpacity(SDL_Texture * texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, int opacity, double angle, SDL_Point center, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SDL_DrawImageScale(SDL_Texture *texture, int x, int y, int w, int h);
	void SDL_DrawImageRotatedScale(SDL_Texture *texture, int x, int y, int w, int h, double angle, SDL_Point center, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void SDL_Renderdisplay(void);
	void SDL_DestroyTexture(SDL_Texture * texture);
	void SDL_DestroyFont(FC_Font * font);
	void SDL_DrawBG(SDL_Color clearColor, SDL_Color colour);
	void SDL_PlayMusicAudio(Mix_Music * audio, int channel = -1, bool _loop = true);
	void SDL_LoadMusicAudio(Mix_Music ** audio, char * path);
	void SDL_DestroyMusicAudio(Mix_Music * audio);
	void SDL_LoadSound(Mix_Chunk ** sound, char * path);
	void SDL_PlaySound(Mix_Chunk * sound, int channel, bool _loop = false);
	void SDL_DestroySound(Mix_Chunk * sound);
	void SDL_PauseMusic();
	void SDL_ResumeMusic();
	void SDL_PauseChannel(int channel);
	void SDL_ResumeChannel(int channel);
	void SDL_SetVolume(int channel, float volume);
	void SDL_SetMusicVolume(float volume);
	void SDL_SetChunkVolume(Mix_Chunk * chunk, float volume);
	float SDL_GetMaxVolume();

};
#endif