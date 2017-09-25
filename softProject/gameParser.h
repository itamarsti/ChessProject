/*
 * gameParser.h
 *
 *  Created on: 19 баев„ 2017
 *      Author: Itamar
 */

#ifndef GAMEPARSER_H_
#define GAMEPARSER_H_

#include <stdbool.h>
#include "gameCommands.h"
#include "gameParser.h"

typedef enum {
	MOVE,
	GET_MOVES,
	SAVE,
	INVALID_SAVE,
	UNDO,
	RESET,
	QUIT2,
	INVALID_LINE2,
	INVALID_POSITION
} GAME_COMMAND;

typedef struct g_command {
	GAME_COMMAND cmd;
	bool validArg; //is set to true if the line contains a valid argument
	int position;
	int destination;
	char* path;
} GameCommand;


char* gameAcceptor();
GameCommand* gameParser(const char* str);
bool isFileCreated(const char* path);
int isTri(char* str);
void destroyGameStruct(GameCommand* cmd);



#endif /* GAMEPARSER_H_ */
