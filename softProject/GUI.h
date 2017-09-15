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
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "mainWindowGUI.h"
#include "settingsWindowGUI.h"
#include "gameWindowGUI.h"


typedef struct MANAGER{
	boardGame* board;
	MainWindow* mw;
	SettingsWindow* sw;
	GameWindow* game;
} Manager;

Manager* createManager();
void destroyManager(Manager* manager);
void guiMain(boardGame* board);

#endif /* GUI_H_ */
