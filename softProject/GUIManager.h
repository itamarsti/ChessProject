/*
 * GUIManager.h
 *
 *  Created on: 13 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

#include "boardFuncs.h"
#include "gameCommands.h"
#include "mainWindowGUI.h"
#include "settingsWindowGUI.h"
#include <assert.h>
#include <stdBool.h>
#include "GUI.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

void quitGame1(Manager* manager);
void gameModeGUI1(Manager* manager, int numOfPlayers, int color, int difficulty);
void setBoardDefaultManager(Manager* manager);


#endif /* GUIMANAGER_H_ */



