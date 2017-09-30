/*
 * mainWindowGUI.c
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: Itamar
 */

/**
 * MainWindow summary:
 *
 * The Main Window GUI sections. This functions are responsible for creating
 * the Main window Data structure, handling the different events in this window etc.
 *
 *
 * createMW							- Crating the MainWindow structure
 * destroyMainWindow				- Destroying the mainWindow Structure
 * drawMainWindow					- Drawing the mainWindow
 * mainWindowHandleEvent			- Classifying different events in Main window
 * isClickOnNewGame					- Checking if there was click on New Game button
 * isClickOnLoadGame				- Checking if there was click on new game button
 * isClickOnQuit					- Checking if there was click on Quit button
 * mainWindowHide					- Hiding the Window
 * mainWindowShow					- Showing the Window
 * mainWindowGuiManager				- Handling the events
 *
 *
 */


#include "mainWindowGUI.h"
#include <assert.h>
#include "boardFuncs.h"






/**
 *
 * Creating the MainWindow structure using SDL.
 * In this part we create a window, renderer and buttons.
 *
 * @return
 * MainWindow pointer of the data Structure
 *
 */


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
		printf("Could not create window in MainWindowGUI: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	// creating the Main Window renderer
	mw->renderer = SDL_CreateRenderer(mw->window, -1, SDL_RENDERER_ACCELERATED);
	if (mw->renderer==NULL) {
		printf("Could not create a renderer in MainWindowGUI: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/mainWindow/mainWindow.bmp");
	if (surface==NULL){
		printf("Could not create a BackGround surface in MainWindowGUI: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	mw->bg = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->bg==NULL){
		printf("Could not create a BackGround texture in MainWindowGUI: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a Welcome texture:

	surface = SDL_LoadBMP("./utilities/mainWindow/welcome.bmp");
	if(surface==NULL){
		printf("Could not create a Welcome surface in MainWindowGUI: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->welcome = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->welcome==NULL){
		printf("Could not create a welcome texture in MainWindowGUI: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a NewGame texture:

	surface = SDL_LoadBMP("./utilities/mainWindow/newGame.bmp");
	if(surface==NULL){
		printf("Could not create a newGame surface in MainWindowGUI: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->newGame = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->newGame==NULL){
		printf("Could not create a newGame texture in MainWindowGUI: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a Load Game texture:

	surface = SDL_LoadBMP("./utilities/mainWindow/loadGame.bmp");
	if(surface==NULL){
		printf("Could not create a loadGame surface in MainWindowGUI: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->loadGame = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->loadGame==NULL){
		printf("Could not create a loadGame texture in MainWindowGUI: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a Quit texture:

	surface = SDL_LoadBMP("./utilities/mainWindow/quitMain.bmp");
	if(surface==NULL){
		printf("Could not create a quit surface in MainWindowGUI: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	mw->quit = SDL_CreateTextureFromSurface(mw->renderer, surface);
	if (mw->quit==NULL){
		printf("Could not create a quit texture in MainWindowGUI: %s\n", SDL_GetError());
		destroyMainWindow(mw);
		return NULL ;
	}
	SDL_FreeSurface(surface);
	return mw;
}

/**
 *
 * Destroying the MainWindow data structure with it's elements and free the memory.
 *
 * @param MainWindow - Main Window data structure
 *
 * @return
 * void
 *
 */

void destroyMainWindow(MainWindow* mw){
	if (mw==NULL) return;
	if(mw->welcome!=NULL) SDL_DestroyTexture(mw->welcome);
	if(mw->quit!=NULL) SDL_DestroyTexture(mw->quit);
	if(mw->newGame!=NULL) SDL_DestroyTexture(mw->newGame);
	if(mw->loadGame!=NULL) SDL_DestroyTexture(mw->loadGame);
	if(mw->bg!=NULL) SDL_DestroyTexture(mw->bg);
	if(mw->renderer!=NULL) SDL_DestroyRenderer(mw->renderer);
	if (mw->window != NULL) SDL_DestroyWindow(mw->window);
	free(mw);
}


/**
 *
 * Drawing the window and presents it to the user.
 *
 * @param MainWindow - Main Window data structure
 *
 * @return
 * void
 *
 */


void drawMainWindow(MainWindow* mw){
	if(mw==NULL){
		printf("ERROR: MainWindow is NULL in drawWindow function\n");
		return;
	}
	assert(mw->quit!=NULL);	assert(mw->bg!=NULL);assert(mw->loadGame!=NULL);
	assert(mw->newGame!=NULL);	assert(mw->renderer!=NULL);	assert(mw->window != NULL);
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


/**
 *
 * This function accepts events and classifying them to an operational commands.
 *
 * @param MainWindow - Main Window data structure
 * @SDL_Event - the interface event
 *
 * @return
 * MAIN_WINDOW_EVENT command event
 *
 */

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



/**
 *
 * This function checks if there was an event in the boundaries of the NewGame Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the NewGame Button boundaries, false otherwise.
 *
 */

bool isClickOnNewGame(int x, int y) {
	if ((x >= 160 && x <= 370) && (y >= 65 && y <= 125)) {
		return true;
	}
	return false;
}

/**
 *
 * This function checks if there was an event in the boundaries of the LoadGame Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the LoadGame Button boundaries, false otherwise.
 *
 */

bool isClickOnLoadGame(int x, int y) {
	if ((x >= 400 && x <= 640) && (y >= 65 && y <= 125)) {
		return true;
	}
	return false;
}


/**
 *
 * This function checks if there was an event in the boundaries of the Quit Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the Quit Button boundaries, false otherwise.
 *
 */

bool isClickOnQuit(int x, int y) {
	if ((x >= 640 && x <= 850) && (y >= 65 && y <= 125)) {
		return true;
	}
	return false;
}


/**
 *
 * This function Hiding the MainWindow
 *
 * @param mw - MainWindow data structure
 *
 * @return
 * void
 *
 */

void mainWindowHide(MainWindow* mw) {
	SDL_HideWindow(mw->window);
}

/**
 *
 * This function showing the MainWindow
 *
 * @param mw - MainWindow data structure
 *
 * @return
 * void
 *
 */

void mainWindowShow(MainWindow* mw) {
	SDL_ShowWindow(mw->window);
}


/**
 *
 * This function responsible for handling the events and translates them to on operetions
 * in the Main Window section.
 *
 * @param mw - MainWindow data structure
 *
 * @return
 * int between 1-3:
 * 		1: quit the game
 * 		2: go to Load Window
 * 		3: go to Settings Window
 *
 */

int mainWindowGuiManager(MainWindow* mw){
	assert(mw !=NULL);
	drawMainWindow(mw);
	bool quitMain = false;
	while(!quitMain){
		SDL_Event event;
		while(SDL_PollEvent(&event)!=0){
			if (mainWindowHandleEvent(mw, &event) == MAIN_WINDOW_EVENT_QUIT) {
				destroyMainWindow(mw);
				return 1;
			}
			else if (mainWindowHandleEvent(mw, &event) == MAIN_WINDOW_LOAD_GAME){
				destroyMainWindow(mw);
				return 2;
			}
			else if (mainWindowHandleEvent(mw, &event) == MAIN_WINDOW_NEW_GAME){
				destroyMainWindow(mw);
				return 3;
			}
		}
	}
	return 0;
}
