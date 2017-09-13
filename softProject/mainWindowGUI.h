/*
 * mainWindowGUI.h
 *
 *  Created on: 11 ����� 2017
 *      Author: Itamar
 */

#ifndef MAINWINDOWGUI_H_
#define MAINWINDOWGUI_H_


#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>


typedef struct MAINWINDOW{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bg;
	SDL_Texture* welcome;
	SDL_Texture* newGame;
	SDL_Texture* loadGame;
	SDL_Texture* quit;
}MainWindow;


typedef enum {
	MAIN_WINDOW_LOAD_GAME,
	MAIN_WINDOW_NEW_GAME,
	MAIN_WINDOW_EVENT_QUIT,
	MAIN_WINDOW_EVENT_NONE,
	MAIN_WINDOW_INVALID
} MAIN_WINDOW_EVENT;



MainWindow* createMW();
void destroyMainWindow(MainWindow* mw);
void drawMainWindow(MainWindow* mw);
MAIN_WINDOW_EVENT mainWindowHandleEvent(MainWindow* mw, SDL_Event* event);
bool isClickOnNewGame(int x, int y);
bool isClickOnLoadGame(int x, int y);
bool isClickOnQuit(int x, int y);
void mainWindowHide(MainWindow* mw);
void mainWindowShow(MainWindow* mw);

#endif /* MAINWINDOWGUI_H_ */
