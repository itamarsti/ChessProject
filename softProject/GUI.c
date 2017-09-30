/*
 * GUI.c
 *
 *  Created on: 31 баев„ 2017
 *      Author: Itamar
 */

/**
 * GUI summary:
 *
 * The main GUI section. This part includes the creation of the general Manager data structure,
 * handling and managing the whole GUI operations, includes switching between windows.
 *
 *
 *
 * createManager					- Creating the Manager data Structure
 * destroyManager					- Destroying the Manager data Structure
 * guiMain							- The handler of the operations and switches
 * checkMessageWarning				- GUI Message box in case of checkmate/check/tie
 * saveMessageDialog				- Pop-up message box in case the game was saved
 * slotDialog						- Pop-up message box in case the weren't left saved games
 * quitGame							- Terminate the game and free the memory
 * savePleaseMessageDialog			- GUI Message Box asking if to save the game
 * livingOnTheEdge					- Checking if there was checkmate/check/tie
 *
 *
 *
 *
 *
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
		if(mainBool){
			initBoard(manager->board,true);
			setDefault(manager->board);
			manager->mw = (MainWindow*) createMW();
			if(manager->mw==NULL) {
				printf("ERROR: Couldn't create MainWindow struct\n");
				quitGame(manager);
			}
			mainBool = false;
			int handle = mainWindowGuiManager(manager->mw);
			if(handle==1) quitGame(manager);
			else if(handle==2){
				loadBool = true;
				backMainBool = true;
			}
			else if(handle==3)settingsBool = true;
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
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~Beginning of load window~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		else if(loadBool){
			manager->lw = (LoadWindow*) createLW();
			if(manager->lw==NULL) {
				printf("ERROR: Couldn't create LoadWindow struct\n");
				quitGame(manager);
			}
			loadBool = false;
			int handleLoad = loadWindowGuiManager(manager->lw, manager->board,backGameBool,backMainBool);
			if(handleLoad==1) quitGame(manager);
			else if(handleLoad==2  || handleLoad==4){
				if (handleLoad==2) backGameBool = false;
				gameBool = true;
			}
			else if (handleLoad==3){
				backMainBool = false;
				mainBool = true;
			}
		}
		//-----------------------------------End of Load Window--------------------------------
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Beginning of game window~~~~~~~~~~~~~~~~~~~~~~~~~~
		else if(gameBool){
			manager->gw = (GameWindow*) createGW();
			if(manager->gw==NULL) {
				printf("ERROR: Couldn't create GameWindow struct\n");
				quitGame(manager);
			}
			drawGameWindow(manager->gw, manager->board);
			bool gameSaved = true; gameBool = false; bool quit = false;
			while(!quit){
				bool undoBool = manager->board->history->actualSize>4 ? true:false;
				bool loadInsideBool = numOfFilesInDir()>0 ? true: false;
				if(manager->board->gameMode==1 && manager->board->curPlayer!=manager->board->userCol){
					moveAIobj(manager->board, false);
					if(manager->board->history->actualSize>4){
						createGameUndoTexture(manager->gw, true);
					}
					createGameSaveTexture(manager->gw,true);
					drawGameWindow(manager->gw, manager->board);
					gameSaved = false;
					int edge =  livingOnTheEdge(manager->board);
					if(edge==2 || edge==3){
						destroyGameWindow(manager->gw);
						quitGame(manager);
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
								printf("Error: Save MessagBox couldn't be opened");
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
								undo(manager->board, false, true);
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
						destroyGameWindow(manager->gw);
						loadBool = true; backGameBool = true; quit = true;
						break;
					}
					else if (gameWindowHandleEvent(manager->gw, &event3) == GAME_WINDOW_PUSH_MAIN_MENU){
						if(!gameSaved){
							int save = saveGameMessageBox();
							if(save ==2) continue;	//cancel
							else if(save==-1){		//error
								printf("Error: Save MessagBox couldn't be opened");
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
						destroyGameWindow(manager->gw);
						mainBool = true; gameSaved = true;quit = true;
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
										gameSaved = false;
										int edge =  livingOnTheEdge(manager->board);
										if(edge==2 || edge==3){
											destroyGameWindow(manager->gw);
											quitGame(manager);
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


/**
 *
 * Creating the Manager structure using SDL.
 * In this part we create the Board and allocating space in memory for the Manager
 *
 * @return
 * Manager pointer of the data Structure
 *
 */

