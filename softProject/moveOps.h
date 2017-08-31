/*
 * moveOps.h
 *
 *  Created on: 17 ����� 2017
 *      Author: Itamar
 */

#ifndef MOVEOPS_H_
#define MOVEOPS_H_

#include "boardFuncs.h"
#include "gameParser.h"

bool movePawn(boardGame* board, int xPos, int yPos, int xDest, int yDest);
bool moveBishop(boardGame* board, int xPos, int yPos, int xDest, int yDest);
bool moveRook(boardGame* board, int xPos, int yPos, int xDest, int yDest);
bool moveKnight(boardGame* board, int xPos, int yPos, int xDest, int yDest);
bool moveKing(boardGame* board, int xPos, int yPos, int xDest, int yDest);
bool moveQueen(boardGame* board, int xPos, int yPos, int xDest, int yDest);
bool isValidDiagonal(boardGame* board, int rowPos, int colPos, int rowDest, int colDest);
bool isValidHorAndVar(boardGame* board, int rowPos, int colPos, int rowDest, int colDest);
bool moveObj(boardGame* board, GameCommand* command);
void switchObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, char obj);
bool switchAndCheck(boardGame* board, int rowPos, int colPos, int rowDest, int colDest,char obj1, char obj2);
void addMoveToHistory(boardGame* board,int rowPos,int colPos,int rowDest,int colDest);
#endif /* MOVEOPS_H_ */
