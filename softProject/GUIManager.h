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

void quitGame(Manager* manager);
void gameModeGUI(Manager* manager, int numOfPlayers, int color, int difficulty);


#endif /* GUIMANAGER_H_ */



