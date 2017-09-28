/*
 * GUI.h
 *
 *  Created on: 31 ����� 2017
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
bool loadSection(Manager* manager, int numOfFiles, int fileRemove);
void checkMessageWarning(int curPlayer,bool check, bool mate, bool tie);
void saveGameFromGUI(boardGame* game, int numOfFiles);
void saveMessageDialog();
void slotDialog();
void quitGame(Manager* manager);
void savePleaseMessageDialog();


#endif /* GUI_H_ */
