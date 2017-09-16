/*
 * gameCommands.h
 *
 *  Created on: 17 баев„ 2017
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
#include "alphaBetaMinMax.h"

void undo(boardGame* board,bool printActivate, bool playerChangeAcivate);
void exUndo(boardGame* board,bool printActivate);
void changePlayer(boardGame* board);
int NumToRow(int num);
int NumToCol(int num);
int RowColToNum(int row, int col);
void quit(boardGame* board);
void reset(boardGame* board);
void saveFile(boardGame* board, const char* path);
void moveMessage(boardGame* board);
void printCheckMessage(int player);
bool isCheckMate(boardGame* board);
bool isThereOptionMove(boardGame* board,int row,int col);
void terminateGame(boardGame* board,bool mate, bool tie);
bool isWhitePlayer(char c);
bool isBlackPlayer(char c);
void getMovesFunc(boardGame* board,int position);
void getMovesPrintFunc(boardGame* copy, bool valid1, int rowDest, int colDest, int dest);
bool isWinner(boardGame* board);
bool isTie(boardGame* board);
void moveAIobj(boardGame* board);
void computerMoveMessage(boardGame* board, int position, int destination);
bool checkPawnPromotion(boardGame* board);

#endif /* GAMECOMMANDS_H_ */
