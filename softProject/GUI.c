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
	SDL_Window* main = createMainWindow();
}

SDL_Window* createMainWindow(){
	SDL_Window* main = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,600,600, SDL_WINDOW_OPENGL);
	if(main==NULL){
		printf("Error: unable to create window: %s\n",SDL_GetError());
		SDL_Quit();
		exit(0);
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(main,-1,SDL_RENDERER_ACCELERATED);
	if(main==NULL){
		printf("Error: unable to create renderer: %s\n",SDL_GetError());
		SDL_DestroyWindow(main);
		SDL_Quit();
		exit(0);
	}
	SDL_SetRenderDrawColor(renderer,255,0,0,1);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(main);
	SDL_Quit();
	exit(0);
}

