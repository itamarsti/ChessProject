/*
 * mainWindowGUI.c
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: Itamar
 */


#include "mainWindowGUI.h"

MainWindow* createMW(){
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

	surface = SDL_LoadBMP("./utilities/LoadGame.bmp");
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

	surface = SDL_LoadBMP("./utilities/QuitMain.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->Quit = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->Quit==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);
	return mw;
}


void destroyMainWindow(MainWindow* mw){
	if (mw==NULL) return;
	if (mw->board!=NULL) destroyBoard(mw->board);
	if (mw->window != NULL) SDL_DestroyWindow(mw->window);
	if (mw->renderer!=NULL) SDL_DestroyRenderer(mw->renderer);
	if (mw->loadGame!=NULL) SDL_DestroyTexture(mw->loadGame);
	if (mw->newGame!=NULL) SDL_DestroyTexture(mw->newGame);
	if (mw->welcome!=NULL) SDL_DestroyTexture(mw->welcome);
	if (mw->Quit!=NULL)	SDL_DestroyTexture(mw->Quit);
	if (mw->bg!=NULL) SDL_DestroyTexture(mw->bg);
	free(mw);
}
