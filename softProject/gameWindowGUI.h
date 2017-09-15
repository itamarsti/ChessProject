/*
 * gameWindowGUI.h
 *
 *  Created on: 14 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef GAMEWINDOWGUI_H_
#define GAMEWINDOWGUI_H_


#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>


typedef struct GAMEWINDOW{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bg;
	SDL_Texture* restart;
	SDL_Texture* saveGame;
	SDL_Texture* loadGame;
	SDL_Texture* undo;
	SDL_Texture* mainMenu;
	SDL_Texture* quit;
}GameWindow;


typedef enum {
	GAME_WINDOW_LOAD_GAME,
	GAME_WINDOW_SAVE_GAME,
	GAME_WINDOW_RESTART_GAME,
	GAME_WINDOW_UNDO,
	GAME_WINDOW_MAIN_MENU,
	GAME_WINDOW_EVENT_QUIT,
	GAME_WINDOW_EVENT_NONE,
	GAME_WINDOW_INVALID
} GAME_WINDOW_EVENT;



GameWindow* createGW();
void destroyGameWindow(GameWindow* gw);
void drawGameWindow(GameWindow* gw);
GAME_WINDOW_EVENT gameWindowHandleEvent(GameWindow* mw, SDL_Event* event);
//bool isClickOnNewGame(int x, int y);
//bool isClickOnLoadGame(int x, int y);
//bool isClickOnQuit(int x, int y);
void gameWindowHide(GameWindow* gw);
void gameWindowShow(GameWindow* gw);


#endif /* GAMEWINDOWGUI_H_ */
