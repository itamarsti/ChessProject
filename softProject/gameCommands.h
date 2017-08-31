/*
 * gameCommands.h
 *
 *  Created on: 17 ����� 2017
 *      Author: Itamar
 */

#ifndef GAMECOMMANDS_H_
#define GAMECOMMANDS_H_




#define BLACK "black"
#define WHITE "white"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "boardFuncs.h"
#include "gameParser.h"
#include "settingParser.h"
#include "SPArrayList.h"


void undo(boardGame* board);
void exUndo(boardGame* board);
void changePlayer(boardGame* board);
int NumToRow(int num);
int NumToCol(int num);
int RowColToNum(int row, int col);
void quit(boardGame* board);
void reset(boardGame* board);
void saveFile(boardGame* board, const char* path);
void moveMessage(boardGame* board);
void printCheckMessage(int player);



#endif /* GAMECOMMANDS_H_ */
