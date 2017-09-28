/*
 * gameWindowGUI.h
 *
 *  Created on: 14 ����� 2017
 *      Author: Itamar
 */

#ifndef GAMEWINDOWGUI_H_
#define GAMEWINDOWGUI_H_


#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "boardFuncs.h"
#include "gameCommands.h"
#include <SDL.h>
#include <SDL_video.h>
#include "gameParser.h"
#include "loadWindowGUI.h"


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
	SDL_Texture* blackPawn;
	SDL_Texture* blackRook;
	SDL_Texture* blackBishop;
	SDL_Texture* blackKnight;
	SDL_Texture* blackQueen;
	SDL_Texture* blackKing;
	SDL_Texture* whitePawn;
	SDL_Texture* whiteRook;
	SDL_Texture* whiteBishop;
	SDL_Texture* whiteKnight;
	SDL_Texture* whiteQueen;
	SDL_Texture* whiteKing;
	//SDL_Texture* greenLight;
	//SDL_Texture* redLight;
	//SDL_Texture* yellowLight;
}GameWindow;


typedef enum {
	GAME_WINDOW_DRAG_OBJ,
	//GAME_WINDOW_DRAG_LIGHT,
	GAME_WINDOW_PUSH_OBJ,
	//GAME_WINDOW_PUSH_LIGHT,
	GAME_WINDOW_PUSH_LOAD_GAME,
	GAME_WINDOW_PUSH_SAVE_GAME,
	GAME_WINDOW_PUSH_RESTART_GAME,
	GAME_WINDOW_PUSH_UNDO,
	GAME_WINDOW_PUSH_MAIN_MENU,
	GAME_WINDOW_PUSH_EVENT_QUIT,
	//GAME_WINDOW_HOVER_LOAD_GAME,
	//GAME_WINDOW_HOVER_SAVE_GAME,
	//GAME_WINDOW_HOVER_RESTART_GAME,
	//GAME_WINDOW_HOVER_UNDO,
	//GAME_WINDOW_HOVER_MAIN_MENU,
	//GAME_WINDOW_HOVER_EVENT_QUIT,
	GAME_WINDOW_HOVER_OBJ,
	//GAME_WINDOW_HOVER_LIGHT,
	GAME_WINDOW_EVENT_NONE,
	GAME_WINDOW_INVALID
} GAME_WINDOW_EVENT;

void createGR(GameWindow* gw, bool undoBool, bool loadBool);
GameWindow* createGW();
void destroyGameWindow(GameWindow* gw);
void destroyGameRenderer(GameWindow* gw);
void drawGameWindow(GameWindow* gw, boardGame* board);
GAME_WINDOW_EVENT gameWindowHandleEvent(GameWindow* mw, SDL_Event* event);
bool isClickOnSaveGame(int x, int y);
void saveGameFromGUI(boardGame* game, int numOfFiles);
bool isClickOnLoadGameWindow(int x, int y);
bool isClickOnQuitGameWindow(int x, int y);
bool isClickOnRestart(int x, int y);
bool isClickOnUndo(int x, int y);
bool isClickOnMainMenu(int x, int y);
void gameWindowHide(GameWindow* gw);
void gameWindowShow(GameWindow* gw);
int saveGameMessageBox();
int fromPixToPos(int x, int y);
bool isPixToPos(int x, int y);
void drawGameWindowImproved(GameWindow* gw, boardGame* board, SDL_Point* p1, SDL_Point* p2);
void createGameLoadTexture(GameWindow* gw, bool loadBool);
void createGameUndoTexture(GameWindow* gw, bool undoBool);
void createGameSaveTexture(GameWindow* gw, bool saveBool);

#endif /* GAMEWINDOWGUI_H_ */
