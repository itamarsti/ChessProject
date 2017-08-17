/*
 * moveOps.h
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */

#ifndef MOVEOPS_H_
#define MOVEOPS_H_

#include "boardFuncs.h"

void movePawn(boardGame* board, int xPos, int yPos, int xDest, int yDest);
void moveBishop(boardGame* board, int xPos, int yPos, int xDest, int yDest);
void moveRook(boardGame* board, int xPos, int yPos, int xDest, int yDest);
void moveKnight(boardGame* board, int xPos, int yPos, int xDest, int yDest);
void moveKing(boardGame* board, int xPos, int yPos, int xDest, int yDest);
void moveQueen(boardGame* board, int xPos, int yPos, int xDest, int yDest);

bool isValidDiagonal(boardGame* board, int rowPos, int colPos, int rowDest, int colDest);
bool isValidHorAndVar(boardGame* board, int rowPos, int colPos, int rowDest, int colDest);
void moveObj(boardGame* board, int xPos, int yPos, int xDest, int yDest);
void switchObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, char obj);
void switchAndCheck(boardGame* board, int rowPos, int colPos, int rowDest, int colDest,char obj1, char obj2);
#endif /* MOVEOPS_H_ */
