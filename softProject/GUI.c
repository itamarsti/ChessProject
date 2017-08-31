/*
 * GUI.c
 *
 *  Created on: 31 баев„ 2017
 *      Author: Itamar
 */

#include "GUI.h"
#include "boardFuncs.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>


void guiMain(boardGame* board){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* mainWindow = NULL;
	mainWindow = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_RESIZABLE);
	if (mainWindow==NULL) printf("Error: unable to create window: %s\n",SDL_GetError());
	SDL_Renderer* renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (renderer==NULL) printf("Error: unable to create renderer: %s\n",SDL_GetError());
	SDL_Delay(10000);
	SDL_Quit();
}
