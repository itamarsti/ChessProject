/*
 * gameParser.h
 *
 *  Created on: 19 баев„ 2017
 *      Author: Itamar
 */

#ifndef GAMEPARSER_H_
#define GAMEPARSER_H_

#include <stdbool.h>


/*
 * all the possible Game commands Messeages.
 */
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


/**
 * The struct saving the game commands and their availability.
 */
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
int NumToRow(int num);
int NumToCol(int num);
int RowColToNum(int row, int col);



#endif /* GAMEPARSER_H_ */
