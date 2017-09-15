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
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "mainWindowGUI.h"
#include "settingsWindowGUI.h"
#include "GUIManager.h"
#include "gameWindowGUI.h"


void guiMain(boardGame* board){
	bool back = false;
	while(!back){
		Manager* manager = createManager();
		drawMainWindow(manager->mw);
		SDL_Event event;
		while(!back){
			SDL_WaitEvent(&event);

			if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_EVENT_QUIT) {
				quitGame(manager);
			}
			else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_NEW_GAME){
				destroyMainWindow(manager->mw);
				manager->sw = createSW(board->gameMode,board->userCol, board->diffLevel);
				drawSettingsWindow(manager->sw);
				while(1){
					SDL_Event event1;
					SDL_WaitEvent(&event1);
					if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_EVENT_QUIT){
						quitGame(manager);
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_BACK){
						destroyManager(manager);
						back = true;
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_PLAY){
						destroySettingsWindow(manager->sw);
						manager->game = (GameWindow*) createGW();
						drawSettingsWindow(manager->sw);
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_1){
						setNumPlayers(board,1);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(1,1,2);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_2){
						setNumPlayers(board,2);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(2,1,2);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_WHITE){
						if(board->gameMode==2) continue;
						if(board->userCol==1) continue;
						setColor(board,1);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(1,1,2);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_BLACK){
						if(board->gameMode==2) continue;
						if(board->userCol==0) continue;
						setColor(board,0);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(1,0,2);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_1){
						if(board->gameMode==2) continue;
						if(board->diffLevel==1) continue;
						setDifficult(board,1);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(1,board->userCol,1);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_2){
						if(board->gameMode==2) continue;
						if(board->diffLevel==2) continue;
						setDifficult(board,2);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(1,board->userCol,2);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_3){
						if(board->gameMode==2) continue;
						if(board->diffLevel==3) continue;
						setDifficult(board,3);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(1,board->userCol,3);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_4){
						if(board->gameMode==2) continue;
						if(board->diffLevel==4) continue;
						setDifficult(board,4);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(1,board->userCol,4);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_5){
						if(board->gameMode==2) continue;
						if(board->diffLevel==5) continue;
						setDifficult(board,5);
						destroySettingsWindow(manager->sw);
						manager->sw = (SettingsWindow*) createSW(1,board->userCol,5);
						drawSettingsWindow(manager->sw);
						continue;
					}
				}
			}
		}

		//SDL_ShowWindow(mw);
		back = false;
	}

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
	setDefault(manager->board);
	manager->mw = createMW();
	if(manager->mw==NULL){
		printf("couldn't create GUI mainWindow");
		destroyManager(manager);
		return NULL;
	}
	manager->sw = NULL;
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

