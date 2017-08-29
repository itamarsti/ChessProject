/*
 * gameCommands.h
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */

#ifndef GAMECOMMANDS_H_
#define GAMECOMMANDS_H_


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "boardFuncs.h"
#include "gameParser.h"
#include "settingParser.h"
#include "SPArrayList.h"



#define BLACK "black"
#define WHITE "white"


void saveFile(boardGame* board,GameCommand* cmd);
void printInvalidMes(GAME_COMMAND cmd);
void undo(boardGame* board);
void exUndo(boardGame* board);
void changePlayer(boardGame* board);
int NumToRow(int num);
int NumToCol(int num);
int RowColToNum(int row, int col);
void quit(boardGame* board);
void reset(boardGame* board);


#endif /* GAMECOMMANDS_H_ */
