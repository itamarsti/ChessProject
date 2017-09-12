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
#include "mainWindowGUI.h"

void guiMain(boardGame* board){
	SDL_Window* main = createMainWindow();
}

SDL_Window* createMainWindow(){
	MainWindow* mw = (MainWindow*) malloc(sizeof(MainWindow));
	SDL_Surface* surface = NULL;
	if(mw==NULL){
		printf("Couldn't create MainWindow struct\n");
		return NULL ;
	}
	// creating the Game Board
	mw->board = createBoard();
	if (mw->board==NULL){
		printf("Couldn't create game\n");
		destroyMainWindow(mw);
		return NULL ;
	}
	// creating the Main Window Object
	mw->window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000, 650, SDL_WINDOW_OPENGL);
	if (mw->window==NULL){
		printf("Could not create window: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	// creating the Main Window renderer
	mw->renderer = SDL_CreateRenderer(mw->window, -1, SDL_RENDERER_ACCELERATED);
	if (mw->renderer==NULL) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/mainWindow.bmp");
	if (surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	mw->bg = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->bg==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a Welcome texture:

	surface = SDL_LoadBMP("./utilities/welcome.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->welcome = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->welcome==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a NewGame texture:

	surface = SDL_LoadBMP("./utilities/newGame.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->newGame = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->newGame==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a Load Game texture:

	surface = SDL_LoadBMP("./utilities/loadGame.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->loadGame = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->loadGame==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a Quit texture:

	surface = SDL_LoadBMP("./utilities/quitMain.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->quit = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->quit==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_SetRenderDrawColor(mw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(mw->renderer);
	SDL_RenderCopy(mw->renderer, mw->bg, NULL, &rec);
	rec.x = 200; rec.y = 0; rec.h = 50;rec.w = 600;	//welcome message
	SDL_RenderCopy(mw->renderer,mw->welcome,NULL,&rec);
	rec.x = 160; rec.y = 65; rec.h = 60;rec.w = 210;	//new game
	SDL_RenderCopy(mw->renderer,mw->newGame,NULL,&rec);
	rec.x = 400; rec.y = 65; rec.h = 60;rec.w = 210;	//load game
	SDL_RenderCopy(mw->renderer,mw->loadGame,NULL,&rec);
	rec.x = 640; rec.y = 65; rec.h = 60;rec.w = 210;	//quit game
	SDL_RenderCopy(mw->renderer,mw->quit,NULL,&rec);
	SDL_RenderPresent(mw->renderer);
	SDL_Delay(10000);
	SDL_DestroyRenderer(mw->renderer);
	SDL_DestroyWindow(mw->window);
	SDL_Quit();
	exit(0);
}

