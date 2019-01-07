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

#include "SDL_Helper.hpp"
#include <iostream>
#include "Settings.hpp"
#include "Colors.h"

SDL_Helper::SDL_Helper()
{

}

SDL_Renderer * SDL_Helper::SDL_GetMainRenderer(void)
{
	return this->m_renderer;
}

SDL_Window * SDL_Helper::SDL_GetMainWindow(void)
{
	return this->m_window;
}

bool SDL_Helper::SDL_IsInitialized(void)
{
	return this->m_initialized;
}

FC_Font * SDL_Helper::GetFont(int size)
{
	if (size <= 20)
		return this->Roboto_small;
	else if (size <= 25)
		return this->Roboto;
	else if (size <= 30)
		return this->Roboto_large;
	else
		return this->Roboto_OSK;

	return this->Roboto;
}

Result SDL_Helper::SDL_HelperInit(void)
{
	Result ret = 0;

	SDL_Init(SDL_INIT_EVERYTHING);
	this->m_window = SDL_CreateWindow("Template", 0, 0, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
	this->m_renderer = SDL_CreateRenderer(this->m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(this->m_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID);

	//Initialize SDL_mixer 
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return -1;

	if (R_FAILED(ret = plGetSharedFontByType(&this->fontData, PlSharedFontType_Standard)))
		return ret;

	if (R_FAILED(ret = plGetSharedFontByType(&this->fontExtData, PlSharedFontType_NintendoExt)))
		return ret;

	this->Roboto = FC_CreateFont();
	FC_LoadFont_RW(this->Roboto, this->m_renderer, SDL_RWFromMem((void*)this->fontData.address, this->fontData.size), SDL_RWFromMem((void*)this->fontExtData.address, this->fontExtData.size), 1, 25, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);

	this->Roboto_large = FC_CreateFont();
	FC_LoadFont_RW(this->Roboto_large, this->m_renderer, SDL_RWFromMem((void*)this->fontData.address, this->fontData.size), SDL_RWFromMem((void*)this->fontExtData.address, this->fontExtData.size), 1, 30, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);

	this->Roboto_small = FC_CreateFont();
	FC_LoadFont_RW(this->Roboto_small, this->m_renderer, SDL_RWFromMem((void*)this->fontData.address, this->fontData.size), SDL_RWFromMem((void*)this->fontExtData.address, this->fontExtData.size), 1, 20, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);

	this->Roboto_OSK = FC_CreateFont();
	FC_LoadFont_RW(this->Roboto_OSK, this->m_renderer, SDL_RWFromMem((void*)this->fontData.address, this->fontData.size), SDL_RWFromMem((void*)this->fontExtData.address, this->fontExtData.size), 1, 50, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);

	this->m_initialized = true;

	return 0;
}

void SDL_Helper::SDL_LoadCustomFont(FC_Font ** font, char * fontPath, int size, SDL_Color color)
{
	*font = FC_CreateFont();
	TTF_Font * ttf_font = TTF_OpenFont(fontPath, size);
	FC_LoadFontFromTTF(*font, this->m_renderer, ttf_font, ttf_font, color);
	TTF_CloseFont(ttf_font);
}

void SDL_Helper::SDL_DrawTextWithFont(FC_Font * font, int x, int y, SDL_Color colour, const char *text)
{
	FC_DrawColor(font, this->m_renderer, x, y, colour, text);
}

void SDL_Helper::SDL_DestroyFont(FC_Font * font)
{
	FC_FreeFont(font);
}

void SDL_Helper::SDL_Exit(void)
{
	FC_FreeFont(this->Roboto_OSK);
	FC_FreeFont(this->Roboto_small);
	FC_FreeFont(this->Roboto_large);
	FC_FreeFont(this->Roboto);
	TTF_Quit();

	Mix_Quit();
	Mix_CloseAudio();
	IMG_Quit();

	SDL_DestroyRenderer(this->m_renderer);
	SDL_DestroyWindow(this->m_window);
	SDL_Quit();
}


void SDL_Helper::SDL_ClearScreen(SDL_Color colour)
{
	SDL_SetRenderDrawColor(this->m_renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderClear(this->m_renderer);
}

void SDL_Helper::SDL_DrawRect(int x, int y, int w, int h, SDL_Color colour)
{
	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	SDL_SetRenderDrawColor(this->m_renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(this->m_renderer, &rect);
}

void SDL_Helper::SDL_DrawCircle(int x, int y, int r, SDL_Color colour)
{
	filledCircleRGBA(this->m_renderer, x, y, r, colour.r, colour.g, colour.b, colour.a);
	return;
}

void SDL_Helper::SDL_DrawText(int x, int y, int size, SDL_Color colour, const char *text)
{
	FC_DrawColor(GetFont(size), this->m_renderer, x, y, colour, text);
}

void SDL_Helper::SDL_DrawTextf(int x, int y, int size, SDL_Color colour, const char* text, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, 256, text, args);
	SDL_DrawText(x, y, size, colour, buffer);
	va_end(args);
}


void SDL_Helper::SDL_GetTextDimensions(int size, const char *text, u32 *width, u32 *height)
{
	FC_Font *font = GetFont(size);

	if (width != NULL)
		*width = FC_GetWidth(font, text);
	if (height != NULL)
		*height = FC_GetHeight(font, text);
}


void SDL_Helper::SDL_LoadImage(SDL_Texture **texture, char *path)
{
	SDL_Surface *loaded_surface = NULL;
	loaded_surface = IMG_Load(path);

	if (loaded_surface) {
		Uint32 colorkey = SDL_MapRGB(loaded_surface->format, 0, 0, 0);
		SDL_SetColorKey(loaded_surface, SDL_TRUE, colorkey);
		*texture = SDL_CreateTextureFromSurface(this->m_renderer, loaded_surface);
	}

	SDL_FreeSurface(loaded_surface);
}

void SDL_Helper::SDL_DrawImage(SDL_Texture *texture, int x, int y)
{
	SDL_Rect position;
	position.x = x; position.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	SDL_RenderCopy(this->m_renderer, texture, NULL, &position);
}

void SDL_Helper::SDL_DrawImageRotated(SDL_Texture *texture, int x, int y, double angle, SDL_Point center, SDL_RendererFlip flip)
{
	SDL_Rect position;
	position.x = x; position.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	SDL_RenderCopyEx(this->m_renderer, texture, NULL, &position, angle, &center, flip);
}

void SDL_Helper::SDL_DrawImageRect(SDL_Texture * texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h)
{
	SDL_Rect srcrect = { tex_x, tex_y, tex_w, tex_h };
	SDL_Rect dstrect = { x, y, tex_w, tex_h };
	SDL_RenderCopy(this->m_renderer, texture, &srcrect, &dstrect);
}

void SDL_Helper::SDL_DrawImageRotatedRect(SDL_Texture * texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, double angle, SDL_Point center, SDL_RendererFlip flip)
{
	SDL_Rect srcrect = { tex_x, tex_y, tex_w, tex_h };
	SDL_Rect dstrect = { x, y, tex_w, tex_h };
	SDL_RenderCopyEx(this->m_renderer, texture, &srcrect, &dstrect, angle, &center, flip);
}

void SDL_Helper::SDL_DrawImageRectOpacity(SDL_Texture * texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, int opacity)
{
	SDL_SetTextureAlphaMod(texture, opacity);
	SDL_DrawImageRect(texture, x, y, tex_x, tex_y, tex_w, tex_h);
}

void SDL_Helper::SDL_DrawImageRotatedRectOpacity(SDL_Texture * texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h, int opacity, double angle, SDL_Point center, SDL_RendererFlip flip)
{
	SDL_SetTextureAlphaMod(texture, opacity);
	SDL_DrawImageRotatedRect(texture, x, y, tex_x, tex_y, tex_w, tex_h, angle, center, flip);
}

void SDL_Helper::SDL_DrawImageScale(SDL_Texture *texture, int x, int y, int w, int h)
{
	SDL_Rect position;
	position.x = x; position.y = y; position.w = w; position.h = h;
	SDL_RenderCopy(this->m_renderer, texture, NULL, &position);
}

void SDL_Helper::SDL_DrawImageRotatedScale(SDL_Texture *texture, int x, int y, int w, int h, double angle, SDL_Point center, SDL_RendererFlip flip)
{
	SDL_Rect position;
	position.x = x; position.y = y; position.w = w; position.h = h;
	SDL_RenderCopyEx(this->m_renderer, texture, NULL, &position, angle, &center, flip);
}

void SDL_Helper::SDL_Renderdisplay(void)
{
	SDL_RenderPresent(this->m_renderer);
}

void SDL_Helper::SDL_DrawImageOpacity(SDL_Texture *texture, int x, int y, int opacity)
{
	SDL_SetTextureAlphaMod(texture, opacity);
	SDL_DrawImage(texture, x, y);
}

void SDL_Helper::SDL_DrawImageRotatedOpacity(SDL_Texture *texture, int x, int y, int opacity, double angle, SDL_Point center, SDL_RendererFlip flip)
{
	SDL_SetTextureAlphaMod(texture, opacity);
	SDL_DrawImageRotated(texture, x, y, angle, center, flip);
}

void SDL_Helper::SDL_DrawImageScaleOpacity(SDL_Texture *texture, int x, int y, int w, int h, int opacity)
{
	SDL_SetTextureAlphaMod(texture, opacity);
	SDL_DrawImageScale(texture, x, y, w, h);
}

void SDL_Helper::SDL_DrawImageRotatedScaleOpacity(SDL_Texture *texture, int x, int y, int w, int h, int opacity, double angle, SDL_Point center, SDL_RendererFlip flip)
{
	SDL_SetTextureAlphaMod(texture, opacity);
	SDL_DrawImageRotatedScale(texture, x, y, w, h, angle, center, flip);
}

void SDL_Helper::SDL_DestroyTexture(SDL_Texture * texture)
{
	SDL_DestroyTexture(texture);
}

void SDL_Helper::SDL_DrawBG(SDL_Color clearColor, SDL_Color colour)
{
	SDL_ClearScreen(clearColor);
	SDL_DrawRect(0, 0, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, colour);
}

void SDL_Helper::SDL_LoadMusicAudio(Mix_Music ** sound, char * path)
{
	*sound = Mix_LoadMUS(path);
}

void SDL_Helper::SDL_PlayMusicAudio(Mix_Music * audio, int channel, bool _loop)
{
	SDL_ResumeMusic();
	int _times = _loop ? -1 : 1;
	if (Mix_PlayMusic(audio, _times) == -1)
	{
		return;
	}
}

void SDL_Helper::SDL_DestroyMusicAudio(Mix_Music * audio)
{
	Mix_FreeMusic(audio);
}

void SDL_Helper::SDL_LoadSound(Mix_Chunk ** sound, char * path)
{
	*sound = Mix_LoadWAV(path);
}

void SDL_Helper::SDL_PlaySound(Mix_Chunk * sound, int channel, bool _loop)
{
	int _times = _loop ? -1 : 0; // zero?
	if (Mix_PlayChannel(channel, sound, _times) == -1)
	{
		return;
	}
}

void SDL_Helper::SDL_DestroySound(Mix_Chunk * sound)
{
	Mix_FreeChunk(sound);
}

void SDL_Helper::SDL_PauseMusic()
{
	Mix_PauseMusic();
}

void SDL_Helper::SDL_ResumeMusic()
{
	Mix_ResumeMusic();
}

void SDL_Helper::SDL_SetMusicVolume(float volume)
{
	Mix_VolumeMusic(volume);
}

void SDL_Helper::SDL_PauseChannel(int channel)
{
	Mix_Pause(channel);
}

void SDL_Helper::SDL_ResumeChannel(int channel)
{
	Mix_Resume(channel);
}

void SDL_Helper::SDL_SetVolume(int channel, float volume)
{
	Mix_Volume(channel, volume);
}

void SDL_Helper::SDL_SetChunkVolume(Mix_Chunk * chunk, float volume)
{
	Mix_VolumeChunk(chunk, volume);
}

float SDL_Helper::SDL_GetMaxVolume()
{
	return MIX_MAX_VOLUME;
}