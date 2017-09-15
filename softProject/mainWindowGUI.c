/*
 * mainWindowGUI.c
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: Itamar
 */


#include "mainWindowGUI.h"
#include <assert.h>
#include "boardFuncs.h"


MainWindow* createMW(){
	MainWindow* mw = (MainWindow*) malloc(sizeof(MainWindow));
	SDL_Surface* surface = NULL;
	if(mw==NULL){
		printf("Couldn't create MainWindow struct\n");
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
	surface= SDL_LoadBMP("./utilities/mainWindow/mainWindow.bmp");
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

	surface = SDL_LoadBMP("./utilities/mainWindow/welcome.bmp");
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

	surface = SDL_LoadBMP("./utilities/mainWindow/newGame.bmp");
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

	surface = SDL_LoadBMP("./utilities/mainWindow/loadGame.bmp");
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

	surface = SDL_LoadBMP("./utilities/mainWindow/quitMain.bmp");
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
	return mw;
}


void destroyMainWindow(MainWindow* mw){
	if (mw==NULL) return;
	if (mw->window != NULL) SDL_DestroyWindow(mw->window);
	if (mw->renderer!=NULL) SDL_DestroyRenderer(mw->renderer);
	if (mw->loadGame!=NULL) SDL_DestroyTexture(mw->loadGame);
	if (mw->newGame!=NULL) SDL_DestroyTexture(mw->newGame);
	if (mw->welcome!=NULL) SDL_DestroyTexture(mw->welcome);
	if (mw->quit!=NULL)	SDL_DestroyTexture(mw->quit);
	if (mw->bg!=NULL) SDL_DestroyTexture(mw->bg);
	free(mw);
}

void drawMainWindow(MainWindow* mw){
	if(mw==NULL){
		printf("mw is NULL");
		return;
	}
	assert(mw->quit!=NULL);
	assert(mw->bg!=NULL);
	assert(mw->loadGame!=NULL);
	assert(mw->newGame!=NULL);
	assert(mw->renderer!=NULL);
	assert(mw->window != NULL);
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
}



MAIN_WINDOW_EVENT mainWindowHandleEvent(MainWindow* mw, SDL_Event* event) {
	if (event == NULL || mw == NULL ) {
		return MAIN_WINDOW_INVALID;
	}
	switch (event->type) {
		case SDL_MOUSEBUTTONUP:
			 if(isClickOnNewGame(event->button.x, event->button.y)){
				return MAIN_WINDOW_NEW_GAME;
			 }
			 else if(isClickOnLoadGame(event->button.x, event->button.y)){
				 return MAIN_WINDOW_LOAD_GAME;
			 }
			 else if(isClickOnQuit(event->button.x, event->button.y)){
				 return  MAIN_WINDOW_EVENT_QUIT;
			 }
			 break;
		case SDL_WINDOWEVENT:
			if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
				return MAIN_WINDOW_EVENT_QUIT;
			}
			break;
		default:
			return MAIN_WINDOW_EVENT_NONE;
		}
	return MAIN_WINDOW_EVENT_NONE;
}



bool isClickOnNewGame(int x, int y) {
	if ((x >= 160 && x <= 370) && (y >= 65 && y <= 125)) {
		return true;
	}
	return false;
}

bool isClickOnLoadGame(int x, int y) {
	if ((x >= 400 && x <= 640) && (y >= 65 && y <= 125)) {
		return true;
	}
	return false;
}

bool isClickOnQuit(int x, int y) {
	if ((x >= 640 && x <= 850) && (y >= 65 && y <= 125)) {
		return true;
	}
	return false;
}


void mainWindowHide(MainWindow* mw) {
	SDL_HideWindow(mw->window);
}

void mainWindowShow(MainWindow* mw) {
	SDL_ShowWindow(mw->window);
}