Manager* createManager(){
	Manager* manager = (Manager*) malloc(sizeof(Manager));
	if(manager==NULL){
		printf("ERROR: coudln't create manager struct\n");
		return NULL;
	}
	manager->board = createBoard();
	if(manager->board==NULL){
		printf("ERROR: couldn't create boardGame in GUI\n");
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


/**
 *
 * Destroying the Manager data structure with it's elements and free the memory.
 *
 * @param manager -Manager data structure
 *
 * @return
 * void
 *
 */

void destroyManager(Manager* manager){
	if(manager==NULL) return;
	if(manager->board!=NULL) destroyBoard(manager->board);
	free(manager);
	return;
}


/**
 *
 * Showing Message Warning if there was check/checkmate/tie
 *
 * @param curPlayer - the current player
 * @param check - true/false for check
 * @param mate	- true/false for checkmate
 * @param tie	- true/false for tie
 * @param gameMode - the current gameMode
 * @param userCol - the User Color
 *
 * @return
 * Manager pointer of the data Structure
 *
 */

void checkMessageWarning(int curPlayer,bool check, bool mate, bool tie, int gameMode, int userCol){
	if(check){
		if(gameMode==2 || (gameMode==1 && curPlayer!=userCol)){
			if(curPlayer==1){
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Check Message",
						"Check! white king is threatened!",NULL);
				}
			else if (curPlayer==0){
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Check Message",
						"Check! black king is threatened!",NULL);
			}
		}
		else if(gameMode ==1 && curPlayer==userCol){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,"Check Message",
					"Check!",NULL);
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


/**
 *
 * Showing pop-up which announcing the game was saved.
 *
 * @return
 * void
 *
 */

void saveMessageDialog(){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Save Message",
		"Game was saved!",NULL);
}

/**
 *
 * Showing pop-up which announcing to make some move before the user's can save the game
 *
 * @return
 * void
 *
 */

void savePleaseMessageDialog(){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Save Message",
		"Please make a move before SAVING!",NULL);
}


/**
 *
 * Showing pop-up which announcing there weren't left any saveg games to load from
 *
 * @return
 * void
 *
 */


void slotDialog(){
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Load Message",
		"There are no saved Games!",NULL);
}


/**
 *
 * Exiting the game in GUI mode by destroying the Manager data structure and print if
 * to the command line
 *
 * @param manager - Manager Data Structure
 *
 * @return
 * void
 *
 */

void quitGame(Manager* manager){
	if(manager!=NULL){
		destroyManager(manager);
		SDL_Quit();
		printf("Exiting...");
		exit(0);
	}
}

/**
 *
 * This function checking if there was checkMate, check or tie and activating
 * the Message function.
 *
 * @param board - boardGame Data Structure
 *
 * @return
 * integer between 1-3:
 * 	1 - for Check
 * 	2 - for CheckMate
 * 	3 - for Tie
 *
 */

int livingOnTheEdge(boardGame* board){
	bool kingSafe = isMyKingSafe(board);
	bool checkMate = isCheckMate(board);
	if(kingSafe==false && checkMate==false){
		checkMessageWarning(board->curPlayer, true, false, false, board->gameMode,board->userCol);
		return 1;
	}
	else if(kingSafe==false && checkMate==true){
		checkMessageWarning(board->curPlayer, false, true, false,board->gameMode,board->userCol);
		return 2;
	}
	else if(kingSafe==true && checkMate==true){
		checkMessageWarning(board->curPlayer, false, false, true,board->gameMode,board->userCol);
		return 3;
	}
	return 0;
}

