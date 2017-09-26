/*
 * GUI.c
 *
 *  Created on: 31 баев„ 2017
 *      Author: Itamar
 */

#include "GUI.h"
#include "boardFuncs.h"
#include "gameCommands.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>
#include "mainWindowGUI.h"
#include "settingsWindowGUI.h"
#include "loadWindowGUI.h"
#include "gameWindowGUI.h"
#include "alphaBetaMinMax.h"


void guiMain(){
	Manager* manager =(Manager*) createManager();
	if(manager->mw==NULL) printf("main window is null");
	setDefault(manager->board);
	initBoard(manager->board,true);
	bool loadBool, settingsBool, gameBool, backMainBool, backGameBool = false;
	bool mainBool = true;
	while(1){
		if(mainBool){			//~~~~~~~~~Beginning of main window~~~~~~~~
			initBoard(manager->board,true);
			if(manager->mw==NULL) printf("main window is null");
			setDefault(manager->board);
			//if(manager->mw!=NULL) destroyMainWindow(manager->mw);
			manager->mw = (MainWindow*) createMW();
			drawMainWindow(manager->mw);
			bool quitMain = false;
			while(!quitMain){
				SDL_Event event;
				mainBool = false;
				while(SDL_PollEvent(&event)!=0){
					if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_EVENT_QUIT) {
						destroyMainWindow(manager->mw);
						quitGame(manager);
					}
					else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_LOAD_GAME){
						destroyMainWindow(manager->mw);
						loadBool = true;
						backMainBool = true;
						quitMain = true;
						break;
					}
					else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_NEW_GAME){
						destroyMainWindow(manager->mw);
						settingsBool = true;
						quitMain = true;
						break;
					}
				}
			}
		}
		//----------------------------End of main Window--------------------------------
		else if(settingsBool){				//~~~~~~~~~Beginning of settings window~~~~~~~~
			manager->sw = (SettingsWindow*) createSW(manager->board->gameMode,manager->board->userCol, manager->board->diffLevel);
			drawSettingsWindow(manager->sw);
			settingsBool = false;
			bool quitSettings = false;
			while(!quitSettings){
				SDL_Event event1;
				quitSettings = false;
				while(SDL_PollEvent(&event1)!=0){
					if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_EVENT_QUIT){
						destroySettingsWindow(manager->sw);
						quitGame(manager);
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_PUSH_BACK){
						destroySettingsWindow(manager->sw);
						mainBool = true;
						quitSettings = true;
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_PUSH_START){
						destroySettingsWindow(manager->sw);
						gameBool = true;
						quitSettings = true;
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_HOVER_BACK){
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,manager->board->gameMode,manager->board->userCol,manager->board->diffLevel,true,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_HOVER_START){
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,manager->board->gameMode,manager->board->userCol,manager->board->diffLevel,false,true);
						drawSettingsWindow(manager->sw);
						break;
					}

					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_1){
						setNumPlayers(manager->board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,1,2,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_2){
						setNumPlayers(manager->board,2);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,2,1,manager->board->diffLevel,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_WHITE){
						if(manager->board->gameMode==2) continue;
						if(manager->board->userCol==1) continue;
						setColor(manager->board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,1,manager->board->diffLevel,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_BLACK){
						if(manager->board->gameMode==2) continue;
						if(manager->board->userCol==0) continue;
						setColor(manager->board,0);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,0,manager->board->diffLevel,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_1){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==1) continue;
						setDifficult(manager->board,1);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,1,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_2){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==2) continue;
						setDifficult(manager->board,2);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,2,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_3){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==3) continue;
						setDifficult(manager->board,3);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,3,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_4){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==4) continue;
						setDifficult(manager->board,4);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,4,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_5){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==5) continue;
						setDifficult(manager->board,5);
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,1,manager->board->userCol,5,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
					else{
						destroySettingsRenderer(manager->sw);
						createSR(manager->sw,manager->board->gameMode,manager->board->userCol,manager->board->diffLevel,false,false);
						drawSettingsWindow(manager->sw);
						break;
					}
				}
			}
		}
		//----------------------------End of Settings Window--------------------------------
		else if(loadBool){					//~~~~~~~~~Beginning of load window~~~~~~~~
			printf("inside load before creating load window\n");
			int dirFiles = numOfFilesInDir();
			int fileRemove =0;
			manager->lw = (LoadWindow*) createLW();
			drawLoadWindow(manager->lw,dirFiles);
			printf("after creating load window\n");
			loadBool = false;
			bool quitLoad = false;
			while(!quitLoad){
				printf("inside loop");
				SDL_Event event2;
				quitLoad = false;
				while(SDL_WaitEvent(&event2)!=0){
					dirFiles = numOfFilesInDir();
					if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_EVENT_QUIT){
						destroyLoadWindow(manager->lw);
						quitGame(manager);
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_PUSH_BACK){
						destroyLoadWindow(manager->lw);
						if (backGameBool)gameBool = true;
						else if(backMainBool)mainBool = true;
						backMainBool = false;
						backGameBool = false;
						quitLoad = true;
						break;
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_PUSH_LOAD){
						if(dirFiles>0 && fileRemove>0){
							initBoard(manager->board,true);
							loadRemoveChangeFile(dirFiles, fileRemove,manager->board,manager->lw);
							destroyLoadWindow(manager->lw);
							gameBool = true;
							quitLoad = true;
							break;
						}
						break;
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_HOVER_BACK){
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,true,fileRemove,false);
						drawLoadWindow(manager->lw,dirFiles);
						break;
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_HOVER_LOAD){
						destroyLoadRenderer(manager->lw);
						createLR(manager->lw,dirFiles,false,fileRemove,true);
						drawLoadWindow(manager->lw,dirFiles);
						break;
					}
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME1SLOT
						||loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME2SLOT
						||loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME3SLOT
						||loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME4SLOT
						||loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME5SLOT){
					if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME1SLOT) fileRemove = 1;
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME2SLOT) fileRemove = 2;
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME3SLOT) fileRemove = 3;
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME4SLOT) fileRemove = 4;
					else if (loadWindowHandleEvent(manager->lw, &event2) == LOAD_WINDOW_GAME5SLOT) fileRemove = 5;
					destroyLoadRenderer(manager->lw);
					createLR(manager->lw,dirFiles,false,fileRemove,false);
					drawLoadWindow(manager->lw,dirFiles);
					break;
					}
					else{
						printf("in here\n");
						destroyLoadRenderer(manager->lw);
						printf("in here2\n");
						createLR(manager->lw,dirFiles,false,fileRemove,false);
						drawLoadWindow(manager->lw, dirFiles);
						break;
					}
				}
			}
		}
		//----------------------------End of Load Window--------------------------------
		else if(gameBool){ //~~~~~~~~~Beginning of game window~~~~~~~~

			manager->gw = (GameWindow*) createGW();
			drawGameWindow(manager->gw, manager->board);
			bool gameSaved = false;
			gameBool = false;
			bool quit = false;
			while(!quit){
				if(manager->board->gameMode==1 && manager->board->curPlayer!=manager->board->userCol){
					moveAIobj(manager->board);
					destroyGameRenderer(manager->gw);
					createGR(manager->gw,false,false,false,false,false,false);
					drawGameWindow(manager->gw, manager->board);
					bool kingSafe = isMyKingSafe(manager->board);
					bool checkMate = isCheckMate(manager->board);
					if(kingSafe==false && checkMate==true){
						checkMessageWarning(manager->board->curPlayer, false, true, false);
						quitGame(manager);
					}
					else if(kingSafe==true && checkMate==true){
						checkMessageWarning(manager->board->curPlayer, false, false, true);
						quitGame(manager);
					}
					else if(kingSafe==false && checkMate==false){
						checkMessageWarning(manager->board->curPlayer, true, false, false);
					}
					continue;
				}
				SDL_Event event3;
				while(SDL_PollEvent(&event3)){
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
						destroyGameWindow(manager->gw);
						quitGame(manager);
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_UNDO){
						if(manager->board->gameMode==1){
							if(manager->board->history->actualSize!=0){
								undo(manager->board, false, true); //one more undo
								undo(manager->board, false, true);
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,false,false,false,false,false,false);
								drawGameWindow(manager->gw, manager->board);
								gameSaved = false;
							}
						}
						continue;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_RESTART_GAME){
						initBoard(manager->board,false);
						destroyGameRenderer(manager->gw);
						createGR(manager->gw,false,false,false,false,false,false);
						drawGameWindow(manager->gw, manager->board);
						gameSaved = false;
						break;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_SAVE_GAME){
						if(!gameSaved){
							int files = numOfFilesInDir();
							saveGameFromGUI(manager->board,files);
							saveMessageDialog();
							gameSaved = true;
						}
						continue;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_LOAD_GAME){
						destroyGameWindow(manager->gw);
						loadBool = true;
						backGameBool = true;
						quit = true;
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
								saveMessageDialog();
							}
							else if(save==0){		//no
							}
						}

						gameSaved = true;
						destroyGameWindow(manager->gw);
						mainBool = true;
						quit = true;
						break;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_EVENT_QUIT){
						destroyGameRenderer(manager->gw);
						createGR(manager->gw,false,false,false,false,false,true);
						drawGameWindow(manager->gw, manager->board);
						continue;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_HOVER_UNDO){
						if(manager->board->gameMode==1){
							if(manager->board->history->actualSize!=0){
								destroyGameRenderer(manager->gw);
								createGR(manager->gw,true,false,false,false,false,false);
								drawGameWindow(manager->gw, manager->board);
							}
						}
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
					else if(gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_DRAG_OBJ){
						SDL_Point p1 = {.x = event3.button.x, .y = event3.button.y};
						//printf("xPos is :%d, yPos is:%d\n",p1.x,p1.y);
						bool done = false;
						while(!done){
							SDL_Event event8;
							while(SDL_PollEvent(&event8)!=0){
								SDL_Point p2 = {.x = event8.button.x, .y = event8.button.y};
								//printf("xDest is :%d, yDest is:%d\n",p2.x,p2.y);
								if(gameWindowHandleEvent(manager->gw, &event8)==GAME_WINDOW_HOVER_OBJ){
									SDL_RenderClear(manager->gw->renderer);
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,false,false,false,false,false,false);
									drawGameWindowImproved(manager->gw, manager->board,&p1,&p2);
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event8)==GAME_WINDOW_PUSH_OBJ){
									SDL_Point p3 = {.x = event8.button.x, .y = event8.button.y};
									int pos = fromPixToPos(p1.x, p1.y);
									int dest = fromPixToPos(p3.x, p3.y);
									//printf("the position is:%d, the destination is: %d\n", pos, dest);
									if(moveObj(manager->board, pos, dest, false)){
										SDL_RenderClear(manager->gw->renderer);
										destroyGameRenderer(manager->gw);
										createGR(manager->gw,false,false,false,false,false,false);
										drawGameWindow(manager->gw, manager->board);
										bool kingSafe = isMyKingSafe(manager->board);
										bool checkMate = isCheckMate(manager->board);
										if(kingSafe==false && checkMate==true){
											checkMessageWarning(manager->board->curPlayer, false, true, false);
											quitGame(manager);
										}
										else if(kingSafe==true && checkMate==true){
											checkMessageWarning(manager->board->curPlayer, false, false, true);
											quitGame(manager);
										}
										else if(kingSafe==false && checkMate==false){
											checkMessageWarning(manager->board->curPlayer, true, false, false);
										}
									}
									done = true;
									break;
								}
								else{
									SDL_RenderClear(manager->gw->renderer);
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,false,false,false,false,false,false);
									drawGameWindow(manager->gw, manager->board);
									done = true;
									break;
								}
							}
						}
					}
					/*
					else if(gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_DRAG_LIGHT){
						SDL_Point p1 = {.x = event3.button.x, .y = event3.button.y};
						//printf("xPos is :%d, yPos is:%d\n",p1.x,p1.y);
						bool done2 = false;
						while(!done2){
							SDL_Event event8;
							while(SDL_PollEvent(&event8)!=0){

							}
						}
					}
					*/
					else{
						destroyGameRenderer(manager->gw);
						createGR(manager->gw,false,false,false,false,false,false);
						drawGameWindow(manager->gw, manager->board);
						continue;
					}
				}

			}
		}
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
	printf("in destroy manager\n");
	if(manager==NULL) return;
	if(manager->board!=NULL) destroyBoard(manager->board);
	free(manager);
	return;
}



void checkMessageWarning(int curPlayer,bool check, bool mate, bool tie){
	if(check){
		if(curPlayer==1){
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Check Message",
					"Check! white king is threatened!",NULL);
			}
			else if (curPlayer==0){
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Check Message",
						"Check! black king is threatened!",NULL);
			}
	}
	else if(mate){
		if(curPlayer==1){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"CheckMate Message",
					"CheckMate! Black player wins the game!",NULL);
		}
		else if (curPlayer==0){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"CheckMate Message",
					"CheckMate! White player wins the game!",NULL);
		}
	}
	else if(tie){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Tie Message",
				"Tie! The game ends...",NULL);
	}
}

void saveMessageDialog(){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Save Message",
		"Game was saved!",NULL);
}
void quitGame(Manager* manager){
	if(manager!=NULL){
		destroyManager(manager);
		SDL_Quit();
		printf("Exiting...");
		exit(0);
	}
}


void setBoardDefaultManager(Manager* manager){
	if(manager==NULL){
		destroyManager(manager);
		SDL_Quit();
		printf("Exiting...");
		exit(0);
	}
	manager->board->curPlayer=1;
	manager->board->diffLevel=2;
	manager->board->gameMode=1;
	manager->board->userCol=1;
}

