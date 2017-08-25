/*
 * boardFuncs.h
 *
 *  Created on: 11 ����� 2017
 *      Author: Itamar
 */

#ifndef BOARDFUNCS_H_
#define BOARDFUNCS_H_

#include "SPArrayList.h"

typedef struct boardGame{
	char boardArr[8][8];
	SPArrayList* history;
	int gameMode;
	int diffLevel;
	int userCol;
	int curPlayer;
}boardGame;

#define ROW 8
#define COL 8
#define PIPE '|'
#define UNDERSCORE '_'
#define HYPHEN '-'
#define BlackPawn 'M'
#define WhitePawn 'm'
#define BlackBishop 'B'
#define WhiteBishop 'b'
#define BlackRook 'R'
#define WhiteRook 'r'
#define BlackKnight 'N'
#define WhiteKnight 'n'
#define BlackQueen 'Q'
#define WhiteQueen 'q'
#define BlackKing 'K'
#define WhiteKing 'k'


boardGame* createBoard();
void initBoard(boardGame* board);
void printBoard(boardGame* board);
void destroyBoard(boardGame* board);
void setDifficult(boardGame* board, int num);
void setColor(boardGame* board, int num);
void boardPrintSet(boardGame*board);
void setNumPlayers(boardGame* board, int num);
boardGame* copyBoard(boardGame*board);


#endif /* BOARDFUNCS_H_ */
