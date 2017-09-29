/*
 * settingsWindowGUI.c
 *
 *  Created on: 12 בספט׳ 2017
 *      Author: Itamar
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "settingsWindowGUI.h"
#include "boardFuncs.h"




bool isClickOnGameMode1(int x, int y){
	if((x>=520&& x<=710) && (y>=20&& y<=104)) return true;
	return false;
}

bool isClickOnGameMode2(int x, int y){
	if((x>=750&& x<=940) && (y>=20&& y<=104)) return true;
	return false;
}

bool isClickOnColWhite(int x, int y){
	if((x>=520&& x<=710) && (y>=130&& y<=214)) return true;
	return false;
}

bool isClickOnColBlack(int x, int y){
	if((x>=750&& x<=940) && (y>=130&& y<=214)) return true;
	return false;
}


bool isClickOnNoob(int x, int y){
	if((x>=340&& x<=466) && (y>=340&& y<=462)) return true;
	return false;
}

bool isClickOnEasy(int x, int y){
	if((x>=495&& x<=623) && (y>=340&& y<=462)) return true;
	return false;
}

bool isClickOnModerate(int x, int y){
	if((x>=650&& x<=774) && (y>=340&& y<=462)) return true;
	return false;
}

bool isClickOnHard(int x, int y){
	if((x>=805&& x<=931) && (y>=340&& y<=462)) return true;
	return false;
}

//bool isClickOnExpert(int x, int y){return true;}
bool isClickOnStart(int x, int y){
	if((x>=410&& x<=536) && (y>=505 && y<=627)) return true;
		return false;
}



bool isClickOnBack(int x, int y){
	if((x>=720&& x<=846) && (y>=505 && y<=625)) return true;
	return false;
}


void destroySettingsWindow(SettingsWindow* sw){
	//printf("inside destroy settings\n");
	if (sw==NULL) return;
	if (sw->gameMode1!=NULL) SDL_DestroyTexture(sw->gameMode1);
	//printf("destroying mode1\n");
	if(sw->gameMode2!=NULL) SDL_DestroyTexture(sw->gameMode2);
	//printf("destroying mode2\n");
	if (sw->bg!=NULL) SDL_DestroyTexture(sw->bg);
	//printf("destroying bg\n");
	if (sw->color!=NULL) SDL_DestroyTexture(sw->color);
	//printf("destroying color\n");
	if (sw->mode!=NULL) SDL_DestroyTexture(sw->mode);
	//printf("destroying mode\n");
	if (sw->colWhite!=NULL) SDL_DestroyTexture(sw->colWhite);
	//printf("destroying white\n");
	if (sw->colBlack!=NULL) SDL_DestroyTexture(sw->colBlack);
	//printf("destroying black\n");
	if (sw->difficulty!=NULL) SDL_DestroyTexture(sw->difficulty);
	//printf("destroying diffi\n");
	if (sw->noob!=NULL) SDL_DestroyTexture(sw->noob);
	//printf("destroying noob\n");
	if (sw->easy!=NULL) SDL_DestroyTexture(sw->easy);
	//printf("destroying easy\n");
	if (sw->moderate!=NULL) SDL_DestroyTexture(sw->moderate);
	//printf("destroying moderate\n");
	if (sw->hard!=NULL) SDL_DestroyTexture(sw->hard);
	//printf("destroying hard\n");
	if (sw->back!=NULL) SDL_DestroyTexture(sw->back);
	//printf("destroying back\n");
	if (sw->start!=NULL) SDL_DestroyTexture(sw->start);
	//printf("destroying start\n");
	if (sw->renderer!=NULL) SDL_DestroyRenderer(sw->renderer);
	//printf("destroying renderer\n");
	if (sw->window != NULL) SDL_DestroyWindow(sw->window);
	//printf("destroying window\n");
	//printf("the end of destroy settings window\n");
	free(sw);
}


void destroySettingsRenderer(SettingsWindow* sw){
	if (sw==NULL) return;
	if (sw->window == NULL)return;
	if (sw->renderer!=NULL) SDL_DestroyRenderer(sw->renderer);
	if (sw->bg!=NULL) SDL_DestroyTexture(sw->bg);
	if (sw->color!=NULL) SDL_DestroyTexture(sw->color);
	if (sw->mode!=NULL) SDL_DestroyTexture(sw->mode);
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
}

SettingsWindow* createSR(SettingsWindow* sw, int numPlayers, int color, int diffi){
	assert(sw!=NULL); assert(sw->window!=NULL);
	SDL_Surface* surface = NULL;
	// creating the Settings Window renderer
	sw->renderer = SDL_CreateRenderer(sw->window, -1, SDL_RENDERER_ACCELERATED);
	if (sw->renderer==NULL) {
		printf("Could not create a renderer in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/settingsWindow/settingsBackground.bmp");
	if (surface==NULL){
		printf("Could not create a bg surface in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	sw->bg = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->bg==NULL){
		printf("Could not create a bg texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a mode texture:
	surface = SDL_LoadBMP("./utilities/settingsWindow/mode.bmp");
	if(surface==NULL){
		printf("Could not create a mode surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->mode = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->mode==NULL){
		printf("Could not create a mode texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a gameMode1 texture:
	if(numPlayers==1)surface = SDL_LoadBMP("./utilities/settingsWindow/gameMode1Clicked.bmp");
	else if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/gameMode1.bmp");
	if(surface==NULL){
		printf("Could not create a mode1 surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->gameMode1 = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->gameMode1==NULL){
		printf("Could not create a mode1 texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a gameMode2 texture:
	if(numPlayers==1)surface = SDL_LoadBMP("./utilities/settingsWindow/gameMode2.bmp");
	else if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/gameMode2Clicked.bmp");
	if(surface==NULL){
		printf("Could not create a mode2 surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->gameMode2 = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->gameMode2==NULL){
		printf("Could not create a mode2 texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a color texture:
	surface = SDL_LoadBMP("./utilities/settingsWindow/color.bmp");
	if(surface==NULL){
		printf("Could not create a color surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->color = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->color==NULL){
		printf("Could not create a color texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a colWhite texture:
	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/white.bmp");
	else if (numPlayers==1){
		if(color==0) surface = SDL_LoadBMP("./utilities/settingsWindow/white.bmp");
		else if(color==1) surface = SDL_LoadBMP("./utilities/settingsWindow/whiteClicked.bmp");
	}
	if(surface==NULL){
		printf("Could not create a white surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->colWhite = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->colWhite==NULL){
		printf("Could not create a white texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a colBlack texture:
	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/black.bmp");
	else if (numPlayers==1){
		if(color==0) surface = SDL_LoadBMP("./utilities/settingsWindow/blackClicked.bmp");
		else if(color==1) surface = SDL_LoadBMP("./utilities/settingsWindow/black.bmp");
	}
	if(surface==NULL){
		printf("Could not create a black surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->colBlack = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->colBlack==NULL){
		printf("Could not create a black texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a difficulty texture:
	surface = SDL_LoadBMP("./utilities/settingsWindow/difficulty.bmp");
	if(surface==NULL){
		printf("Could not create a difficulty surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->difficulty = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->difficulty==NULL){
		printf("Could not create a difficulty texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a noob texture:
	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/noob.bmp");
	else if (numPlayers==1){
		if(diffi==1) surface = SDL_LoadBMP("./utilities/settingsWindow/noobClicked.bmp");
		else surface = SDL_LoadBMP("./utilities/settingsWindow/noob.bmp");
	}
	if(surface==NULL){
		printf("Could not create a noob surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->noob = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->noob==NULL){
		printf("Could not create a noob texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a easy texture:
	if(numPlayers==2) 	surface = SDL_LoadBMP("./utilities/settingsWindow/easy.bmp");
	else if (numPlayers==1){
		if(diffi==2) surface = SDL_LoadBMP("./utilities/settingsWindow/easyClicked.bmp");
		else surface = SDL_LoadBMP("./utilities/settingsWindow/easy.bmp");
	}
	if(surface==NULL){
		printf("Could not create a easy surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->easy = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->easy==NULL){
		printf("Could not create a easy texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a moderate texture:

	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/moderate.bmp");
	else if (numPlayers==1){
		if(diffi==3) surface = SDL_LoadBMP("./utilities/settingsWindow/moderateClicked.bmp");
		else surface = SDL_LoadBMP("./utilities/settingsWindow/moderate.bmp");
	}
	if(surface==NULL){
		printf("Could not create a moderate surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->moderate = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->moderate==NULL){
		printf("Could not create a moderate texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);


	//Creating a hard texture:

	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/hard.bmp");
	else if (numPlayers==1){
		if(diffi==4) surface = SDL_LoadBMP("./utilities/settingsWindow/hardClicked.bmp");
		else surface = SDL_LoadBMP("./utilities/settingsWindow/hard.bmp");
	}
	if(surface==NULL){
		printf("Could not create a hard surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->hard = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->hard==NULL){
		printf("Could not create a hard texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating an expert texture:
/*
	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/expert.bmp");
	else if (numPlayers==1){
		if(diffi==5) surface = SDL_LoadBMP("./utilities/settingsWindow/expertClicked.bmp");
		else surface = SDL_LoadBMP("./utilities/expert.bmp");
	}
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->expert = SDL_CreateTextureFromSurface(expert->renderer, surface);
	if (sw->expert==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);
*/

	//Creating a back texture:
	surface = SDL_LoadBMP("./utilities/settingsWindow/backClicked.bmp");
	if(surface==NULL){
		printf("Could not create a back surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->back = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->back==NULL){
		printf("Could not create a back texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	//Creating a start texture:

	surface = SDL_LoadBMP("./utilities/settingsWindow/startClicked.bmp");
	if(surface==NULL){
		printf("Could not create a start surface in SettingsWindow: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->start = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->start==NULL){
		printf("Could not create a back texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	return sw;
}


SettingsWindow* createSW(int numPlayers, int color, int diffi){
	SettingsWindow* sw = (SettingsWindow*) malloc(sizeof(SettingsWindow));
	if(sw==NULL){
		printf("Couldn't create SettingsWindow struct in SettingsWindow\n");
		return NULL ;
	}
	sw->window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000, 650, SDL_WINDOW_OPENGL);
	if (sw->window==NULL){
		printf("Could not create window in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return NULL ;
	}
	createSR(sw, numPlayers, color, diffi);
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
			/*
			else if(isClickOnExpert(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_COL_DIFFICULTY_5;
			}
			*/
			else if(isClickOnBack(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_PUSH_BACK;
			}
			else if(isClickOnStart(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_PUSH_START;
			}
			break;
		/*
		case SDL_MOUSEMOTION:
			if(isClickOnBack(event->motion.x, event->motion.y)){
				return SETTINGS_WINDOW_HOVER_BACK;
			}
			else if(isClickOnStart(event->button.x, event->button.y)){
				return SETTINGS_WINDOW_HOVER_START;
			}
			break;
			*/
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
			printf("ERROR: SettingsWindow is NULL");
			return;
	}
	assert(sw->window != NULL);	assert(sw->renderer!=NULL); assert(sw->bg!=NULL);
	assert(sw->back!=NULL); assert(sw->start!=NULL);
	assert(sw->mode!=NULL); assert(sw->color!=NULL); assert(sw->difficulty!=NULL);
	assert(sw->gameMode2!=NULL); assert(sw->gameMode1!=NULL); assert(sw->easy!=NULL);
	assert(sw->colBlack!=NULL);	assert(sw->colWhite!=NULL); assert(sw->noob!=NULL);
	assert(sw->hard!=NULL); assert(sw->moderate!=NULL);

	SDL_RenderClear(sw->renderer);
	SDL_SetRenderDrawColor(sw->renderer, 255, 255, 255, 255);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_RenderCopy(sw->renderer, sw->bg, NULL, &rec);
	rec.x = 300; rec.y = 30;rec.w = 162; rec.h = 72;	//mode message
	SDL_RenderCopy(sw->renderer, sw->mode, NULL, &rec);
	rec.x = 300; rec.y = 135;rec.w = 158; rec.h = 72;	//color message
	SDL_RenderCopy(sw->renderer, sw->color, NULL, &rec);
	rec.x = 285; rec.y = 230;rec.w = 240; rec.h = 88;	//difficulty message
	SDL_RenderCopy(sw->renderer, sw->difficulty, NULL, &rec);
	rec.x = 520; rec.y = 20;rec.w = 190; rec.h = 84;	//gameMode1 message
	SDL_RenderCopy(sw->renderer, sw->gameMode1, NULL, &rec);
	rec.x = 750; rec.y = 20;rec.w = 190; rec.h = 84;	//gameMode2 message
	SDL_RenderCopy(sw->renderer, sw->gameMode2, NULL, &rec);
	rec.x = 520; rec.y = 130;rec.w = 190; rec.h = 84;	//white message
	SDL_RenderCopy(sw->renderer, sw->colWhite, NULL, &rec);
	rec.x = 750; rec.y = 130;rec.w = 190; rec.h = 84;	//black message
	SDL_RenderCopy(sw->renderer, sw->colBlack, NULL, &rec);
	rec.x = 340; rec.y = 340;rec.w = 126; rec.h = 122;	//noob message
	SDL_RenderCopy(sw->renderer, sw->noob, NULL, &rec);
	rec.x = 495; rec.y = 340;rec.w = 128; rec.h = 122;	//easy message
	SDL_RenderCopy(sw->renderer, sw->easy, NULL, &rec);
	rec.x = 650; rec.y = 340;rec.w = 124; rec.h = 122;	//moderate message
	SDL_RenderCopy(sw->renderer, sw->moderate, NULL, &rec);
	rec.x = 805; rec.y = 340;rec.w = 126; rec.h = 122;	//hard message
	SDL_RenderCopy(sw->renderer, sw->hard, NULL, &rec);
	rec.x = 720; rec.y = 505;rec.w = 126; rec.h = 120;	//back message
	SDL_RenderCopy(sw->renderer, sw->back, NULL, &rec);
	rec.x = 410; rec.y = 505;rec.w = 126; rec.h = 122;	//start message
	SDL_RenderCopy(sw->renderer, sw->start, NULL, &rec);
	SDL_RenderPresent(sw->renderer);
}

void createGameMode1Texture(SettingsWindow* sw, int numPlayers){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	SDL_DestroyTexture(sw->gameMode1);
	SDL_Surface* surface = NULL;
	if(numPlayers==1)surface = SDL_LoadBMP("./utilities/settingsWindow/gameMode1Clicked.bmp");
	else if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/gameMode1.bmp");
	if(surface==NULL){
		printf("Could not create a mode1 surface in SettingsWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->gameMode1 = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->gameMode1==NULL){
		printf("Could not create a mode1 texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return;
	}
	SDL_FreeSurface(surface);
}

void createGameMode2Texture(SettingsWindow* sw, int numPlayers){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	SDL_DestroyTexture(sw->gameMode2);
	SDL_Surface* surface = NULL;
	if(numPlayers==1)surface = SDL_LoadBMP("./utilities/settingsWindow/gameMode2.bmp");
	else if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/gameMode2Clicked.bmp");
	if(surface==NULL){
		printf("Could not create a mode2 surface in SettingsWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->gameMode2 = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->gameMode2==NULL){
		printf("Could not create a mode2 texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return;
	}
	SDL_FreeSurface(surface);
}

void createGameNoobTexture(SettingsWindow* sw, int numPlayers){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	SDL_DestroyTexture(sw->noob);
	SDL_Surface* surface = NULL;
	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/noob.bmp");
	else if (numPlayers==1)surface = SDL_LoadBMP("./utilities/settingsWindow/noobClicked.bmp");
	if(surface==NULL){
		printf("Could not create a noob surface in SettingsWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->noob = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->noob==NULL){
		printf("Could not create a noob texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return;
	}
	SDL_FreeSurface(surface);
}


void createGameEasyTexture(SettingsWindow* sw, int numPlayers ){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	SDL_DestroyTexture(sw->easy);
	SDL_Surface* surface = NULL;
	if(numPlayers==2) 	surface = SDL_LoadBMP("./utilities/settingsWindow/easy.bmp");
	else if (numPlayers==1) surface = SDL_LoadBMP("./utilities/settingsWindow/easyClicked.bmp");
	if(surface==NULL){
		printf("Could not create a easy surface in SettingsWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->easy = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->easy==NULL){
		printf("Could not create a easy texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return;
	}
	SDL_FreeSurface(surface);
}



void createGameModerateTexture(SettingsWindow* sw, int numPlayers ){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	SDL_DestroyTexture(sw->moderate);
	SDL_Surface* surface = NULL;
	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/moderate.bmp");
	else if (numPlayers==1)surface = SDL_LoadBMP("./utilities/settingsWindow/moderateClicked.bmp");
	if(surface==NULL){
		printf("Could not create a moderate surface in SettingsWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->moderate = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->moderate==NULL){
		printf("Could not create a moderate texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return;
	}
	SDL_FreeSurface(surface);
}



void createGameHardTexture(SettingsWindow* sw, int numPlayers){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	SDL_DestroyTexture(sw->hard);
	SDL_Surface* surface = NULL;
	if(numPlayers==2) surface = SDL_LoadBMP("./utilities/settingsWindow/hard.bmp");
	else if (numPlayers==1)surface = SDL_LoadBMP("./utilities/settingsWindow/hardClicked.bmp");
	if(surface==NULL){
		printf("Could not create a hard surface in SettingsWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->hard = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->hard==NULL){
		printf("Could not create a hard texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return;
	}
	SDL_FreeSurface(surface);
}


void createGameDifficultyDecider(SettingsWindow* sw, int diffiOld, int diffiNew){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	if(diffiOld==0){
		createGameNoobTexture(sw,2);
		createGameEasyTexture(sw,2);
		createGameModerateTexture(sw,2);
		createGameHardTexture(sw,2);
	}
	else{
		if(diffiOld==1) createGameNoobTexture(sw,2);
		else if (diffiOld==2) createGameEasyTexture(sw,2);
		else if (diffiOld==3) createGameModerateTexture(sw,2);
		else if (diffiOld==4) createGameHardTexture(sw,2);
		if(diffiNew==1) createGameNoobTexture(sw,1);
		else if (diffiNew==2) createGameEasyTexture(sw,1);
		else if (diffiNew==3) createGameModerateTexture(sw,1);
		else if (diffiNew==4) createGameHardTexture(sw,1);
	}
}



void createSetWhiteTexture(SettingsWindow* sw, int userCol){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	SDL_DestroyTexture(sw->colWhite);
	SDL_Surface* surface = NULL;
	if(userCol==0) surface = SDL_LoadBMP("./utilities/settingsWindow/white.bmp");
	else if (userCol==1)surface = SDL_LoadBMP("./utilities/settingsWindow/whiteClicked.bmp");
	if(surface==NULL){
		printf("Could not create a white surface in SettingsWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->colWhite = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->colWhite==NULL){
		printf("Could not create a white texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return;
	}
	SDL_FreeSurface(surface);
}


void createSetBlackTexture(SettingsWindow* sw, int userCol){
	assert(sw!=NULL); assert(sw->window!=NULL); assert(sw->renderer!=NULL);
	SDL_DestroyTexture(sw->colBlack);
	SDL_Surface* surface = NULL;
	if(userCol==1) surface = SDL_LoadBMP("./utilities/settingsWindow/black.bmp");
	else if (userCol==0)surface = SDL_LoadBMP("./utilities/settingsWindow/blackClicked.bmp");
	if(surface==NULL){
		printf("Could not create a black surface in SettingsWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	sw->colBlack = SDL_CreateTextureFromSurface(sw->renderer, surface);
	if (sw->colBlack==NULL){
		printf("Could not create a black texture in SettingsWindow: %s\n", SDL_GetError());
		destroySettingsWindow(sw);
		return;
	}
	SDL_FreeSurface(surface);
}







