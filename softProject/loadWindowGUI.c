/*
 * loadWindowGUI.c
 *
 *  Created on: 16 בספט׳ 2017
 *      Author: Itamar
 */

#include "loadWindowGUI.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>



LoadWindow* createLR(LoadWindow* lw, int slotsNum, bool backLightened, int slotLight, bool loadLight){
	//printf("the slots in create LR is: %d", slotsNum);
	assert(lw!=NULL); assert(lw->window!=NULL);
	SDL_Surface* surface = NULL;
	printf("survived surface\n");
	// creating the Settings Window renderer
	lw->renderer = SDL_CreateRenderer(lw->window, -1, SDL_RENDERER_ACCELERATED);
	printf("creating renderer");

	if (lw->renderer==NULL) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return NULL ;
	}
	printf("creating bg");
	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/loadWindow/loadBackground.bmp");
	if (surface==NULL){
		printf("Could not create a bg surface: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return NULL ;
	}
	lw->bg = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->bg==NULL){
		printf("Could not create a bg texture: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return NULL ;
	}
	SDL_FreeSurface(surface);
	printf("till back create\n");
	//Creating back texture:
	if(backLightened) surface = SDL_LoadBMP("./utilities/loadWindow/backClicked.bmp");
	else if(!backLightened) surface = SDL_LoadBMP("./utilities/loadWindow/back.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	lw->back = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->back==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return NULL ;
	}
	SDL_FreeSurface(surface);
	printf("till load create\n");

	//Creating a load texture:
	if(loadLight)surface = SDL_LoadBMP("./utilities/loadWindow/loadClicked.bmp");
	else if(!loadLight)surface = SDL_LoadBMP("./utilities/loadWindow/load.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	lw->load = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->load==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return NULL ;
	}
	SDL_FreeSurface(surface);

	printf("till slot1 create\n");

	//Creating slot1 texture:
	if(slotsNum>0){
		if(slotLight==1) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot1Clicked.bmp");
		else if(slotLight!=1) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot1.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return NULL;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot1 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot1==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return NULL ;
		}
		SDL_FreeSurface(surface);
	}
	printf("till slot2 create\n");

	//Creating slot2 texture:

	if(slotsNum>1){
		if(slotLight==2) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot2Clicked.bmp");
		else if(slotLight!=2) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot2.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return NULL;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot2 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot2==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return NULL ;
		}
		SDL_FreeSurface(surface);
	}

	printf("till slot3 create\n");

	//Creating slot3 texture:

	if(slotsNum>2){
		if(slotLight==3) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot3Clicked.bmp");
		else if(slotLight!=3) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot3.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return NULL;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot3 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot3==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return NULL ;
		}
		SDL_FreeSurface(surface);
	}
	printf("till slot4 create\n");

	//Creating slot4 texture:

	if(slotsNum>3){
		if(slotLight==4) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot4Clicked.bmp");
		else if(slotLight!=4) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot4.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return NULL;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot4 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot4==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return NULL ;
		}
		SDL_FreeSurface(surface);
	}
	printf("till slot5 create\n");

	//Creating slot5 texture:
	if(slotsNum>4){

		if(slotLight==5) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot5Clicked.bmp");
		else if(slotLight!=5) surface = SDL_LoadBMP("./utilities/loadWindow/gameSlot5.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return NULL;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot5= SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot5==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return NULL ;
		}
		SDL_FreeSurface(surface);
	}
	printf("till the end create\n");
	return lw;
}




LoadWindow* createLW(int slotsNum){
	//printf("the slots in create LW is: %d", slotsNum);
	LoadWindow* lw = (LoadWindow*) malloc(sizeof(LoadWindow));
	if(lw==NULL){
		printf("Couldn't create LoadWindow struct\n");
		return NULL ;
	}
	lw->window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000, 650, SDL_WINDOW_OPENGL);
	if (lw->window==NULL){
		printf("Could not create window: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return NULL ;
	}
	createLR(lw,slotsNum,false,0,false);
	return lw;
}



