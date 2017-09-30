/*
 * loadWindowGUI.c
 *
 *  Created on: 17 בספט׳ 2017
 *      Author: Itamar
 */

/**
 * LoadWindow summary:
 *
 * The Main Window GUI sections. This functions are responsible for creating
 * the Main window Data structure, handling the different events in this window etc.
 *
 *
 *
 *
 * createLW 					- Creating the LoadWindow structure
 * createLR 					- Creating the Renderer and the textures
 * destroyLoadWindow 			- Destroying theLoadWindow Structure
 * destroyLoadRenderer		 	- Destroying only the renderer and textures
 * numOfFilesInDir 				- Counting the number of files saved locally
 * loadFilePath					- Loading a file Saved locally to the Game Board
 * loadRemoveChangeFile 		- Doing actions of manipulating the files in order to load
 * drawLoadWindow 				- Drawing the LoadWindow
 * loadWindowHandleEvent 		- Classifying different events in Load window
 * isClickOnSlot1				- Checking if there was click on Slot1 button
 * isClickOnSlot2				- Checking if there was click on Slot2 button
 * isClickOnSlot3				- Checking if there was click on Slot3 button
 * isClickOnSlot4				- Checking if there was click on Slot4 button
 * isClickOnSlot5				- Checking if there was click on Slot5 button
 * isClickOnLWBack				- Checking if there was click on Back button
 * isClickOnLWLoad				- Checking if there was click on Load button
 * createBackTexture			- Creating and Destroying the back Texture (light/not light)
 * createLoadTexture			- Creating and Destroying the load Texture (light/not light)
 * loadWindowHide				- Hiding the Window
 * loadWindowShow				- Showing the Window
 *loadWindowGuiManager 			- Handling the different cases and translates command to action
 *
 *
 */

#include "loadWindowGUI.h"
#include <assert.h>
#include <string.h>



/**
 *
 * Creating the LoadWindow structure using SDL.
 * In this part we create a window, renderer and buttons.
 *
 * @return
 * LoadWindow pointer of the data Structure
 *
 */

LoadWindow* createLW(){
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
	createLR(lw,numFiles,0,false);
	return lw;
}


/**
 *
 * Creating the LoadWindow Renderer and textures using SDL.
 * In this part we create only renderer and buttons.
 *
 * @param lw - LoadWindow Data structure
 * @param slotsNum - which slot to light (if any of them)
 * @param slotLight - if to light some slot
 * @param loadLight - if to light the load
 *
 * @return
 * void
 *
 */

