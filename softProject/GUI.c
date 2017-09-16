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
#include "loadWindowGUI.h"
#include "GUIManager.h"
#include "gameWindowGUI.h"


void guiMain(boardGame* board){
	bool back = false;
	Manager* manager = createManager();
	while(1){
		setDefault(manager->board);
		manager->mw = (MainWindow*) createMW();
		drawMainWindow(manager->mw);
		SDL_Event event;
		back = false;
		while(!back){
			SDL_WaitEvent(&event);
			if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_EVENT_QUIT) {
				quitGame(manager);
			}
			else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_LOAD_GAME){
				destroyMainWindow(manager->mw);
				int dirFiles = numOfFilesInDir();
				manager->lw = (LoadWindow*) createLW(dirFiles);
				drawLoadWindow(manager->lw,dirFiles);
				int fileRemove =0;
				while(1){
					SDL_Event event1;
					SDL_WaitEvent(&event1);
					if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_EVENT_QUIT){
							quitGame(manager);
					}
					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_PUSH_BACK){
						destroyLoadWindow(manager->lw);
						back=true;
						break;
					}
					/*
					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_PUSH_LOAD){
						destroyLoadWindow(manager->lw);
						back=true;
						break;
					}
					*/
					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_HOVER_BACK){
						destroyLoadWindow(manager->lw);

						createLR(manager->lw,dirFiles,true,fileRemove,false);
						printf("before draw\n");

						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}

					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_HOVER_LOAD){
						destroyLoadWindow(manager->lw);
						printf("before create");
						createLR(manager->lw,dirFiles,false,0,true);
						printf("before draw");
						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}
					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_SLOT1){
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,false,1,false);
						drawLoadWindow(manager->lw,dirFiles);
						fileRemove = 1;
						continue;
					}
					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_SLOT2){
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,false,2,false);
						drawLoadWindow(manager->lw,dirFiles);
						fileRemove = 2;
						continue;
					}

					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_SLOT3){
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,false,3,false);
						drawLoadWindow(manager->lw,dirFiles);
						fileRemove = 3;
						continue;
					}
					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_SLOT4){
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,false,4,false);
						drawLoadWindow(manager->lw,dirFiles);
						fileRemove = 4;
						continue;
					}
					else if (loadWindowHandleEvent(manager->lw, &event1) == LOAD_WINDOW_SLOT5){
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,false,5,false);
						drawLoadWindow(manager->lw,dirFiles);
						fileRemove = 5;
						continue;
					}


				}
			}
			else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_NEW_GAME){
				destroyMainWindow(manager->mw);
				manager->sw = (SettingsWindow*) createSW(manager->board->gameMode,manager->board->userCol, manager->board->diffLevel);
				drawSettingsWindow(manager->sw);
				//bool backLighted = false;
				while(1){
					SDL_Event event1;
					SDL_WaitEvent(&event1);
					if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_EVENT_QUIT){
						quitGame(manager);
					}

					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_PUSH_BACK){
						destroySettingsWindow(manager->sw);
						back = true;
						break;
					}/*
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_PUSH_START){
						destroySettingsWindow(manager->sw);
						manager->game = (GameWindow*) createGW();
						drawGameWindow(manager->gw);
						while(1){
						SDL_Event event1;
						SDL_WaitEvent(&event1);
						}
					}
*/
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_HOVER_BACK){
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,manager->board->gameMode,manager->board->userCol,manager->board->diffLevel,true,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_HOVER_START){
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,manager->board->gameMode,manager->board->userCol,manager->board->diffLevel,false,true);
						drawSettingsWindow(manager->sw);
						continue;
					}

					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_1){
						setNumPlayers(manager->board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,1,2,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_2){
						setNumPlayers(manager->board,2);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,2,1,manager->board->diffLevel,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_WHITE){
						if(manager->board->gameMode==2) continue;
						if(manager->board->userCol==1) continue;
						setColor(manager->board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,1,manager->board->diffLevel,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_BLACK){
						if(manager->board->gameMode==2) continue;
						if(manager->board->userCol==0) continue;
						setColor(manager->board,0);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,0,manager->board->diffLevel,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_1){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==1) continue;
						setDifficult(manager->board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,1,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_2){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==2) continue;
						setDifficult(manager->board,2);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,2,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_3){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==3) continue;
						setDifficult(manager->board,3);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,3,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_4){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==4) continue;
						setDifficult(manager->board,4);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,4,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_5){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==5) continue;
						setDifficult(manager->board,5);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,5,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
					else{
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,manager->board->gameMode,manager->board->userCol,manager->board->diffLevel,false,false);
						drawSettingsWindow(manager->sw);
						continue;
					}
				}
			}
		}

		//SDL_ShowWindow(mw);

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
	manager->gw = NULL;
	manager->lw = NULL;
	return manager;
}


void destroyManager(Manager* manager){
	if(manager==NULL) return;
	else{
		if(manager->board!=NULL) destroyBoard(manager->board);
		if(manager->mw!=NULL) destroyMainWindow(manager->mw);
		if(manager->sw!=NULL) destroySettingsWindow(manager->sw);
		if(manager->gw!=NULL) destroyGameWindow(manager->gw);
		//if(manager->lw!=NULL) destroyLoadWindow(manager->lw);
		free(manager);	// gameWindow need to be added
		return;
	}
}

