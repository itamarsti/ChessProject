/*
 * settingsWindowGUI.c
 *
 *  Created on: 12 ����� 2017
 *      Author: Itamar
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "settingsWindowGUI.h"
#include "boardFuncs.h"

bool isClickOnGameMode1(int x, int y){return true;}
bool isClickOnGameMode2(int x, int y){return true;}
bool isClickOnColWhite(int x, int y){return true;}
bool isClickOnColBlack(int x, int y){return true;}
bool isClickOnNoob(int x, int y){return true;}
bool isClickOnEasy(int x, int y){return true;}
bool isClickOnModerate(int x, int y){return true;}
bool isClickOnHard(int x, int y){return true;}
bool isClickOnExpert(int x, int y){return true;}
bool isClickOnPlay(int x, int y){return true;}
bool isClickOnBack(int x, int y){return true;}


void destroySettingsWindow(SettingsWindow* sw){
	if (sw==NULL) return;
	if (sw->window != NULL) SDL_DestroyWindow(sw->window);
	if (sw->renderer!=NULL) SDL_DestroyRenderer(sw->renderer);
	if (sw->bg!=NULL) SDL_DestroyTexture(sw->bg);
	if (sw->settings!=NULL) SDL_DestroyTexture(sw->settings);
	if (sw->gameMode1!=NULL) SDL_DestroyTexture(sw->gameMode1);
	if (sw->gameMode2!=NULL) SDL_DestroyTexture(sw->gameMode2);
	if (sw->colWhite!=NULL) SDL_DestroyTexture(sw->colWhite);
	if (sw->colBlack!=NULL) SDL_DestroyTexture(sw->colBlack);
	if (sw->difficulty!=NULL) SDL_DestroyTexture(sw->difficulty);
	if (sw->noob!=NULL) SDL_DestroyTexture(sw->noob);
	if (sw->easy!=NULL) SDL_DestroyTexture(sw->easy);
	if (sw->moderate!=NULL) SDL_DestroyTexture(sw->moderate);
	if (sw->hard!=NULL) SDL_DestroyTexture(sw->hard);
	if (sw->back!=NULL) SDL_DestroyTexture(sw->back);
	if (sw->start!=NULL) SDL_DestroyTexture(sw->start);
	free(sw);
}

SettingsWindow* createSW(){
	SettingsWindow* sw = (SettingsWindow*) malloc(sizeof(SettingsWindow));
	SDL_Surface* surface = NULL;
	if(sw==NULL){
		printf("Couldn't create SettingsWindow struct\n");
		return NULL ;
	}
	sw->window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000, 650, SDL_WINDOW_OPENGL);
	if (sw->window==NULL){
		printf("Could not create window: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	// creating the Settings Window renderer
	sw->renderer = SDL_CreateRenderer(sw->window, -1, SDL_RENDERER_ACCELERATED);
	if (sw->renderer==NULL) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/settingsWindow.bmp");
	if (surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	sw->bg = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->bg==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a settings texture:
	/*
	 *
	 *
	 *
	surface = SDL_LoadBMP("./utilities/settings.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->settings = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->settings==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a gameMode1 texture:

	surface = SDL_LoadBMP("./utilities/gameMode1.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->gameMode1 = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->gameMode1==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a gameMode2 texture:
	surface = SDL_LoadBMP("./utilities/gameMode2.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->gameMode2 = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->gameMode2==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a colWhite texture:
	surface = SDL_LoadBMP("./utilities/colWhite.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->colWhite = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->colWhite==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a colBlack texture:
	surface = SDL_LoadBMP("./utilities/colBlack.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->colBlack = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->colBlack==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a difficulty texture:
	surface = SDL_LoadBMP("./utilities/difficulty.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->difficulty = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->difficulty==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a noob texture:
	surface = SDL_LoadBMP("./utilities/noob.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->noob = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->noob==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a easy texture:
	surface = SDL_LoadBMP("./utilities/easy.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->easy = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->easy==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a moderate texture:
	surface = SDL_LoadBMP("./utilities/moderate.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->moderate = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->moderate==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a hard texture:
	surface = SDL_LoadBMP("./utilities/hard.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->hard = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->hard==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a back texture:
	surface = SDL_LoadBMP("./utilities/back.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->back = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->back==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a start texture:
	surface = SDL_LoadBMP("./utilities/start.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->start = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->start==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	*/
	return sw;
}



void settingsWindowHide(SettingsWindow* sw) {
	SDL_HideWindow(sw->window);
}

void settingsWindowShow(SettingsWindow* sw) {
	SDL_ShowWindow(sw->window);
}


SETTINGS_WINDOW_EVENT settingsWindowHandleEvent(SettingsWindow* sw, SDL_Event* event) {
	if (event == NULL || sw == NULL ) {
		return SETTINGS_WINDOW_INVALID;
	}
	switch (event->type) {
		case SDL_MOUSEBUTTONUP:
			if(isClickOnGameMode1(event->button.x,event->button.y)){
				return SETTINGS_WINDOW_GAME_MODE_1;
			}
			else if(isClickOnGameMode2(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_GAME_MODE_2;
			}
			else if(isClickOnColWhite(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_COL_WHITE;
			}
			else if(isClickOnColBlack(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_COL_BLACK;
			}
			else if(isClickOnNoob(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_COL_DIFFICULTY_1;
			}
			else if(isClickOnEasy(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_COL_DIFFICULTY_2;
			}
			else if(isClickOnModerate(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_COL_DIFFICULTY_3;
			}
			else if(isClickOnHard(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_COL_DIFFICULTY_4;
			}
			else if(isClickOnExpert(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_COL_DIFFICULTY_5;
			}
			else if(isClickOnPlay(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_PLAY;
			}
			else if(isClickOnBack(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_BACK;
			}
			break;
		case SDL_WINDOWEVENT:
			if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
				return SETTINGS_WINDOW_EVENT_QUIT;
			}
			break;
		default:
			return SETTINGS_WINDOW_EVENT_NONE;
		}
	return SETTINGS_WINDOW_EVENT_NONE;
}

void drawSettingsWindow(SettingsWindow* sw){
	if(sw==NULL){
			printf("sw is NULL");
			return;
		}
	assert(sw->window != NULL);	assert(sw->renderer!=NULL); assert(sw->bg!=NULL);
	//assert(sw->back!=NULL);	assert(sw->colBlack!=NULL);	assert(sw->colWhite!=NULL);
	//assert(sw->difficulty!=NULL); assert(sw->easy!=NULL); assert(sw->gameMode1!=NULL);
	//assert(sw->gameMode2!=NULL); assert(sw->hard!=NULL); assert(sw->moderate!=NULL);
	//assert(sw->noob!=NULL);	assert(sw->settings!=NULL); assert(sw->start!=NULL);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_SetRenderDrawColor(sw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(sw->renderer);
	SDL_RenderCopy(sw->renderer, sw->bg, NULL, &rec);
	SDL_RenderPresent(sw->renderer);
}