void destroyLoadWindow(LoadWindow* lw){
	if (lw==NULL) return;
	if (lw->window != NULL) SDL_DestroyWindow(lw->window);
	if (lw->renderer!=NULL) SDL_DestroyRenderer(lw->renderer);
	if (lw->bg!=NULL) SDL_DestroyTexture(lw->bg);
	if (lw->slot1!=NULL) SDL_DestroyTexture(lw->slot1);
	if (lw->slot2!=NULL) SDL_DestroyTexture(lw->slot2);
	if (lw->slot3!=NULL) SDL_DestroyTexture(lw->slot3);
	if (lw->slot4!=NULL) SDL_DestroyTexture(lw->slot4);
	if (lw->slot5!=NULL) SDL_DestroyTexture(lw->slot5);
	if (lw->load!=NULL) SDL_DestroyTexture(lw->load);
	if (lw->back!=NULL) SDL_DestroyTexture(lw->back);
	free(lw);
}


void destroyLoadRenderer(LoadWindow* lw){
	if (lw==NULL) return;
	if (lw->window == NULL)return;
	if (lw->bg!=NULL) SDL_DestroyTexture(lw->bg);
	if (lw->back!=NULL) SDL_DestroyTexture(lw->back);
	if (lw->load!=NULL) SDL_DestroyTexture(lw->load);
	if (lw->slot1!=NULL) SDL_DestroyTexture(lw->slot1);
	if (lw->slot2!=NULL) SDL_DestroyTexture(lw->slot2);
	if (lw->slot3!=NULL) SDL_DestroyTexture(lw->slot3);
	if (lw->slot4!=NULL) SDL_DestroyTexture(lw->slot4);
	if (lw->slot5!=NULL) SDL_DestroyTexture(lw->slot5);
	if (lw->renderer!=NULL) SDL_DestroyRenderer(lw->renderer);
}



