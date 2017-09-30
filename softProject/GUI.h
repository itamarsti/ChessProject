/*
 * GUI.h
 *
 *  Created on: 31 баев„ 2017
 *      Author: Itamar
 */

#ifndef GUI_H_
#define GUI_H_

#include "boardFuncs.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include "mainWindowGUI.h"
#include "settingsWindowGUI.h"
#include "gameWindowGUI.h"
#include "loadWindowGUI.h"
#include "alphaBetaMinMax.h"
#include "gameCommands.h"



/**
 *
 * The structure which saves the GUI Manager:
 * 		1. board - boardGame Data Structure
 * 		2. mw - MainWindow Data Structure
 * 		3. sw - SettingsWindow Data Structure
 * 		4. gw - GameWindow Data Structure
 * 		5. lw - LoadWindow Data Structure
 *
 */


typedef struct MANAGER{
	boardGame* board;
	MainWindow* mw;
	SettingsWindow* sw;
	GameWindow* gw;
	LoadWindow* lw;
} Manager;



Manager* createManager();
void destroyManager(Manager* manager);
void guiMain();
void checkMessageWarning(int curPlayer,bool check, bool mate, bool tie, int gameMode, int userCol);
void saveMessageDialog();
void slotDialog();
void quitGame(Manager* manager);
void savePleaseMessageDialog();
int livingOnTheEdge(boardGame* board);

#endif /* GUI_H_ */
