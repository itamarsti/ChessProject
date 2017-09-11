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
			SDL_WINDOWPOS_CENTERED,1000,650, SDL_WINDOW_OPENGL);
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
	SDL_Surface* loadSurface = SDL_LoadBMP("./utilities/mainWindow.bmp");
	if (loadSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		SDL_Quit();
		exit(0);
	}
	SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer,loadSurface);
	if (bgTexture == NULL ) {
			printf("Could not create a surface: %s\n", SDL_GetError());
			SDL_Quit();
			exit(0);
	}
	SDL_FreeSurface(loadSurface);
	//SDL_SetRenderDrawColor(renderer,255,0,0,1);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bgTexture, NULL, &rec);
	SDL_RenderPresent(renderer);
	SDL_Delay(100000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(main);
	SDL_Quit();
	exit(0);
}

