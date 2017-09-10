/*
 * GUI.h
 *
 *  Created on: 31 баев„ 2017
 *      Author: Itamar
 */

#ifndef GUI_H_
#define GUI_H_

#include "GUI.h"
#include "boardFuncs.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>



typedef struct MANAGER{
	boardGame* board;
	SDL_Window* mainWindow;
	SDL_Window* newGame;
	SDL_Window* game;
} manager;

SDL_Window* createMainWindow();
void guiMain(boardGame* board);

#endif /* GUI_H_ */