void createLR(LoadWindow* lw, int slotsNum, int slotLight, bool loadLight){
	assert(slotsNum>=0); assert(slotsNum<=5); assert(slotLight>=0); assert(slotLight<=5);
	assert(lw!=NULL); assert(lw->window!=NULL);
	SDL_Surface* surface = NULL;
	if(lw->renderer==NULL) printf("renderer is null");
	//SDL_RenderClear(lw->renderer);

	// creating the load Window renderer
	if(lw->renderer!=NULL) SDL_DestroyRenderer(lw->renderer);
	lw->renderer = SDL_CreateRenderer(lw->window, -1, SDL_RENDERER_ACCELERATED);
	if (lw->renderer==NULL) {
		printf("Could not create a renderer in LoadWindow: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return ;
	}
	//Creating a background texture:

	surface= SDL_LoadBMP("./utilities/loadWindow/anotherBackground.bmp");
	if (surface==NULL){
		//printf("Could not create a bg surface in LoadWindow: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	lw->bg = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->bg==NULL){
		printf("Could not create a bg texture in LoadWindow: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a back texture:
	surface = SDL_LoadBMP("./utilities/loadWindow/backNewClicked.bmp");
	if(surface==NULL){
		printf("Could not create a back surface in LoadWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	lw->back = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->back==NULL){
		printf("Could not create a back texture in LoadWindow: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a load texture:
	if((loadLight)&& (slotLight!=0)) surface = SDL_LoadBMP("./utilities/loadWindow/loadNewClicked.bmp");
	else surface = SDL_LoadBMP("./utilities/loadWindow/loadNew.bmp");
	if(surface==NULL){
		printf("Could not create a load surface in LoadWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	lw->load = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->load==NULL){
		printf("Could not create a load texture in LoadWindow: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating slot1 texture:
	if(slotsNum>=1){
		if(slotLight==1) surface = SDL_LoadBMP("./utilities/loadWindow/slot1Clicked.bmp");
		else if(slotLight!=1) surface = SDL_LoadBMP("./utilities/loadWindow/slot1.bmp");
		if(surface==NULL){
			printf("Could not create a slot1 surface in LoadWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot1 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot1==NULL){
			printf("Could not create a slot1 texture in LoadWindow: %s\n", SDL_GetError());
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
			printf("Could not create a slot2 surface in LoadWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot2 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot2==NULL){
			printf("Could not create a slot 2 texture in LoadWindow: %s\n", SDL_GetError());
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
			printf("Could not create a slot3 surface in LoadWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot3 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot3==NULL){
			printf("Could not create a slot3 texture in LoadWindow: %s\n", SDL_GetError());
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
			printf("Could not create a slot4 surface in LoadWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot4 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot4==NULL){
			printf("Could not create a slot4 texture in LoadWindow: %s\n", SDL_GetError());
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
			printf("Could not create a slot5 surface in LoadWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->slot5 = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->slot5==NULL){
			printf("Could not create a slot5 texture in LoadWindow: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return;
		}
		SDL_FreeSurface(surface);
	}
}

/**
 *
 * Destroying the LoadWindow data structure with it's elements and free the memory.
 *
 * @param lw - Load Window data structure
 *
 * @return
 * void
 *
 */


void destroyLoadWindow(LoadWindow* lw){
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
	if(lw->load!=NULL) SDL_DestroyTexture(lw->load);
	if(lw->bg!=NULL) SDL_DestroyTexture(lw->bg);
	if(lw->renderer!=NULL) SDL_DestroyRenderer(lw->renderer);
	if(lw->window!=NULL) SDL_DestroyWindow(lw->window);
	free(lw);
	return;
}

/**
 *
 * Destroying the LoadWindow renderer and textures.
 *
 * @param lw - Load Window data structure
 *
 * @return
 * void
 *
 */


void destroyLoadRenderer(LoadWindow* lw){
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


/**
 *
 * Drawing the window and presents it to the user.
 *
 * @param lw - Load Window data structure
 * @param slotsNum - how much slots to show
 * @return
 * void
 *
 */

void drawLoadWindow(LoadWindow* lw, int slotsNum){
	if(lw==NULL){
		printf("ERROR: LoadWindow is null in draw");
		return;
	}
	assert(lw->window!=NULL); //assert(lw->bg!=NULL);
	assert(lw->back!=NULL); assert(lw->renderer!=NULL); assert(lw->load!=NULL);
	if(slotsNum>=1) assert(lw->slot1!=NULL);
	if(slotsNum>=2) assert(lw->slot2!=NULL);
	if(slotsNum>=3) assert(lw->slot3!=NULL);
	if(slotsNum>=4) assert(lw->slot4!=NULL);
	if(slotsNum>=5) assert(lw->slot5!=NULL);
	SDL_SetRenderDrawColor(lw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(lw->renderer);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_RenderCopy(lw->renderer, lw->bg, NULL, &rec);
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

	rec.x = 750; rec.y = 100;rec.w = 160; rec.h = 88;	//load message
	SDL_RenderCopy(lw->renderer, lw->load, NULL, &rec);
	rec.x = 750; rec.y = 250;rec.w = 162; rec.h = 88;	//back message
	SDL_RenderCopy(lw->renderer, lw->back, NULL, &rec);
	SDL_RenderPresent(lw->renderer);
}

/**
 *
 * Counting the number of Files saved in the local directory (up till 5 files);
 *
 * @return
 * number of files in directory(integer);
 *
 */

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
		printf("ERROR: couldn't find local files");
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
	free(ent);
}


/**
 *
 * Loading a file to the BoardGame.
 *
 * @param board - BoardGame data structure
 * @param path - the relevant path to load from
 *
 * @return
 * void
 *
 */

void loadFilePath(boardGame*board, char* path){
	assert(board!=NULL); assert(board->boardArr!=NULL); assert(path!=NULL);
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
		token = strtok(buffer,"<> ");
		if(strcmp(token,"difficulty ")==0){
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


/**
 *
 * Doing all the actions of manipulating the files in the local directory.
 * The function supports in saving the Last 5 updated files such that "slot1" is
 * the LRU.
 *
 * @param fileDeleted - which file to delete from saving after loading
 * @param numOfFiles - number of files in the local directory
 * @param game - BoardGame data structure
 * @param lw - LoadWindow Data Structure
 *
 * @return
 * void
 *
 */

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


/**
 *
 * This function accepts events and classifying them to an operational commands.
 *
 * @param lw - Load Window data structure
 * @SDL_Event - the interface event
 *
 * @return
 * LOAD_WINDOW_EVENT command event
 *
 */

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
		/*
		case SDL_MOUSEMOTION:
			if(isClickOnLWLoad(event->motion.x,event->motion.y)){
				return LOAD_WINDOW_HOVER_LOAD;
			}
			else if(isClickOnLWBack(event->motion.x,event->motion.y)){
				return LOAD_WINDOW_HOVER_BACK;
			}
			break;
			*/
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


/**
 *
 * This function checks if there was an event in the boundaries of the slot1 Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the slot1 Button boundaries, false otherwise.
 *
 */

bool isClickOnSlot1(int x, int y){
	if((x>=400&& x<=598) && (y>=120&& y<=176)) return true;
	return false;
}

/**
 *
 * This function checks if there was an event in the boundaries of the slot2 Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the slot2 Button boundaries, false otherwise.
 *
 */

bool isClickOnSlot2(int x, int y){
	if((x>=400&& x<=600) && (y>=191&& y<=249)) return true;
	return false;
}

/**
 *
 * This function checks if there was an event in the boundaries of the slot3 Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the slot3 Button boundaries, false otherwise.
 *
 */

bool isClickOnSlot3(int x, int y){
	if((x>=400&& x<=600) && (y>=264 && y<=320)) return true;
	return false;
}

/**
 *
 * This function checks if there was an event in the boundaries of the slot4 Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the slot4 Button boundaries, false otherwise.
 *
 */

bool isClickOnSlot4(int x, int y){
	if((x>=400&& x<=598) && (y>=335&& y<=391)) return true;
	return false;
}


/**
 *
 * This function checks if there was an event in the boundaries of the slot5 Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the slot5 Button boundaries, false otherwise.
 *
 */

bool isClickOnSlot5(int x, int y){
	if((x>=400&& x<=598) && (y>=406&& y<=460)) return true;
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

bool isClickOnLWLoad(int x, int y){
	if((x>=750&& x<=910) && (y>=100&& y<=188)) return true;
	return false;
}

/**
 *
 * This function checks if there was an event in the boundaries of the Back Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the Back Button boundaries, false otherwise.
 *
 */

bool isClickOnLWBack(int x, int y){
	if((x>=750&& x<=912) && (y>=250&& y<=338)) return true;
	return false;
}

/**
 *
 * This function hiding the LoadWindow
 *
 * @param lw - LoadWindow data structure
 *
 * @return
 * void
 *
 */

void loadWindowHide(LoadWindow* lw){
	assert(lw!=NULL); assert(lw->window!=NULL);
	SDL_HideWindow(lw->window);
}

/**
 *
 * This function showing the LoadWindow
 *
 * @param lw - LoadWindow data structure
 *
 * @return
 * void
 *
 */

void loadWindowShow(LoadWindow* lw){
	assert(lw!=NULL); assert(lw->window!=NULL);
	SDL_ShowWindow(lw->window);
}


/**
 *
 * This function destroy and creates back again the "Back" Button.
 *
 * @param lw - LoadWindow data structure
 *
 * @return
 * void
 *
 */

void createBackTexture(LoadWindow* lw){
	assert(lw!=NULL); assert(lw->window!=NULL); assert(lw->renderer!=NULL);
	SDL_Surface* surface = NULL;
	SDL_DestroyTexture(lw->back);
	surface = SDL_LoadBMP("./utilities/loadWindow/backNewClicked.bmp");
	if(surface==NULL){
		printf("Could not create a back surface in LoadWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	lw->back = SDL_CreateTextureFromSurface(lw->renderer, surface);
	if (lw->back==NULL){
		printf("Could not create a back texture in LoadWindow: %s\n", SDL_GetError());
		destroyLoadWindow(lw);
		return;
	}
	SDL_FreeSurface(surface);
}


/**
 *
 * This function destroy and creates back again the "Load" Button.
 *
 * @param lw - LoadWindow data structure
 * @param slotLight - if slotLoght==0 -->don't Light load
 * @param loadLight - Lighted button or not
 *
 *
 * @return
 * void
 *
 */


void createLoadTexture(LoadWindow* lw, int slotLight, bool loadLight ){
	assert(lw!=NULL); assert(lw->window!=NULL); assert(lw->renderer!=NULL);
	SDL_Surface* surface = NULL;
	SDL_DestroyTexture(lw->load);
	//Creating a load texture:
		if((loadLight)&& (slotLight!=0)) surface = SDL_LoadBMP("./utilities/loadWindow/loadNewClicked.bmp");
		else surface = SDL_LoadBMP("./utilities/loadWindow/loadNew.bmp");
		if(surface==NULL){
			printf("Could not create a load surface in LoadWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		lw->load = SDL_CreateTextureFromSurface(lw->renderer, surface);
		if (lw->load==NULL){
			printf("Could not create a load texture in LoadWindow: %s\n", SDL_GetError());
			destroyLoadWindow(lw);
			return;
		}
		SDL_FreeSurface(surface);
}


/**
 *
 * This function responsible for handling the events and translates them to an operations
 * in the Load Window section.
 *
 * @param lw - LoadWindow data structure
 * @param board - BoardGame data Structure
 * @param backGameBool - true means when clicking back we will go the the Game Window
 * @param backMainBool - true means when clicking back we will go the the Main Window
 * @return
 * int between 1-4:
 * 		1: quit the game
 * 		2: back to Game Window
 * 		3: back to Main Window
 * 		4: load the game and go to Game window
 *		0: should never!! reach to 0!
 */


int loadWindowGuiManager(LoadWindow* lw, boardGame* board, bool backGameBool, bool backMainBool){
	assert(lw!=NULL);
	int dirFiles = numOfFilesInDir();
	int fileRemove =0;
	drawLoadWindow(lw,dirFiles);
	bool quitLoad = false;
	while(!quitLoad){
		SDL_Event event2;
		while(SDL_WaitEvent(&event2)!=0){
			dirFiles = numOfFilesInDir();
			if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_EVENT_QUIT){
				destroyLoadWindow(lw);
				return 1;
			}
			else if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_PUSH_BACK){
				destroyLoadWindow(lw);
				if (backGameBool)return 2;
				else if(backMainBool)return 3;
			}
			else if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_PUSH_LOAD){
				if(dirFiles>0 && fileRemove>0){
					initBoard(board,true);
					loadRemoveChangeFile(dirFiles, fileRemove,board,lw);
					destroyLoadWindow(lw);
					return 4;
				}
				break;
			}
			else if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME1SLOT
				||loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME2SLOT
				||loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME3SLOT
				||loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME4SLOT
				||loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME5SLOT){
			if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME1SLOT) fileRemove = 1;
			else if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME2SLOT) fileRemove = 2;
			else if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME3SLOT) fileRemove = 3;
			else if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME4SLOT) fileRemove = 4;
			else if (loadWindowHandleEvent(lw, &event2) == LOAD_WINDOW_GAME5SLOT) fileRemove = 5;
			destroyLoadRenderer(lw);
			createLR(lw,dirFiles,fileRemove,true);
			drawLoadWindow(lw,dirFiles);
			break;
			}
		}
	}
	return 0;
}
