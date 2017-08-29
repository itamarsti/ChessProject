/*
 * gameCommands.h
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */

#ifndef GAMECOMMANDS_H_
#define GAMECOMMANDS_H_

#include <stdbool.h>
#include "boardFuncs.h"

#define BLACK "black"
#define WHITE "white"


#include "boardFuncs.h"
#include "gameParser.h"
#include <stdbool.h>
#include "gameFlow.h"
#include "settingParser.h"

void undo(boardGame* board);
void exUndo(boardGame* board);
void changePlayer(boardGame* board);
int NumToRow(int num);
int NumToCol(int num);
int RowColToNum(int row, int col);
void quit(boardGame* board);
void reset(boardGame* board);
void saveFile(boardGame* board, GameCommand* cmd);


#endif /* GAMECOMMANDS_H_ */
