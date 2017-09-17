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

void createGR(GameWindow* gw, bool undoBool, bool restartBool, bool saveBool
		, bool loadBool, bool mmBool, bool quitBool){
	assert(gw!=NULL); assert(gw->window!=NULL);
	SDL_Surface* surface = NULL;

	// creating the game Window renderer
	gw->renderer = SDL_CreateRenderer(gw->window, -1, SDL_RENDERER_ACCELERATED);
	if (gw->renderer==NULL) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/gameWindow/gameBackground2.bmp");
	if (surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	gw->bg = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->bg==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a chessBoard texture:
	surface= SDL_LoadBMP("./utilities/gameWindow/chessBoard2.bmp");
	if (surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	gw->cb = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->cb==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a undo texture:

	if(!undoBool) surface = SDL_LoadBMP("./utilities/gameWindow/undo.bmp");
	else if(undoBool) surface = SDL_LoadBMP("./utilities/gameWindow/undoClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->undo = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->undo==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a restart texture:
	if(!restartBool)surface = SDL_LoadBMP("./utilities/gameWindow/restart.bmp");
	else if(!restartBool)surface = SDL_LoadBMP("./utilities/gameWindow/restartClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->restart = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->restart==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a saveGame texture:

	if(!saveBool)surface = SDL_LoadBMP("./utilities/gameWindow/save.bmp");
	else if(!saveBool)surface = SDL_LoadBMP("./utilities/gameWindow/saveClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->saveGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->saveGame==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a Load Game texture:

	if(!loadBool) surface = SDL_LoadBMP("./utilities/gameWindow/load.bmp");
	else if(!loadBool) surface = SDL_LoadBMP("./utilities/gameWindow/loadClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->loadGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->loadGame==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a mainMenu texture:
	if(!mmBool) surface = SDL_LoadBMP("./utilities/gameWindow/mainMenu.bmp");
	else if(!mmBool) surface = SDL_LoadBMP("./utilities/gameWindow/mainMenuClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->mainMenu = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->mainMenu==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a Quit texture:

	if(!quitBool) surface = SDL_LoadBMP("./utilities/gameWindow/quit.bmp");
	else if(!quitBool) surface = SDL_LoadBMP("./utilities/gameWindow/quitClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->quit = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->quit==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

}

GameWindow* createGW(){
	GameWindow* gw = (GameWindow*) malloc(sizeof(GameWindow));
	if(gw==NULL){
		printf("Couldn't create GameMainWindow struct\n");
		return NULL ;
	}
	// creating the game Window Object
	gw->window = (SDL_Window*) SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000, 650, SDL_WINDOW_OPENGL);
	if (gw->window==NULL){
		printf("Could not create window: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	createGR(gw,false,false,false,false,false,false);
	return gw;
}

void drawGameWindow(GameWindow* gw){
	if(gw==NULL){
		printf("gw is NULL");
		return;
	}
	assert(gw->window!=NULL); assert(gw->bg!=NULL);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1300, .h = 650 };
	SDL_SetRenderDrawColor(gw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(gw->renderer);
	SDL_RenderCopy(gw->renderer, gw->bg, NULL, &rec);
	rec.x = 350; rec.y = 25; rec.w = 600;rec.h = 600;	//chessBoard message
	SDL_RenderCopy(gw->renderer,gw->cb,NULL,&rec);

	rec.x = 60; rec.y = 60; rec.w = 200;rec.h = 60;	//undo message
	SDL_RenderCopy(gw->renderer,gw->undo,NULL,&rec);

	rec.x = 60; rec.y = 150; rec.w = 200;rec.h = 60;	//restart message
	SDL_RenderCopy(gw->renderer,gw->restart,NULL,&rec);

	rec.x = 60; rec.y = 240; rec.w = 200;rec.h = 60;	//save message
	SDL_RenderCopy(gw->renderer,gw->saveGame,NULL,&rec);

	rec.x = 60; rec.y = 330; rec.w = 200;rec.h = 60;	//load message
	SDL_RenderCopy(gw->renderer,gw->loadGame,NULL,&rec);

	rec.x = 60; rec.y = 420; rec.w = 200;rec.h = 60;	//mainMenu message
	SDL_RenderCopy(gw->renderer,gw->mainMenu,NULL,&rec);

	rec.x = 60; rec.y = 510; rec.w = 200;rec.h = 60;	//quit message
	SDL_RenderCopy(gw->renderer,gw->quit,NULL,&rec);

	SDL_RenderPresent(gw->renderer);
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
	if (gw->cb!=NULL) SDL_DestroyTexture(gw->cb);
	free(gw);
}

void destroyGameRenderer(GameWindow* gw){
	if (gw==NULL) return;
	if (gw->window == NULL) return;
	if (gw->renderer!=NULL) SDL_DestroyRenderer(gw->renderer);
	if (gw->loadGame!=NULL) SDL_DestroyTexture(gw->loadGame);
	if (gw->saveGame!=NULL) SDL_DestroyTexture(gw->saveGame);
	if (gw->restart!=NULL) SDL_DestroyTexture(gw->restart);
	if (gw->undo!=NULL) SDL_DestroyTexture(gw->undo);
	if (gw->mainMenu!=NULL) SDL_DestroyTexture(gw->mainMenu);
	if (gw->quit!=NULL)	SDL_DestroyTexture(gw->quit);
	if (gw->bg!=NULL) SDL_DestroyTexture(gw->bg);
	if (gw->cb!=NULL) SDL_DestroyTexture(gw->cb);
}




GAME_WINDOW_EVENT gameWindowHandleEvent(GameWindow* gw, SDL_Event* event){
	if (event == NULL || gw == NULL ) {
		return GAME_WINDOW_INVALID;
	}
	switch (event->type) {
		case SDL_MOUSEBUTTONUP:
			 if(isClickOnSaveGame(event->button.x, event->button.y)){
				return GAME_WINDOW_PUSH_SAVE_GAME;
			 }
			 else if(isClickOnLoadGameWindow(event->button.x, event->button.y)){
				 return GAME_WINDOW_PUSH_LOAD_GAME;
			 }
			 else if(isClickOnQuitGameWindow(event->button.x, event->button.y)){
				 return  GAME_WINDOW_PUSH_EVENT_QUIT;
			 }
			 else if(isClickOnRestart(event->button.x, event->button.y)){
				 return  GAME_WINDOW_PUSH_RESTART_GAME;
			 }
			 else if(isClickOnUndo(event->button.x, event->button.y)){
				 return  GAME_WINDOW_PUSH_UNDO;
			 }
			 else if(isClickOnMainMenu(event->button.x, event->button.y)){
				 return  GAME_WINDOW_PUSH_MAIN_MENU;
			 }
			 break;
		case SDL_MOUSEMOTION:
			if(isClickOnSaveGame(event->motion.x, event->motion.y)){
				return GAME_WINDOW_HOVER_SAVE_GAME;
			 }
			 else if(isClickOnLoadGameWindow(event->motion.x, event->motion.y)){
				 return GAME_WINDOW_HOVER_LOAD_GAME;
			 }
			 else if(isClickOnQuitGameWindow(event->motion.x, event->motion.y)){
				 return  GAME_WINDOW_HOVER_EVENT_QUIT;
			 }
			 else if(isClickOnRestart(event->motion.x, event->motion.y)){
				 return  GAME_WINDOW_HOVER_RESTART_GAME;
			 }
			 else if(isClickOnUndo(event->motion.x, event->motion.y)){
				 return  GAME_WINDOW_HOVER_UNDO;
			 }
			 else if(isClickOnMainMenu(event->motion.x, event->motion.y)){
				 return  GAME_WINDOW_HOVER_MAIN_MENU;
			 }
			 break;
		case SDL_WINDOWEVENT:
			if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
				return GAME_WINDOW_PUSH_EVENT_QUIT;
			}
			break;
		default:
			return GAME_WINDOW_EVENT_NONE;
		}
	return GAME_WINDOW_EVENT_NONE;
}


bool isClickOnUndo(int x, int y){
	if((x>=60 && x<=260)&& (y>=60&&y<=120)) return true;
	return false;
}

bool isClickOnRestart(int x, int y){
	if((x>=60 && x<=260)&& (y>=150&&y<=210)) return true;
	return false;
}

bool isClickOnSaveGame(int x, int y){
	if((x>=60 && x<=260)&& (y>=240&&y<=300)) return true;
	return false;
}

bool isClickOnLoadGameWindow(int x, int y){
	if((x>=60 && x<=260)&& (y>=330&&y<=390)) return true;
	return false;
}
bool isClickOnMainMenu(int x, int y){
	if((x>=60 && x<=260)&& (y>=420&&y<=480)) return true;
	return false;
}

bool isClickOnQuitGameWindow(int x, int y){
	if((x>=60 && x<=260)&& (y>=510&&y<=570)) return true;
	return false;
}


void saveGameFromGUI(boardGame* game, int numOfFiles){
	assert(game!=NULL); assert(game->boardArr!=NULL);
	const char* savePath = (char*) "./utilities/loadedGames/game1.xml";
	if(numOfFiles==5){
		remove("./utilities/loadedGames/game5.xml");
		rename("./utilities/loadedGames/game4.xml","./utilities/loadedGames/game5.xml");
		rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game4.xml");
		rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game3.xml");
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==4){
		rename("./utilities/loadedGames/game4.xml","./utilities/loadedGames/game5.xml");
		rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game4.xml");
		rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game3.xml");
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==3){
		rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game4.xml");
		rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game3.xml");
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==2){
		rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game3.xml");
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==1){
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==0){
		saveFile(game, savePath);
	}
	return;
}


void gameWindowHide(GameWindow* gw){
	SDL_HideWindow(gw->window);
}

void gameWindowShow(GameWindow* gw){
	SDL_ShowWindow(gw->window);
}
