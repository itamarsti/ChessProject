/*
 * gameCommands.h
 *
 *  Created on: 17 ����� 2017
 *      Author: Itamar
 */

#ifndef GAMECOMMANDS_H_
#define GAMECOMMANDS_H_

#include <stdbool.h>
#include "boardFuncs.h"


typedef enum {
	MOVE,
	GET_MOVES,
	SAVE,
	UNDO,
	RESET,
	QUIT,
	INVALID_LINE
} GAME_COMMAND;

void undo(boardGame* board);
void exUndo(boardGame* board);
void changePlayer(boardGame* board);
int NumToRow(int num);
int NumToCol(int num);
int RowColToNum(int row, int col);


#endif /* GAMECOMMANDS_H_ */
