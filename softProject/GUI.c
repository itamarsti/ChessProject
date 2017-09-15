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
	Manager* manager = createManager();
	while(1){
		manager->mw = (MainWindow*) createMW();
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
						destroySettingsWindow(manager->sw);
						setDefault(manager->board);
						back = true;
						break;
					}
					/*
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_START){
						destroySettingsWindow(manager->sw);
						manager->game = (GameWindow*) createGW();
						drawGameWindow(manager->gw);
						while(1){
						SDL_Event event1;
						SDL_WaitEvent(&event1);
						}
					}
					*/
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_1){
						setNumPlayers(board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,1,2);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_2){
						setNumPlayers(board,2);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,2,1,2);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_WHITE){
						if(board->gameMode==2) continue;
						if(board->userCol==1) continue;
						setColor(board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,1,board->diffLevel);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_BLACK){
						if(board->gameMode==2) continue;
						if(board->userCol==0) continue;
						setColor(board,0);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,0,board->diffLevel);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_1){
						if(board->gameMode==2) continue;
						if(board->diffLevel==1) continue;
						setDifficult(board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,board->userCol,1);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_2){
						if(board->gameMode==2) continue;
						if(board->diffLevel==2) continue;
						setDifficult(board,2);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,board->userCol,2);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_3){
						if(board->gameMode==2) continue;
						if(board->diffLevel==3) continue;
						setDifficult(board,3);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,board->userCol,3);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_4){
						if(board->gameMode==2) continue;
						if(board->diffLevel==4) continue;
						setDifficult(board,4);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,board->userCol,4);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_5){
						if(board->gameMode==2) continue;
						if(board->diffLevel==5) continue;
						setDifficult(board,5);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,board->userCol,5);
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
	manager->mw = NULL;
	manager->sw = NULL;
	manager->game = NULL;

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

