/*
 * gameWindowGUI.c
 *
 *  Created on: 14 בספט׳ 2017
 *      Author: Itamar
 */

#include "gameWindowGUI.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

GameWindow* createGW(){
	GameWindow* gw = (GameWindow*) malloc(sizeof(GameWindow));
	SDL_Surface* surface = NULL;
	if(gw==NULL){
		printf("Couldn't create GameMainWindow struct\n");
		return NULL ;
	}
	// creating the Main Window Object
	gw->window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000, 650, SDL_WINDOW_OPENGL);
	if (gw->window==NULL){
		printf("Could not create window: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	// creating the Main Window renderer
	gw->renderer = SDL_CreateRenderer(gw->window, -1, SDL_RENDERER_ACCELERATED);
	if (gw->renderer==NULL) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/gameWindow.bmp");
	if (surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	gw->bg = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->bg==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a restart texture:


	surface = SDL_LoadBMP("./utilities/restart.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->restart = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->restart==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a saveGame texture:

	surface = SDL_LoadBMP("./utilities/saveGame.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->saveGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->saveGame==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a Load Game texture:

	surface = SDL_LoadBMP("./utilities/loadGame2.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->loadGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->loadGame==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a Quit texture:

	surface = SDL_LoadBMP("./utilities/quitGame.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->quit = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->quit==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a undo texture:

	surface = SDL_LoadBMP("./utilities/undo.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->undo = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->undo==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a mainMenu texture:

	surface = SDL_LoadBMP("./utilities/mainMenu.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->mainMenu = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->mainMenu==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	SDL_FreeSurface(surface);
	return gw;
}



void destroyGameWindow(GameWindow* gw){
	if (gw==NULL) return;
	if (gw->window != NULL) SDL_DestroyWindow(gw->window);
	if (gw->renderer!=NULL) SDL_DestroyRenderer(gw->renderer);
	if (gw->loadGame!=NULL) SDL_DestroyTexture(gw->loadGame);
	if (gw->saveGame!=NULL) SDL_DestroyTexture(gw->saveGame);
	if (gw->restart!=NULL) SDL_DestroyTexture(gw->restart);
	if (gw->undo!=NULL) SDL_DestroyTexture(gw->undo);
	if (gw->mainMenu!=NULL) SDL_DestroyTexture(gw->mainMenu);
	if (gw->quit!=NULL)	SDL_DestroyTexture(gw->quit);
	if (gw->bg!=NULL) SDL_DestroyTexture(gw->bg);
	free(gw);
}

//void drawGameWindow(GameWindow* gw);
//GAME_WINDOW_EVENT gameWindowHandleEvent(GameWindow* gw, SDL_Event* event)
//bool isClickOnNewGame(int x, int y);
//bool isClickOnLoadGame(int x, int y);
//bool isClickOnQuit(int x, int y);
void gameWindowHide(GameWindow* gw){
	SDL_HideWindow(gw->window);
}

void gameWindowShow(GameWindow* gw){
	SDL_ShowWindow(gw->window);
}
