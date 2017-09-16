/*
 * loadWindowGUI.h
 *
 *  Created on: 16 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef LOADWINDOWGUI_H_
#define LOADWINDOWGUI_H_


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
	SDL_Texture* slot1;
	SDL_Texture* slot2;
	SDL_Texture* slot3;
	SDL_Texture* slot4;
}LoadWindow;


typedef enum {
	LOAD_WINDOW_LOAD_GAME,
	LOAD_WINDOW_NEW_GAME,
	LOAD_WINDOW_EVENT_QUIT,
	LOAD_WINDOW_EVENT_NONE,
	LOAD_WINDOW_INVALID
}LOAD_WINDOW_EVENT;



LoadWindow* createLW();
void destroyLoadWindow(LoadWindow* lw);
void drawLoadWindow(LoadWindow* lw);
LOAD_WINDOW_EVENT loadWindowHandleEvent(LoadWindow* lw, SDL_Event* event);
bool isClickOnSlot1(int x, int y);
bool isClickOnSlot2(int x, int y);
bool isClickOnSlot3(int x, int y);
bool isClickOnSlot4(int x, int y);
bool isClickOnSlot5(int x, int y);
bool isClickOnBack(int x, int y);
bool isClickOnLoadSlot(int x, int y);
void loadWindowHide(LoadWindow* lw);
void loadWindowShow(LoadWindow* lw);

#endif /* LOADWINDOWGUI_H_ */
