/*
 * boardFuncs.h
 *
 *  Created on: 11 баев„ 2017
 *      Author: Itamar
 */

#ifndef BOARDFUNCS_H_
#define BOARDFUNCS_H_


typedef struct boardGame{
	char boardArr[8][8];
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



#endif /* BOARDFUNCS_H_ */
