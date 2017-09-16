/*
 * loadWindowGUI.h
 *
 *  Created on: 16 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef LOADWINDOWGUI_H_
#define LOADWINDOWGUI_H_

#include "boardFuncs.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

typedef struct LOADWINDOW{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bg;
	SDL_Texture* load;
	SDL_Texture* back; SDL_Texture* slot5;
	SDL_Texture* slot4;
	SDL_Texture* slot1;
	SDL_Texture* slot2;
	SDL_Texture* slot3;
}LoadWindow;



typedef enum {
	LOAD_WINDOW_PUSH_LOAD,
	LOAD_WINDOW_HOVER_LOAD,
	LOAD_WINDOW_PUSH_BACK,
	LOAD_WINDOW_HOVER_BACK,
	LOAD_WINDOW_SLOT1,
	LOAD_WINDOW_SLOT2,
	LOAD_WINDOW_SLOT3,
	LOAD_WINDOW_SLOT4,
	LOAD_WINDOW_SLOT5,
	LOAD_WINDOW_EVENT_QUIT,
	LOAD_WINDOW_EVENT_NONE,
	LOAD_WINDOW_INVALID
}LOAD_WINDOW_EVENT;



LoadWindow* createLW(int slotsNum);
LoadWindow* createLR(LoadWindow* lw, int slotsNum, bool backLightened, int slotLight, bool loadLight);
void destroyLoadWindow(LoadWindow* lw);
void destroyLoadRenderer(LoadWindow* lw);
int numOfFilesInDir();
void loadFilePath(boardGame*board, char* path);
void loadRemoveChangeFile(int numOfFiles, int fileDeleted,boardGame* game);
void drawLoadWindow(LoadWindow* lw, int slotsNum);
LOAD_WINDOW_EVENT loadWindowHandleEvent(LoadWindow* lw, SDL_Event* event);
bool isClickOnSlot1(int x, int y);
bool isClickOnSlot2(int x, int y);
bool isClickOnSlot3(int x, int y);
bool isClickOnSlot4(int x, int y);
bool isClickOnSlot5(int x, int y);
bool isClickOnBackLW(int x, int y);
bool isClickOnLoadSlot(int x, int y);
void loadWindowHide(LoadWindow* lw);
void loadWindowShow(LoadWindow* lw);

#endif /* LOADWINDOWGUI_H_ */
