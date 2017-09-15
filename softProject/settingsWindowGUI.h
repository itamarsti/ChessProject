/*
 * settingsWindowGUI.h
 *
 *  Created on: 12 ����� 2017
 *      Author: Itamar
 */

#ifndef SETTINGSWINDOWGUI_H_
#define SETTINGSWINDOWGUI_H_



#include "boardFuncs.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>


typedef struct SETTINGSWINDOW{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bg;
	SDL_Texture* mode;
	SDL_Texture* gameMode1;
	SDL_Texture* gameMode2;
	SDL_Texture* color;
	SDL_Texture* colWhite;
	SDL_Texture* colBlack;
	SDL_Texture* difficulty;
	SDL_Texture* noob;
	SDL_Texture* easy;
	SDL_Texture* moderate;
	SDL_Texture* hard;
	SDL_Texture* back;
	SDL_Texture* start;
}SettingsWindow;


typedef enum {
	SETTINGS_WINDOW_BACK,
	SETTINGS_WINDOW_PLAY,
	SETTINGS_WINDOW_GAME_MODE_1,
	SETTINGS_WINDOW_GAME_MODE_2,
	SETTINGS_WINDOW_COL_WHITE,
	SETTINGS_WINDOW_COL_BLACK,
	SETTINGS_WINDOW_COL_DIFFICULTY_1,
	SETTINGS_WINDOW_COL_DIFFICULTY_2,
	SETTINGS_WINDOW_COL_DIFFICULTY_3,
	SETTINGS_WINDOW_COL_DIFFICULTY_4,
	SETTINGS_WINDOW_COL_DIFFICULTY_5,
	SETTINGS_WINDOW_EVENT_NONE,
	SETTINGS_WINDOW_INVALID,
	SETTINGS_WINDOW_EVENT_QUIT
} SETTINGS_WINDOW_EVENT;



bool isClickOnGameMode1(int x, int y);
bool isClickOnGameMode2(int x, int y);
bool isClickOnColWhite(int x, int y);
bool isClickOnColBlack(int x, int y);
bool isClickOnNoob(int x, int y);
bool isClickOnEasy(int x, int y);
bool isClickOnModerate(int x, int y);
bool isClickOnHard(int x, int y);
bool isClickOnExpert(int x, int y);
bool isClickOnPlay(int x, int y);
bool isClickOnBack(int x, int y);
void destroySettingsWindow(SettingsWindow* sw);
SettingsWindow* createSW();
SETTINGS_WINDOW_EVENT settingsWindowHandleEvent(SettingsWindow* sw, SDL_Event* event);
void drawSettingsWindow(SettingsWindow* sw);

#endif /* SETTINGSWINDOWGUI_H_ */