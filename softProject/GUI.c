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
	if(manager==NULL) printf("ERROR: creating Manager had failed\n");
	bool loadBool = false; bool settingsBool = false;bool gameBool = false;
	bool backMainBool = false; bool backGameBool = false; bool mainBool = true;
	while(1){
		if(mainBool) printf("~~~~~~~~~~~~main bool is true~~~~~~~~~~~~~~\n");
		else if(loadBool) printf("~~~~~~~~~~~~loadBool bool is true~~~~~~~~~~~~\n");
		else if(settingsBool) printf("~~~~~~~~~~~~settingsBool bool is true~~~~~~~~~~~~\n");
		else if(gameBool) printf("~~~~~~~~~~~~gameBool bool is true~~~~~~~~~~~~\n");
		//~~~~~~~~~Beginning of main window~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(mainBool){
			initBoard(manager->board,true);
			setDefault(manager->board);
			manager->mw = (MainWindow*) createMW();
			if(manager->mw==NULL) {
				printf("ERROR: Couldn't create MainWindow struct\n");
				quitGame(manager);
			}
			drawMainWindow(manager->mw);
			bool quitMain = false; mainBool = false;
			while(!quitMain){
				SDL_Event event;
				while(SDL_PollEvent(&event)!=0){
					if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_EVENT_QUIT) {
						destroyMainWindow(manager->mw);
						quitGame(manager);
					}
					else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_LOAD_GAME){
						destroyMainWindow(manager->mw);
						loadBool = true; backMainBool = true; quitMain = true;
						break;
					}
					else if (mainWindowHandleEvent(manager->mw, &event) == MAIN_WINDOW_NEW_GAME){
						destroyMainWindow(manager->mw);
						settingsBool = true; quitMain = true;
						break;
					}
				}
			}
		}
		//----------------------------End of main Window--------------------------------
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~Beginning of settings window~~~~~~~~~~~~~~~~~~~~~~
		else if(settingsBool){
			manager->sw = (SettingsWindow*) createSW(manager->board->gameMode,manager->board->userCol, manager->board->diffLevel);
			if(manager->sw==NULL) {
				printf("ERROR: Couldn't create SettingsWindow struct\n");
				quitGame(manager);
			}
			drawSettingsWindow(manager->sw);
			bool quitSettings = false; settingsBool = false;
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
						mainBool = true; quitSettings = true;
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_PUSH_START){
						destroySettingsWindow(manager->sw);
						gameBool = true; quitSettings = true;
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_1){
						createGameDifficultyDecider(manager->sw ,manager->board->diffLevel, 2);
						setNumPlayers(manager->board,1);
						createGameMode1Texture(manager->sw,  manager->board->gameMode);
						createGameMode2Texture(manager->sw, manager->board->gameMode);
						createSetWhiteTexture(manager->sw, 1);
						createSetBlackTexture(manager->sw, 1);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_GAME_MODE_2){
						setNumPlayers(manager->board,2);
						createGameMode1Texture(manager->sw,  manager->board->gameMode);
						createGameMode2Texture(manager->sw, manager->board->gameMode);
						createGameDifficultyDecider(manager->sw ,0, manager->board->diffLevel);
						createSetWhiteTexture(manager->sw, 0);
						createSetBlackTexture(manager->sw, 1);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_WHITE){
						if(manager->board->gameMode==2) continue;
						if(manager->board->userCol==1) continue;
						setColor(manager->board,1);
						createSetWhiteTexture(manager->sw, 1);
						createSetBlackTexture(manager->sw,1);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_BLACK){
						if(manager->board->gameMode==2) continue;
						if(manager->board->userCol==0) continue;
						setColor(manager->board,0);
						createSetWhiteTexture(manager->sw, 0);
						createSetBlackTexture(manager->sw, 0);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_1){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==1) continue;
						createGameDifficultyDecider(manager->sw ,manager->board->diffLevel, 1);
						setDifficult(manager->board,1);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_2){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==2) continue;
						createGameDifficultyDecider(manager->sw ,manager->board->diffLevel, 2);
						setDifficult(manager->board,2);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_3){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==3) continue;
						createGameDifficultyDecider(manager->sw ,manager->board->diffLevel, 3);
						setDifficult(manager->board,3);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_4){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==4) continue;
						createGameDifficultyDecider(manager->sw ,manager->board->diffLevel, 4);
						setDifficult(manager->board,4);
						drawSettingsWindow(manager->sw);
						break;
					}
					else if (settingsWindowHandleEvent(manager->sw, &event1) == SETTINGS_WINDOW_COL_DIFFICULTY_5){
						if(manager->board->gameMode==2) continue;
						if(manager->board->diffLevel==5) continue;
						createGameDifficultyDecider(manager->sw ,manager->board->diffLevel, 5);
						setDifficult(manager->board,5);
						drawSettingsWindow(manager->sw);
						break;
					}
				}
			}
		}
		//----------------------------End of Settings Window--------------------------------
		else if(loadBool){					//~~~~~~~~~Beginning of load window~~~~~~~~
			printf("at the begining of load window\n");
			int dirFiles = numOfFilesInDir();
			int fileRemove =0;
			manager->lw = (LoadWindow*) createLW();
			drawLoadWindow(manager->lw,dirFiles);
			loadBool = false;
			bool quitLoad = false;
			while(!quitLoad){
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
					createLR(manager->lw,dirFiles,fileRemove,true);
					drawLoadWindow(manager->lw,dirFiles);
					break;
					}
				}
			}
		}
		//----------------------------End of Load Window--------------------------------
							//~~~~~~~~~Beginning of game window~~~~~~~~
		else if(gameBool){
			manager->gw = (GameWindow*) createGW();
			drawGameWindow(manager->gw, manager->board);
			bool gameSaved = true;
			gameBool = false;
			bool quit = false;
			while(!quit){
				bool undoBool = manager->board->history->actualSize>4 ? true:false;
				bool loadInsideBool = numOfFilesInDir()>0 ? true: false;
				if(manager->board->gameMode==1 && manager->board->curPlayer!=manager->board->userCol){
					moveAIobj(manager->board);
					//destroyGameRenderer(manager->gw);
					//createGR(manager->gw,undoBool,loadInsideBool);
					if(manager->board->history->actualSize>4){
						createGameUndoTexture(manager->gw, true);
					}
					createGameSaveTexture(manager->gw,true);
					drawGameWindow(manager->gw, manager->board);
					gameSaved = false;
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
					else if(!(event3.type==SDL_MOUSEBUTTONUP && event3.button.button ==SDL_BUTTON_LEFT)
							&& !(event3.type==SDL_MOUSEBUTTONDOWN && event3.button.button ==SDL_BUTTON_LEFT)
							&&!(event3.type=SDL_MOUSEMOTION && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))){
						break;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_UNDO){
						if(manager->board->gameMode==1){
							if(manager->board->history->actualSize>4){
								undo(manager->board, false, true); //one more undo
								undo(manager->board, false, true);
								if(manager->board->history->actualSize<=4){
									createGameUndoTexture(manager->gw, false);
								}
								drawGameWindow(manager->gw, manager->board);
								gameSaved = false;
							}
						}
						continue;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_RESTART_GAME){
						initBoard(manager->board,false);
						createGameUndoTexture(manager->gw,false);
						createGameSaveTexture(manager->gw,false);
						drawGameWindow(manager->gw, manager->board);
						gameSaved = true;
						break;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_SAVE_GAME){
						if(!gameSaved){
							int files = numOfFilesInDir();
							saveGameFromGUI(manager->board,files);
							saveMessageDialog();
							createGameLoadTexture(manager->gw,true);
							createGameSaveTexture(manager->gw,false);
							drawGameWindow(manager->gw, manager->board);
							gameSaved = true;
						}
						else if(gameSaved) savePleaseMessageDialog();
						break;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_LOAD_GAME){
						int num = numOfFilesInDir();
						if(num==0) slotDialog();
						printf("in push load window\n");
						destroyGameWindow(manager->gw);
						loadBool = true;
						backGameBool = true;
						quit = true;
						printf("in here1\n");
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
					else if(gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_DRAG_OBJ){
						SDL_Point p1 = {.x = event3.button.x, .y = event3.button.y};
						//printf("xPos is :%d, yPos is:%d\n",p1.x,p1.y);
						bool done = false;
						while(!done){
							SDL_Event event8;
							while(SDL_PollEvent(&event8)!=0){
								SDL_Point p2 = {.x = event8.button.x, .y = event8.button.y};
								//printf("xDest is :%d, yDest is:%d\n",p2.x,p2.y);
								if(!(event3.type==SDL_MOUSEBUTTONUP && event3.button.button ==SDL_BUTTON_LEFT)
										&& !(event3.type==SDL_MOUSEBUTTONDOWN && event3.button.button ==SDL_BUTTON_LEFT)
										&&!(event3.type=SDL_MOUSEMOTION && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))){
									break;
								}
								else if(gameWindowHandleEvent(manager->gw, &event8)==GAME_WINDOW_HOVER_OBJ){
									//SDL_RenderClear(manager->gw->renderer);
									//destroyGameRenderer(manager->gw);
									//createGR(manager->gw,undoBool,loadInsideBool);
									drawGameWindowImproved(manager->gw, manager->board,&p1,&p2);
									continue;
								}
								else if (gameWindowHandleEvent(manager->gw, &event8)==GAME_WINDOW_PUSH_OBJ){
									SDL_Point p3 = {.x = event8.button.x, .y = event8.button.y};
									int pos = fromPixToPos(p1.x, p1.y);
									int dest = fromPixToPos(p3.x, p3.y);
									//printf("the position is:%d, the destination is: %d\n", pos, dest);
									if(moveObj(manager->board, pos, dest, false)){
										//SDL_RenderClear(manager->gw->renderer);
										if(manager->board->history->actualSize>4 && manager->board->gameMode==1){
											createGameUndoTexture(manager->gw, true);
										}
										createGameSaveTexture(manager->gw,true);
										drawGameWindow(manager->gw, manager->board);
										bool kingSafe = isMyKingSafe(manager->board);
										bool checkMate = isCheckMate(manager->board);
										gameSaved = false;
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
									else{
										drawGameWindow(manager->gw, manager->board);
									}
									done = true;
									break;
								}

								else{
									SDL_RenderClear(manager->gw->renderer);
									destroyGameRenderer(manager->gw);
									createGR(manager->gw,undoBool,loadInsideBool);
									drawGameWindow(manager->gw, manager->board);
									done = true;
									break;
								}

							}
						}
					}
				}
			}
		}
	}
}


Manager* createManager(){
	Manager* manager = (Manager*) malloc(sizeof(Manager));
	if(manager==NULL){
		printf("ERROR: coudln't create manager struct\n");
		return NULL;
	}
	manager->board = createBoard();
	if(manager->board==NULL){
		printf("ERROR couldn't create boardGame in GUI");
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

void savePleaseMessageDialog(){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Save Message",
		"Please make a move before SAVING!",NULL);
}

void slotDialog(){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Load Message",
		"There are no saved Games!",NULL);
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