void drawLoadWindow(LoadWindow* lw, int slotsNum){
	if(lw==NULL){
			printf("lw is NULL");
			return;
	}
	assert(lw->window != NULL);	assert(lw->renderer!=NULL); assert(lw->bg!=NULL);
	assert(lw->load!=NULL); assert(lw->back!=NULL);
	if(slotsNum>0) assert(lw->slot1!=NULL);
	if(slotsNum>1) assert(lw->slot2!=NULL);
	if(slotsNum>2) assert(lw->slot3!=NULL);
	if(slotsNum>3) assert(lw->slot4!=NULL);
	if(slotsNum>4) assert(lw->slot5!=NULL);
	SDL_SetRenderDrawColor(lw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(lw->renderer);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_RenderCopy(lw->renderer, lw->bg, NULL, &rec);
	printf("number of slots is:%d\n", slotsNum);
	if(slotsNum>0) {
		rec.x = 400; rec.y = 120;rec.w = 198; rec.h = 56;	//slot1 message
		SDL_RenderCopy(lw->renderer, lw->slot1, NULL, &rec);
	}
	if(slotsNum>1){
		rec.x = 400; rec.y = 191;rec.w = 200; rec.h = 58;	//slot2 message
		SDL_RenderCopy(lw->renderer, lw->slot2, NULL, &rec);
	}
	if(slotsNum>2){
		rec.x = 400; rec.y = 264;rec.w = 200; rec.h = 56;	//slot3 message
		SDL_RenderCopy(lw->renderer, lw->slot3, NULL, &rec);
	}
	if(slotsNum>3){
		rec.x = 400; rec.y = 335;rec.w = 198; rec.h = 56;	//slot4 message
		SDL_RenderCopy(lw->renderer, lw->slot4, NULL, &rec);
	}
	if(slotsNum>4){
		rec.x = 400; rec.y = 406;rec.w = 198; rec.h = 54;	//slot5 message
		SDL_RenderCopy(lw->renderer, lw->slot5, NULL, &rec);
	}
	rec.x = 750; rec.y = 100;rec.w = 160; rec.h = 88;	//load message
	SDL_RenderCopy(lw->renderer, lw->load, NULL, &rec);

	rec.x = 750; rec.y = 250;rec.w = 162; rec.h = 88;	//back message
	SDL_RenderCopy(lw->renderer, lw->back, NULL, &rec);
	SDL_RenderPresent(lw->renderer);
}


LOAD_WINDOW_EVENT loadWindowHandleEvent(LoadWindow* lw, SDL_Event* event) {
	if (event == NULL || lw == NULL ) {
		return LOAD_WINDOW_INVALID;
	}
	switch (event->type) {
		case SDL_MOUSEBUTTONUP:
			if(isClickOnSlot1(event->button.x,event->button.y)){
				return LOAD_WINDOW_SLOT1;
			}
			else if(isClickOnSlot2(event->button.x, event->button.y)){
				return LOAD_WINDOW_SLOT2;
			}
			else if(isClickOnSlot3(event->button.x, event->button.y)){
				return LOAD_WINDOW_SLOT3;
			}
			else if(isClickOnSlot4(event->button.x, event->button.y)){
				return LOAD_WINDOW_SLOT4;
			}
			else if(isClickOnSlot5(event->button.x, event->button.y)){
				return LOAD_WINDOW_SLOT5;
			}
			else if(isClickOnBackLW(event->button.x, event->button.y)){
				return LOAD_WINDOW_PUSH_BACK;
			}
			else if(isClickOnLoadSlot(event->button.x, event->button.y)){
				return LOAD_WINDOW_PUSH_LOAD;
			}
			break;
		case SDL_MOUSEMOTION:
			if(isClickOnBackLW(event->motion.x, event->motion.y)){
				return LOAD_WINDOW_HOVER_BACK;
			}
			else if(isClickOnLoadSlot(event->motion.x, event->motion.y)){
				return LOAD_WINDOW_HOVER_LOAD;
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


bool isClickOnLoadSlot(int x, int y){
	if((x>=750&& x<=910) && (y>=100&& y<=188)) return true;
	return false;
}

bool isClickOnBackLW(int x, int y){
	if((x>=750&& x<=912) && (y>=250&& y<=338)) return true;
	return false;
}

int numOfFilesInDir(){
	DIR *dir;
	struct dirent *ent;
	int counter = 0;
	if ((dir = opendir ("./utilities/loadedGames")) != NULL) {
		readdir (dir);
		readdir (dir);
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
		  counter++;
	  }
	  //printf("number of files is:%d\n",counter);
	  closedir (dir);
	  return counter;
	}
	else {
		printf("error");
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
}

void loadRemoveChangeFile(int numOfFiles, int fileDeleted,boardGame* game){
	assert(game!=NULL); assert(game->boardArr!=NULL);
	if(numOfFiles==0) return;
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
		if (fileDeleted<=4) rename("./utilities/loadedGames/game5.xml","./utilities/loadedGames/game4.xml");
		if (fileDeleted<=3)	rename("./utilities/loadedGames/game4.xml","./utilities/loadedGames/game3.xml");
		if (fileDeleted<=2)	rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game2.xml");
		if (fileDeleted<=1)	rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game1.xml");
	}
	else if (numOfFiles==4){
		if (fileDeleted<=3)	rename("./utilities/loadedGames/game4.xml","./utilities/loadedGames/game3.xml");
		if (fileDeleted<=2)	rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game2.xml");
		if (fileDeleted<=1)	rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game1.xml");
	}
	else if (numOfFiles==3){
		if (fileDeleted<=2)	rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game2.xml");
		if (fileDeleted<=1)	rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game1.xml");
	}
	else if (numOfFiles==2){
		if (fileDeleted<=1)	rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game1.xml");
	}
}

void loadFilePath(boardGame*board, char* path){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(path!=NULL);
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


/*
LinkedList* initLinkedLIst(){
	LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
	assert(ll!=NULL);
	ll->count =0 ;
	return ll;
}


Node* initNode(char* str){
	assert(str!=NULL);
	Node* node = (Node*) malloc(sizeof(Node));
	assert(node!=NULL);
	node->data = (char*) malloc(sizeof(char)*(strlen(str)+1));
	assert(node->data!=NULL);
	strcpy(node->data, str);
	return node;
}
*/
/*
void insertNode(LinkedList* ll, Node* node){
	assert(ll!=NULL);
	assert(node!=NULL);
	if(ll->head==NULL){
		ll->head = node;
	}
	Node* cur = ll->head;
	else{
		while(cur->){

		}
	}
}
*/
/*
void drawLoadWindow(LoadWindow* lw);
LOAD_WINDOW_EVENT loadWindowHandleEvent(LoadWindow* lw, SDL_Event* event);
bool isClickOnSlot1(int x, int y);
bool isClickOnSlot2(int x, int y);
bool isClickOnSlot3(int x, int y);
bool isClickOnSlot4(int x, int y);
bool isClickOnSlot5(int x, int y);
bool isClickOnBack(int x, int y);
bool isClickOnLoadSlot(int x, int y);
void loadWindowHide(LoadWindow* lw);
void loadWindowShow(LoadWindow* lw);
*/
