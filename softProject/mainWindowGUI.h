/*
 * mainWindowGUI.h
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef MAINWINDOWGUI_H_
#define MAINWINDOWGUI_H_


#include "GUI.h"
#include "boardFuncs.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>


typedef struct MAINWINDOW{
	boardGame* board;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bg;
	SDL_Texture* welcome;
	SDL_Texture* newGame;
	SDL_Texture* loadGame;
	SDL_Texture* Quit;
}MainWindow;

void destroyMainWindow(MainWindow* mw);
MainWindow* createMW();

#endif /* MAINWINDOWGUI_H_ */
