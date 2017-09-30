/*
 * mainWindowGUI.h
 *
 *  Created on: 11 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef MAINWINDOWGUI_H_
#define MAINWINDOWGUI_H_


#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>

/**
 * The structure which saves the elements in main window GUI:
 * 		1. window - window element
 * 		2. renderer - the renderer element
 * 		3. bg - the backGround photo element
 * 		4. welcome - the welcome texture element
 * 		5. new game - button
 * 		6. loadGame - button
 * 		7. quit - button
 */

typedef struct MAINWINDOW{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bg;
	SDL_Texture* welcome;
	SDL_Texture* newGame;
	SDL_Texture* loadGame;
	SDL_Texture* quit;
}MainWindow;


/**
 * The type of the events to handle with in Main Window.
 */

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
int mainWindowGuiManager(MainWindow* mw);


#endif /* MAINWINDOWGUI_H_ */
