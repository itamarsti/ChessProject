/*
 * GUI.c
 *
 *  Created on: 31 ����� 2017
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
		back = false;
		while(!back){
			SDL_Event event;
			SDL_WaitEvent(&event);
			if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_EVENT_QUIT) {
				quitGame(manager);
			}
			else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_LOAD_GAME){
				destroyMainWindow(manager->mw);
				int dirFiles = numOfFilesInDir();
				manager->lw = (LoadWindow*) createLW(dirFiles);
				//printf("got till here");
				drawLoadWindow(manager->lw,dirFiles);
				//printf("got till here2");
				int fileRemove =0;
				bool mainBool = false;
				while(!mainBool){
					SDL_Event event2;
					SDL_WaitEvent(&event2);
					if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_EVENT_QUIT){
							quitGame(manager);
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_PUSH_BACK){
						destroyLoadWindow(manager->lw);
						back=true;
						break;
					}

					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_PUSH_LOAD){
						if(dirFiles>0 && dirFiles<=5 && fileRemove>0 && fileRemove<=5 ){
							loadRemoveChangeFile(dirFiles, fileRemove,manager->board);
							destroyLoadWindow(manager->lw);
							manager->gw = (GameWindow*) createGW();
							drawGameWindow(manager->gw, manager->board);
							bool gameSaved = false;
							while(1){
								SDL_Event event3;
								SDL_WaitEvent(&event3);
								if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_EVENT_QUIT){
									if(!gameSaved){
										int save = saveGameMessageBox();
										if(save ==2) continue;	//cancel
										else if(save==-1){		//error
											printf("Error in Save MessagBox");
											continue;
										}
										else if (save==1){		//yes
											int files = numOfFilesInDir();
											saveGameFromGUI(manager->board,files);
										}
										else if(save==0){		//no
										}
									}
									quitGame(manager);
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_UNDO){
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_RESTART_GAME){
									initBoard(manager->board,false);
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_SAVE_GAME){
									int files = numOfFilesInDir();
									saveGameFromGUI(manager->board,files);
									gameSaved = true;
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_LOAD_GAME){
									dirFiles = numOfFilesInDir();
									destroyGameWindow(manager->gw);
									manager->lw = (LoadWindow*) createLW(dirFiles);
									drawLoadWindow(manager->lw,dirFiles);
									fileRemove =0;
									mainBool = false;
									break;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_MAIN_MENU){
									if(!gameSaved){
										int save = saveGameMessageBox();
										if(save ==2) continue;	//cancel
										else if(save==-1){		//error
											printf("Error in Save MessagBox");
											continue;
										}
										else if (save==1){		//yes
											int files = numOfFilesInDir();
											saveGameFromGUI(manager->board,files);
										}
										else if(save==0){		//no
										}
									}
									gameSaved = true;
									destroyGameWindow(manager->gw);
									mainBool = true;
									back = true;
									break;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_EVENT_QUIT){
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,false,false,false,false,false,true);
									drawGameWindow(manager->gw, manager->board);
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_UNDO){
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,true,false,false,false,false,false);
									drawGameWindow(manager->gw, manager->board);
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_RESTART_GAME){
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,false,true,false,false,false,false);
									drawGameWindow(manager->gw, manager->board);
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_SAVE_GAME){
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,false,false,true,false,false,false);
									drawGameWindow(manager->gw, manager->board);
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_LOAD_GAME){
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,false,false,false,true,false,false);
									drawGameWindow(manager->gw, manager->board);
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_MAIN_MENU){
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,false,false,false,false,true,false);
									drawGameWindow(manager->gw, manager->board);
									continue;
								}
								else{
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,false,false,false,false,false,false);
									drawGameWindow(manager->gw, manager->board);
									continue;
								}
							}
						}
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_HOVER_BACK){
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,true,fileRemove,false);
						//printf("before draw\n");
						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}

					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_HOVER_LOAD){
						destroyLoadRenderer(manager->lw);
						//printf("before create\n");
						createLR(manager->lw,dirFiles,false,fileRemove,true);
						//printf("before draw\n");
						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME1SLOT){
						destroyLoadRenderer(manager->lw);
						fileRemove = 1;
						createLR(manager->lw,dirFiles,false,fileRemove,false);
						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME2SLOT){
						destroyLoadRenderer(manager->lw);
						fileRemove = 2;
						createLR(manager->lw,dirFiles,false,fileRemove,false);
						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}

					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME3SLOT){
						destroyLoadRenderer(manager->lw);
						fileRemove = 3;
						createLR(manager->lw,dirFiles,false,fileRemove,false);
						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME4SLOT){
						destroyLoadRenderer(manager->lw);
						fileRemove = 4;
						createLR(manager->lw,dirFiles,false,fileRemove,false);
						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME5SLOT){
						destroyLoadRenderer(manager->lw);
						fileRemove = 5;
						createLR(manager->lw,dirFiles,false,fileRemove,false);
						drawLoadWindow(manager->lw,dirFiles);
						continue;
					}
					else{
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,false,fileRemove,false);
						drawLoadWindow(manager->lw, dirFiles);
						continue;
					}


				}
			}
			else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_NEW_GAME){
				destroyMainWindow(manager->mw);
				manager->sw = (SettingsWindow*) createSW(manager->board->gameMode,manager->board->userCol, manager->board->diffLevel);
				drawSettingsWindow(manager->sw);
				//bool backLighted = false;
				bool mainBool = false;
				while(!mainBool){
					SDL_Event event1;
					SDL_WaitEvent(&event1);
					if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_EVENT_QUIT){
						quitGame(manager);
					}

					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_PUSH_BACK){
						destroySettingsWindow(manager->sw);
						back = true;
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_PUSH_START){
						destroySettingsWindow(manager->sw);
						manager->gw = (GameWindow*) createGW();
						drawGameWindow(manager->gw, manager->board);
						bool gameSaved = false;
						while(1){
							SDL_Event event3;
							SDL_WaitEvent(&event3);
							if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_EVENT_QUIT){
								if(!gameSaved){
									int save = saveGameMessageBox();
									if(save ==2) continue;	//cancel
									else if(save==-1){		//error
										printf("Error in Save MessagBox");
										continue;
									}
									else if (save==1){		//yes
										int files = numOfFilesInDir();
										saveGameFromGUI(manager->board,files);
									}
									else if(save==0){		//no
									}
								}
								quitGame(manager);
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_UNDO){
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_RESTART_GAME){
								initBoard(manager->board,false);
								continue;
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_SAVE_GAME){
								int files = numOfFilesInDir();
								saveGameFromGUI(manager->board,files);
								gameSaved = true;
								continue;
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_LOAD_GAME){
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_MAIN_MENU){
								if(!gameSaved){
									int save = saveGameMessageBox();
									if(save ==2) continue;	//cancel
									else if(save==-1){		//error
										printf("Error in Save MessagBox");
										continue;
									}
									else if (save==1){		//yes
										int files = numOfFilesInDir();
										saveGameFromGUI(manager->board,files);
									}
									else if(save==0){		//no
									}
								}
								gameSaved = true;
								destroyGameWindow(manager->gw);
								mainBool = true;
								back = true;
								break;
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_EVENT_QUIT){
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,false,false,false,false,false,true);
								drawGameWindow(manager->gw, manager->board);
								continue;
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_UNDO){
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,true,false,false,false,false,false);
								drawGameWindow(manager->gw, manager->board);
								continue;
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_RESTART_GAME){
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,false,true,false,false,false,false);
								drawGameWindow(manager->gw, manager->board);
								continue;
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_SAVE_GAME){
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,false,false,true,false,false,false);
								drawGameWindow(manager->gw, manager->board);
								continue;
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_LOAD_GAME){
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,false,false,false,true,false,false);
								drawGameWindow(manager->gw, manager->board);
								continue;
							}
							else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_MAIN_MENU){
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,false,false,false,false,true,false);
								drawGameWindow(manager->gw, manager->board);
								continue;
							}
							else{
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,false,false,false,false,false,false);
								drawGameWindow(manager->gw, manager->board);
								continue;
							}

						}
					}
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
	initBoard(manager->board, true);
	setDefault(manager->board);
	manager->mw = NULL;
	manager->sw = NULL;
	manager->gw = NULL;
	manager->lw = NULL;
	return manager;
}


void destroyManager(Manager* manager){
	printf("in destroy manager");
	if(manager==NULL) return;
	else{
		if(manager->board!=NULL) destroyBoard(manager->board);
		printf("destroy board works fine\n");
		if(manager->mw!=NULL) destroyMainWindow(manager->mw);
		printf("destroy mainWindow works fine\n");
		if(manager->sw!=NULL) destroySettingsWindow(manager->sw);
		printf("destroy settingsWindow works fine\n");
		if(manager->gw!=NULL) destroyGameWindow(manager->gw);
		printf("destroy gamwWindow works fine\n");
		if(manager->lw!=NULL) destroyLoadWindow(manager->lw);
		printf("destroy loadWindow works fine\n");
		free(manager);
		return;
	}
}

