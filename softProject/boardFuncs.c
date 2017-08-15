/*
 * boardFuncs.c
 *
 *  Created on: 11 баев„ 2017
 *      Author: Itamar
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "commandsFuncs.h"

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

boardGame* createBoard(){
	boardGame* board = (boardGame*)malloc(sizeof(boardGame));
	assert(board!=NULL);
	for (int i=0;i<ROW;i++){
		for (int j=0;j<COL;j++){
			board->boardArr[i][j]=UNDERSCORE;
		}
	}
	board->gameMode = 1;
	board->diffLevel = 2;
	board->userCol = 1;				//1 - white; 0 - black;
	board->curPlayer = 1;			//1 = white player, 0 = black player
	return board;
}

void initBoard(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	for(int i=0;i<8;i++){
		board->boardArr[1][i] = BlackPawn;
		board->boardArr[6][i] = WhitePawn;
	}
	board->boardArr[7][0] = WhiteRook; board->boardArr[7][7] = WhiteRook;
	board->boardArr[0][0] = BlackRook; board->boardArr[0][7] = BlackRook;
	board->boardArr[7][1] = WhiteKnight; board->boardArr[7][6] = WhiteKnight;
	board->boardArr[0][1] = BlackKnight; board->boardArr[0][6] = BlackKnight;
	board->boardArr[7][2] = WhiteBishop; board->boardArr[7][5] = WhiteBishop;
	board->boardArr[0][2] = BlackBishop; board->boardArr[0][5] = BlackBishop;
	board->boardArr[7][3] = WhiteQueen; board->boardArr[7][4] = WhiteKing;
	board->boardArr[0][3] = BlackQueen; board->boardArr[0][4] = BlackKing;


}

void printBoard(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	for(int i=0;i<ROW;i++){
		printf("%d%c",8-i,PIPE);
		for(int j=0;j<COL;j++){
			printf(" %c",board->boardArr[i][j]);
		}
		printf(" %c\n",PIPE);
	}
	printf("  ");
	for (int k=0;k<17;k++){
		printf("%c",HYPHEN);
	}
	printf(" \n");
	printf("   ");
	printf("A B C D E F G H  \n");
}

void destroyBoard(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->userCol!=NULL);
	free(board->boardArr);
	free(board->userCol);
	free(board);
}


void setDifficult(boardGame* board, int num){
	assert(board!=NULL);
	board->diffLevel = num;
}

void boardPrintSet(boardGame*board){
	assert(board!=NULL);
	printf("SETTINGS:/n");
	if(board->gameMode==1){
		printf("GAME MODE: %d",board->gameMode);
		return;}
	else{
		printf("GAME MODE: %d",board->gameMode);
		printf("DIFFICULTY_LVL: %d",board->diffLevel);
		printf("USER_CLR: %s",board->userCol);
		return;
	}
}
