/*
 * loadWindowGUI.c
 *
 *  Created on: 17 בספט׳ 2017
 *      Author: Itamar
 */

#include "loadWindowGUI.h"
#include <assert.h>



LoadWindow* createLW(int slotsNum){
	printf("inside create LW\n");
	LoadWindow* lw = (LoadWindow*) malloc(sizeof(LoadWindow));
	if(lw==NULL){
		printf("Couldn't create LoadWindow struct\n");
		return NULL;
	}
	lw->window = (SDL_Window*) SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1000, 650, SDL_WINDOW_OPENGL);
	if(lw->window==NULL){
		printf("Couldn't create LW window\n");
		free(lw);
		return NULL;
	}


	int numFiles = numOfFilesInDir();
	printf("before create LR\n");
	createLR(lw,numFiles,false,0,false);
	printf("after create LR\n");
	return lw;
}


void createLR(LoadWindow* lw, int slotsNum, bool backLight, int slotLight, bool loadLight){
	assert(slotsNum>=0); assert(slotsNum<=5); assert(slotLight>=0); assert(slotLight<=5);
	assert(lw!=NULL); assert(lw->window!=NULL);
	SDL_Surface* surface = NULL;
	printf("inside LW func\n");
	if(lw->renderer==NULL) printf("renderer is null");
	SDL_RenderClear(lw->renderer);
	printf("after clear LW func\n");

	// creating the load Window renderer
	if(lw->renderer!=NULL) SDL_DestroyRenderer(lw->renderer);
	lw->renderer = SDL_CreateRenderer(lw->window, -1, SDL_RENDERER_ACCELERATED);
	if (lw->renderer==NULL) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return ;
	}
	//Creating a background texture:
	//if(lw->bg!=NULL) SDL_DestroyTexture(lw->bg);

	surface= SDL_LoadBMP("./utilities/loadWindow/anotherBackground.bmp");
	if (surface==NULL){
		printf("Could not create a bg surface: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	lw->bg = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->bg==NULL){
		printf("Could not create a bg texture: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	SDL_FreeSurface(surface);
	printf("after creating bg load\n");


	//Creating a back texture:
	if(backLight) surface = SDL_LoadBMP("./utilities/loadWindow/backNewClicked.bmp");
	else if(!backLight) surface = SDL_LoadBMP("./utilities/loadWindow/backNew.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	lw->back = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->back==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a load texture:
	if((loadLight)&& (slotLight!=0)) surface = SDL_LoadBMP("./utilities/loadWindow/loadNewClicked.bmp");
	else surface = SDL_LoadBMP("./utilities/loadWindow/loadNew.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	lw->load = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->load==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating slot1 texture:
	if(slotsNum>=1){
		if(slotLight==1) surface = SDL_LoadBMP("./utilities/loadWindow/slot1Clicked.bmp");
		else if(slotLight!=1) surface = SDL_LoadBMP("./utilities/loadWindow/slot1.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot1 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot1==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return;
		}
		SDL_FreeSurface(surface);
	}


	//Creating slot2 texture:

	if(slotsNum>=2){
		if(slotLight==2) surface = SDL_LoadBMP("./utilities/loadWindow/slot2Clicked.bmp");
		else if(slotLight!=2) surface = SDL_LoadBMP("./utilities/loadWindow/slot2.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot2 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot2==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return;
		}
		SDL_FreeSurface(surface);
	}

	//Creating slot3 texture:

	if(slotsNum>=3){
		if(slotLight==3) surface = SDL_LoadBMP("./utilities/loadWindow/slot3Clicked.bmp");
		else if(slotLight!=3) surface = SDL_LoadBMP("./utilities/loadWindow/slot3.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot3 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot3==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return;
		}
		SDL_FreeSurface(surface);
	}

	//Creating slot4 texture:

	if(slotsNum>=4){
		if(slotLight==4) surface = SDL_LoadBMP("./utilities/loadWindow/slot4Clicked.bmp");
		else if(slotLight!=4) surface = SDL_LoadBMP("./utilities/loadWindow/slot4.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot4 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot4==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return;
		}
		SDL_FreeSurface(surface);
	}

	//Creating slot5 texture:

	if(slotsNum>=5){
		if(slotLight==5) surface = SDL_LoadBMP("./utilities/loadWindow/slot5Clicked.bmp");
		else if(slotLight!=5) surface = SDL_LoadBMP("./utilities/loadWindow/slot5.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot5 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot5==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return;
		}
		SDL_FreeSurface(surface);
	}
}


void destroyLoadWindow(LoadWindow* lw){
	printf("in destroy load window\n");
	int filesNum = numOfFilesInDir();
	if(lw==NULL) return;
	if(filesNum>=1){
		if(lw->slot1!=NULL) SDL_DestroyTexture(lw->slot1);
	}
	if(filesNum>=2){
		if(lw->slot2!=NULL) SDL_DestroyTexture(lw->slot2);
	}
	if(filesNum>=3){
		if(lw->slot3!=NULL) SDL_DestroyTexture(lw->slot3);
	}
	if(filesNum>=4){
		if(lw->slot4!=NULL) SDL_DestroyTexture(lw->slot4);
	}
	if(filesNum>=5){
		if(lw->slot5!=NULL) SDL_DestroyTexture(lw->slot5);
	}
	if(lw->back!=NULL) SDL_DestroyTexture(lw->back);
	printf("after destroying the back\n");
	if(lw->load!=NULL) SDL_DestroyTexture(lw->load);
	printf("after destroying the load\n");
	if(lw->bg!=NULL) SDL_DestroyTexture(lw->bg);
	printf("after destroying the bg\n");
	if(lw->renderer!=NULL) SDL_DestroyRenderer(lw->renderer);
	printf("after destroying the renderer\n");
	if(lw->window!=NULL) SDL_DestroyWindow(lw->window);
	printf("after destroying the window\n");
	free(lw);
	printf("ends destroy load window\n");
	return;
}

void destroyLoadRenderer(LoadWindow* lw){
	printf("in destroy load renderer\n");
	if(lw==NULL) return;
	if(lw->window!=NULL) return;
	if(lw->bg!=NULL) SDL_DestroyTexture(lw->bg);
	if(lw->back!=NULL) SDL_DestroyTexture(lw->back);
	if(lw->load!=NULL) SDL_DestroyTexture(lw->load);
	if(lw->slot1!=NULL) SDL_DestroyTexture(lw->slot1);
	if(lw->slot2!=NULL) SDL_DestroyTexture(lw->slot2);
	if(lw->slot3!=NULL) SDL_DestroyTexture(lw->slot3);
	if(lw->slot4!=NULL) SDL_DestroyTexture(lw->slot4);
	if(lw->slot5!=NULL) SDL_DestroyTexture(lw->slot5);
	if(lw->renderer!=NULL) SDL_DestroyRenderer(lw->renderer);

	return;
}
void drawLoadWindow(LoadWindow* lw, int slotsNum){
	//printf("in draw loadWindow\n");
	if(lw==NULL){
		printf("lw is null in draw");
		return;
	}
	assert(lw->window!=NULL); //assert(lw->bg!=NULL);
	assert(lw->back!=NULL); assert(lw->renderer!=NULL); assert(lw->load!=NULL);
	//printf("passed the asserts of lw draw\n");
	if(slotsNum>=1) assert(lw->slot1!=NULL);
	if(slotsNum>=2) assert(lw->slot2!=NULL);
	if(slotsNum>=3) assert(lw->slot3!=NULL);
	if(slotsNum>=4) assert(lw->slot4!=NULL);
	if(slotsNum>=5) assert(lw->slot5!=NULL);
	SDL_SetRenderDrawColor(lw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(lw->renderer);
	//printf("till here again\n");
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_RenderCopy(lw->renderer, lw->bg, NULL, &rec);
	//printf("till here again2\n");

	if(slotsNum>=1) {
		rec.x = 400; rec.y = 120;rec.w = 198; rec.h = 56;	//slot1 message
		SDL_RenderCopy(lw->renderer, lw->slot1, NULL, &rec);
	}

	if(slotsNum>=2){
		rec.x = 400; rec.y = 191;rec.w = 200; rec.h = 58;	//slot2 message
		SDL_RenderCopy(lw->renderer, lw->slot2, NULL, &rec);
	}
	if(slotsNum>=3){
		rec.x = 400; rec.y = 264;rec.w = 200; rec.h = 56;	//slot3 message
		SDL_RenderCopy(lw->renderer, lw->slot3, NULL, &rec);
	}
	if(slotsNum>=4){
		rec.x = 400; rec.y = 335;rec.w = 198; rec.h = 56;	//slot4 message
		SDL_RenderCopy(lw->renderer, lw->slot4, NULL, &rec);
	}
	if(slotsNum>=5){
		rec.x = 400; rec.y = 406;rec.w = 198; rec.h = 54;	//slot5 message
		SDL_RenderCopy(lw->renderer, lw->slot5, NULL, &rec);
	}

	//printf("ready to set load in lw draw\n");
	rec.x = 750; rec.y = 100;rec.w = 160; rec.h = 88;	//load message
	SDL_RenderCopy(lw->renderer, lw->load, NULL, &rec);
	//printf("ready to set back in lw draw\n");
	rec.x = 750; rec.y = 250;rec.w = 162; rec.h = 88;	//back message
	SDL_RenderCopy(lw->renderer, lw->back, NULL, &rec);
	//printf("the end of lw draw");
	SDL_RenderPresent(lw->renderer);
}

int numOfFilesInDir(){
	DIR *dir;
	struct dirent *ent;
	int counter = 0;
	if ((dir = opendir ("./utilities/loadedGames")) != NULL) {
		readdir (dir);
		readdir (dir);
	  /* counting all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
		  counter++;
	  }
	  closedir (dir);
	  return counter;
	}
	else {
		printf("error");
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
	free(ent);
}

void loadFilePath(boardGame*board, char* path){
	assert(board!=NULL); assert(board->boardArr!=NULL); assert(path!=NULL);
	printf("path is:%s\n",path);
	FILE* file = (FILE*) fopen(path,"r");
	assert(file!=NULL);
	char buffer[1024];
	char* token;
	fscanf(file, "%[^\n]\n", buffer);	//xml version & encoding
	fscanf(file, "%[^\n]\n", buffer); 	//	game
	fscanf(file, "%[^\n]\n", buffer);	//current turn
	board->curPlayer = (int) buffer[14]-'0';
	fscanf(file, "%[^\n]\n", buffer);	//game mode
	board->gameMode = (int) buffer[11]-'0';
	if(board->gameMode==1){
		fscanf(file, "%[^\n]\n", buffer);	//difficulty turn
		token = strtok(buffer," <>");
		if(strcmp(token,"difficulty ")){
			int difficulty = (int)buffer[12]-'0';
			board->diffLevel = difficulty;
		}
		fscanf(file, "%[^\n]\n", buffer);	//game_color turn
		token = strtok(buffer," <>");
		if(strcmp(token,"game_color ")){
			int gameCol = (int)buffer[12]-'0';
			board->userCol = gameCol;
		}
	}
	fscanf(file, "%[^\n]\n", buffer);	//board
	for(int i=0;i<ROW;i++){
		fscanf(file, "%[^\n]\n", buffer); //row
		for(int j=7;j<7+COL;j++){
			board->boardArr[i][j-7] = (char)buffer[j];
		}
	}
	fclose(file);
}

void loadRemoveChangeFile(int numOfFiles, int fileDeleted,boardGame* game, LoadWindow* lw){
	assert(game!=NULL); assert(game->boardArr!=NULL);
	assert(lw!=NULL); assert(lw->window!=NULL);
	if(numOfFiles==0||fileDeleted==0) return;
	if(fileDeleted==1){
		loadFilePath(game,"./utilities/loadedGames/game1.xml");
		remove("./utilities/loadedGames/game1.xml");
	}
	else if(fileDeleted==2){
		loadFilePath(game, "./utilities/loadedGames/game2.xml");
		remove("./utilities/loadedGames/game2.xml");
	}
	else if(fileDeleted==3){
		loadFilePath(game, "./utilities/loadedGames/game3.xml");
		remove("./utilities/loadedGames/game3.xml");
	}
	else if(fileDeleted==4){
		loadFilePath(game, "./utilities/loadedGames/game4.xml");
		remove("./utilities/loadedGames/game4.xml");
	}
	else if(fileDeleted==5){
		loadFilePath(game, "./utilities/loadedGames/game5.xml");
		remove("./utilities/loadedGames/game5.xml");
	}

	if(numOfFiles==5){
		if (fileDeleted<=1)	rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game1.xml");
		if (fileDeleted<=2)	rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game2.xml");
		if (fileDeleted<=3)	rename("./utilities/loadedGames/game4.xml","./utilities/loadedGames/game3.xml");
		if (fileDeleted<=4) rename("./utilities/loadedGames/game5.xml","./utilities/loadedGames/game4.xml");
		if(lw->slot5!=NULL) SDL_DestroyTexture(lw->slot5);
	}
	else if (numOfFiles==4){
		if (fileDeleted<=1)	rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game1.xml");
		if (fileDeleted<=2)	rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game2.xml");
		if (fileDeleted<=3)	rename("./utilities/loadedGames/game4.xml","./utilities/loadedGames/game3.xml");
		if(lw->slot4!=NULL) SDL_DestroyTexture(lw->slot4);
	}
	else if (numOfFiles==3){
		if (fileDeleted<=1)	rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game1.xml");
		if (fileDeleted<=2)	rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game2.xml");
		if(lw->slot3!=NULL) SDL_DestroyTexture(lw->slot3);
	}
	else if (numOfFiles==2){
		if (fileDeleted<=1)	rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game1.xml");
		if(lw->slot2!=NULL) SDL_DestroyTexture(lw->slot2);
	}
	else if (numOfFiles==1){
		if(lw->slot1!=NULL) SDL_DestroyTexture(lw->slot1);
	}
	return;
}


LOAD_WINDOW_EVENT loadWindowHandleEvent(LoadWindow* lw, SDL_Event* event){
	if((lw==NULL)|| (event==NULL)){
		return LOAD_WINDOW_INVALID;
	}
	switch (event->type){
		case SDL_MOUSEBUTTONUP:
			if(isClickOnSlot1(event->button.x,event->button.y)){
				return LOAD_WINDOW_GAME1SLOT;
			}
			else if(isClickOnSlot2(event->button.x,event->button.y)){
				return LOAD_WINDOW_GAME2SLOT;
			}
			else if(isClickOnSlot3(event->button.x,event->button.y)){
				return LOAD_WINDOW_GAME3SLOT;
			}
			else if(isClickOnSlot4(event->button.x,event->button.y)){
				return LOAD_WINDOW_GAME4SLOT;
			}
			else if(isClickOnSlot5(event->button.x,event->button.y)){
				return LOAD_WINDOW_GAME5SLOT;
			}
			else if(isClickOnLWLoad(event->button.x,event->button.y)){
				return LOAD_WINDOW_PUSH_LOAD;
			}
			else if(isClickOnLWBack(event->button.x,event->button.y)){
				return LOAD_WINDOW_PUSH_BACK;
			}
			break;
		case SDL_MOUSEMOTION:
			if(isClickOnLWLoad(event->motion.x,event->motion.y)){
				return LOAD_WINDOW_HOVER_LOAD;
			}
			else if(isClickOnLWBack(event->motion.x,event->motion.y)){
				return LOAD_WINDOW_HOVER_BACK;
			}
			break;
		case SDL_WINDOWEVENT:
			if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
				return LOAD_WINDOW_EVENT_QUIT;
			}
			break;
		default:
			return LOAD_WINDOW_EVENT_NONE;
		}
	return LOAD_WINDOW_EVENT_NONE;
	}



bool isClickOnSlot1(int x, int y){
	if((x>=400&& x<=598) && (y>=120&& y<=176)) return true;
	return false;
}

bool isClickOnSlot2(int x, int y){
	if((x>=400&& x<=600) && (y>=191&& y<=249)) return true;
	return false;
}

bool isClickOnSlot3(int x, int y){
	if((x>=400&& x<=600) && (y>=264 && y<=320)) return true;
	return false;
}

bool isClickOnSlot4(int x, int y){
	if((x>=400&& x<=598) && (y>=335&& y<=391)) return true;
	return false;
}

bool isClickOnSlot5(int x, int y){
	if((x>=400&& x<=598) && (y>=406&& y<=460)) return true;
	return false;
}

bool isClickOnLWLoad(int x, int y){
	if((x>=750&& x<=910) && (y>=100&& y<=188)) return true;
	return false;
}

bool isClickOnLWBack(int x, int y){
	if((x>=750&& x<=912) && (y>=250&& y<=338)) return true;
	return false;
}

void loadWindowHide(LoadWindow* lw){
	assert(lw!=NULL); assert(lw->window!=NULL);
	SDL_HideWindow(lw->window);
}

void loadWindowShow(LoadWindow* lw){
	assert(lw!=NULL); assert(lw->window!=NULL);
	SDL_ShowWindow(lw->window);
}



