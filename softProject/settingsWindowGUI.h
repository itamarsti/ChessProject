/*
 * settingsWindowGUI.h
 *
 *  Created on: 12 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef SETTINGSWINDOWGUI_H_
#define SETTINGSWINDOWGUI_H_



#include "boardFuncs.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>


/**
 * The structure which saves the elements in Settings Window GUI:
 * 		1. window - window element
 * 		2. renderer - the renderer element
 * 		3. bg - the backGround photo element
 * 		4. mode - texture
 * 		5. gameMode1 - button
 * 		6. gameMode2 - button
 * 		7. color - texture
 * 		8. colWhite - button
 * 		9. colBlack - button
 * 		10. difficulty - texture
 * 		11. noob - button
 * 		12. easy - button
 * 		13. moderate - button
 * 		14. hard - button
 * 		15. back - button
 * 		16. start - button
 */

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
	SETTINGS_WINDOW_PUSH_BACK,
	SETTINGS_WINDOW_PUSH_START,
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
//bool isClickOnExpert(int x, int y);
bool isClickOnStart(int x, int y);
bool isClickOnBack(int x, int y);
void destroySettingsRenderer(SettingsWindow* sw);
void destroySettingsWindow(SettingsWindow* sw);
SettingsWindow* createSW(int numPlayers, int color, int diffi);
SettingsWindow* createSR(SettingsWindow* sw, int numPlayers, int color, int diffi);
SETTINGS_WINDOW_EVENT settingsWindowHandleEvent(SettingsWindow* sw, SDL_Event* event);
void drawSettingsWindow(SettingsWindow* sw);
void createGameMode1Texture(SettingsWindow* sw, int numPlayers);
void createGameMode2Texture(SettingsWindow* sw, int numPlayers);
void createGameNoobTexture(SettingsWindow* sw, int numPlayers);
void createGameEasyTexture(SettingsWindow* sw, int numPlayers);
void createGameModerateTexture(SettingsWindow* sw, int numPlayers);
void createGameHardTexture(SettingsWindow* sw, int numPlayers);
void createGameDifficultyDecider(SettingsWindow* sw, int diffiOld, int diffiNew);
void createSetWhiteTexture(SettingsWindow* sw, int numPlayers);
void createSetBlackTexture(SettingsWindow* sw, int numPlayers);
void settingsWindowHide(SettingsWindow* sw);
void settingsWindowShow(SettingsWindow* sw);
int settingsWindowGuiManager(SettingsWindow* sw, boardGame* board);
void difficultyHelper(SettingsWindow* sw, boardGame* board, int difficulty);
void gameModeHelper(SettingsWindow* sw, boardGame* board, int gameMode);
void userColorHelper(SettingsWindow* sw, boardGame* board, int userCol);
#endif /* SETTINGSWINDOWGUI_H_ */
