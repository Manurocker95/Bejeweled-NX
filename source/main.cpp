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

// Include cout library
#include <iostream>

// Include the main libnx system header, for Switch development
#include <switch.h>
#include "SDL_Helper.hpp"
#include "Colors.h"
#include "Settings.hpp"
#include "SceneManager.hpp"
#include <sys\stat.h>
#include "Filepaths.h"

// Main program entrypoint
int main(int argc, char* argv[])
{
	consoleInit(NULL);
	plInitialize();
	romfsInit();

	mkdir(DATA_FOLDER, 0777);

	SDL_Helper * helper = new SDL_Helper();
	helper->SDL_HelperInit();
	
	SceneManager::Instance()->Start(helper);

	if (!SceneManager::Instance()->IsOut())
	{
		// Main loop
		while (appletMainLoop())
		{
			helper->SDL_ClearScreen(C_BLACK);
			helper->SDL_DrawRect(0, 0, SWITCH_SCREEN_WIDTH, SWITCH_SCREEN_HEIGHT, C_WHITE);

			SceneManager::Instance()->Update();

			if (SceneManager::Instance()->IsOut())
				break; // break in order to return to hbmenu

			helper->SDL_Renderdisplay();
		}
	}


	plExit();
	romfsExit();
	SceneManager::Instance()->Exit();
	delete(SceneManager::Instance());

	helper->SDL_Exit();
	delete(helper);

	return 0;
}