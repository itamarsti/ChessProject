/*
 * moveOps.h
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */

#ifndef MOVEOPS_H_
#define MOVEOPS_H_

#include "boardFuncs.h"
#include "gameParser.h"

bool movePawn(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint);
bool moveBishop(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool moveRook(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool moveKnight(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool moveKing(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool moveQueen(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool isValidDiagonal(boardGame* board, int rowPos, int colPos, int rowDest, int colDest);
bool isValidHorAndVar(boardGame* board, int rowPos, int colPos, int rowDest, int colDest);
bool moveObj(boardGame* board,int position, int destination,bool doPrint);
void switchObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, char obj,bool changePlayer);
bool switchAndCheck(boardGame* board, int rowPos, int colPos, int rowDest, int colDest,char obj1, char obj2, bool print);
void addMoveToHistory(boardGame* board,int rowPos,int colPos,int rowDest,int colDest);
int trackKingPosition(boardGame* board, char symbol);
bool isMyKingSafe(boardGame* board);
bool safeArea(boardGame* board,int position,char symbol);
bool isSafeStraight(boardGame* board,int row, int col,char symbol);
bool isSafeDiagnoal(boardGame* board,int row, int col,char symbol);
bool isSafeFromKingAndKnight(boardGame* board,int row, int col,char symbol);
bool isSafeFromPawn(boardGame* board,int row, int col,char symbol);


#endif /* MOVEOPS_H_ */
