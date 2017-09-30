/*
 * loadWindowGUI.h
 *
 *  Created on: 17 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef LOADWINDOWGUI_H_
#define LOADWINDOWGUI_H_

#include "boardFuncs.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <dirent.h>
#include <SDL.h>
#include <SDL_video.h>


/**
 * The type of the events to handle with in Load Window.
 */

typedef enum{
	LOAD_WINDOW_EVENT_QUIT,
	LOAD_WINDOW_EVENT_NONE,
	LOAD_WINDOW_INVALID,
	LOAD_WINDOW_GAME1SLOT,
	LOAD_WINDOW_GAME2SLOT,
	LOAD_WINDOW_GAME3SLOT,
	LOAD_WINDOW_GAME4SLOT,
	LOAD_WINDOW_GAME5SLOT,
	LOAD_WINDOW_PUSH_BACK,
	LOAD_WINDOW_PUSH_LOAD,
}LOAD_WINDOW_EVENT;


/**
 * The structure which saves the elements in Load Window GUI:
 * 		1. window - window element
 * 		2. renderer - the renderer element
 * 		3. bg - the backGround photo element
 * 		4. slot1 - button
 * 		5. slot2 - button
 * 		6. slot3 - button
 * 		7. slot4 - button
 * 		8. slot5 - button
 * 		9. back - button
 * 		10. load - button
 */


typedef struct LOADWINDOW{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bg;
	SDL_Texture* slot1;
	SDL_Texture* slot2;
	SDL_Texture* slot3;
	SDL_Texture* slot4;
	SDL_Texture* slot5;
	SDL_Texture* back;
	SDL_Texture* load;

}LoadWindow;


LoadWindow* createLW();
void createLR(LoadWindow* lw, int slotsNum, int slotLight, bool loadLight);
void destroyLoadWindow(LoadWindow* lw);
void destroyLoadRenderer(LoadWindow* lw);
int numOfFilesInDir();
void loadFilePath(boardGame*board, char* path);
void loadRemoveChangeFile(int numOfFiles, int fileDeleted,boardGame* game, LoadWindow* lw);
void drawLoadWindow(LoadWindow* lw, int slotsNum);
LOAD_WINDOW_EVENT loadWindowHandleEvent(LoadWindow* lw, SDL_Event* event);
bool isClickOnSlot1(int x, int y);
bool isClickOnSlot2(int x, int y);
bool isClickOnSlot3(int x, int y);
bool isClickOnSlot4(int x, int y);
bool isClickOnSlot5(int x, int y);
bool isClickOnLWBack(int x, int y);
bool isClickOnLWLoad(int x, int y);
void createBackTexture(LoadWindow* lw);
void createLoadTexture(LoadWindow* lw, int slotLight, bool loadLight);
void loadWindowHide(LoadWindow* lw);
void loadWindowShow(LoadWindow* lw);
int loadWindowGuiManager(LoadWindow* lw, boardGame* board, bool backGameBool, bool backMainBool);
#endif /* LOADWINDOWGUI_H_ */
