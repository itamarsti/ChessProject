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
#include "settingsWindowGUI.h"
#include "GUIManager.h"


void guiMain(boardGame* board){
	Manager* manager = createManager();
	drawMainWindow(manager->mw);
	SDL_Event event;
	while(1){
		SDL_WaitEvent(&event);
		if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_EVENT_QUIT) {
			quitMainWindow(manager);
		}
	}
	//SDL_ShowWindow(mw);
}



Manager* createManager(){
	Manager* manager = (Manager*) malloc(sizeof(Manager));
	if(manager==NULL){
		printf("coudln't create manager");
		return NULL;
	}
	manager->board = createBoard();
	if(manager->board==NULL){
		printf("couldn't create boardGame in GUI");
		destroyManager(manager);
		return NULL;
	}
	initBoard(manager->board);
	manager->mw = createMW();
	if(manager->mw==NULL){
		printf("couldn't create GUI mainWindow");
		destroyManager(manager);
		return NULL;
	}
	manager->sw = createSW();
	if(manager->mw==NULL){
		printf("couldn't create GUI settingsWindow");
		destroyManager(manager);
		return NULL;
	}
	return manager;
}


void destroyManager(Manager* manager){
	if(manager==NULL) return;
	else{
		if(manager->board!=NULL) destroyBoard(manager->board);
		if(manager->mw!=NULL) destroyMainWindow(manager->mw);
		if(manager->sw!=NULL) destroySettingsWindow(manager->sw);

		free(manager);	// gameWindow need to be added
		return;
	}
}

