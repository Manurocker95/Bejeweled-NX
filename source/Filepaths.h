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
#ifndef _FILEPATHS_HPP_
#define _FILEPATHS_HPP_

/* Save data */
#define DATA_FOLDER "sdmc:/switch/Manurocker95/Bejeweled/"
#define DATA_FILE "sdmc:/switch/Manurocker95/Bejeweled/data.sav"

/* Localization */
#define LOCALIZATION_TEXT_FOLDER  "romfs:/Assets/Files/"
#define LOCALIZATION_TEXT_FILE "romfs:/Assets/Files/en.localization"
#define LOCALIZATION_TEXT_FILE_EXTENSION ".localization"

/* Sounds */
#define SND_BGM_GAME  "romfs:/Assets/Audio/Music/game.mp3"
#define SND_BGM_TITLE  "romfs:/Assets/Audio/Music/title.mp3"

//SFX
#define SND_SFX_TAP "romfs:/Assets/Audio/SFX/tap.wav"
#define SND_SFX_POINT "romfs:/Assets/Audio/SFX/point.wav"
#define SND_SFX_SPLASH "romfs:/Assets/Audio/SFX/bbb.wav"

/* Images */
// Backgrounds
#define IMG_BACKGROUND "romfs:/Assets/Graphics/Background.png"
#define IMG_BACKGROUND_TITLE "romfs:/Assets/Graphics/titleBackground.png"

// PIECES
#define IMG_PIECE_0 "romfs:/Assets/Graphics/Piece_0.png"
#define IMG_PIECE_1 "romfs:/Assets/Graphics/Piece_1.png"
#define IMG_PIECE_2 "romfs:/Assets/Graphics/Piece_2.png"
#define IMG_PIECE_3 "romfs:/Assets/Graphics/Piece_3.png"
#define IMG_PIECE_4 "romfs:/Assets/Graphics/Piece_4.png"
#define IMG_PIECE_5 "romfs:/Assets/Graphics/Piece_5.png"
#define IMG_PIECE_6 "romfs:/Assets/Graphics/Piece_6.png"
#define IMG_GEMS "romfs:/Assets/Graphics/gems.png"

#define IMG_CURSOR "romfs:/Assets/Graphics/cursor.png"

#define IMG_TOGGLE_SOUND "romfs:/Assets/Graphics/sound.png"
#define IMG_TOGGLE_NO_SOUND "romfs:/Assets/Graphics/nosound.png"

//Splash Screen
#define IMG_SPLASHSCREEN "romfs:/Assets/Graphics/Splash.png"

// Loading Screen
#define IMG_BG_LOADING "romfs:/Assets/Graphics/Loading.png" 
// Intro - same cinematic as TREKT
#define IMG_CINEMATIC_INTRO "romfs:/Assets/Graphics/intro.png" 

// Bytton
#define IMG_BTN_RESET "romfs:/Assets/Graphics/resetBtn.png" 

#define IMG_BTN_PLAY "romfs:/Assets/Graphics/playBtn.png" 
#define IMG_BTN_PLAY_PRESSED "romfs:/Assets/Graphics/playBtnPressed.png" 
#define IMG_BTN_PLAY_NON_INTERACTABLE "romfs:/Assets/Graphics/playBtnNonInteractable.png" 

// Logo
#define IMG_LOGO "romfs:/Assets/Graphics/Logo.png"

/* Fonts */
#define FONT_NORMAL "romfs:/Assets/Fonts/normal.ttf"
#define FONT_PUZZLE "romfs:/Assets/Fonts/puzzle.ttf"

#endif