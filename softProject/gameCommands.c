/*
 * gameCommands.c
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gameCommands.h"
#include "boardFuncs.h"

void undo(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	if(board->gameMode==2){
		printf("Undo command not available in 2 players mode\n");
		return;
	}
	if(spArrayListIsEmpty(board->history)){
		printf("Empty history, move cannot be undone\n");
		return;
	}
	exUndo(board);
	for(int i=board->history->actualSize-1; i>board->history->actualSize-5;i--){
		spArrayListRemoveAt(board->history,i);
	}
	board->history->actualSize-=4;

	return;
}

void exUndo(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	int index = board->history->actualSize-1;
	char objDest = (char)board->history->elements[index];
	int posDest = board->history->elements[index-1];
	char objSource = (char)board->history->elements[index-2];
	int posDSource = board->history->elements[index-3];
	board->boardArr[NumToRow(posDest)][NumToCol(posDest)] = objDest;
	board->boardArr[NumToRow(posDSource)][NumToCol(posDSource)] = objSource;
	if(board->curPlayer==0){
		printf("Undo move for player %s : <%d,%d> -> <%d,%d>\n",
		BLACK,NumToRow(posDSource)+1,NumToCol(posDSource)+1,NumToRow(posDest)+1,NumToCol(posDest)+1);
	}
	else if(board->curPlayer==1){
		printf("Undo move for player %s : <%d,%d> -> <%d,%d>\n",
		WHITE,NumToRow(posDSource)+1,NumToCol(posDSource)+1,NumToRow(posDest)+1,NumToCol(posDest)+1);
	}
	changePlayer(board);
	return;

}

int NumToRow(int num){
	int row = num/8;
	return row;
}

int NumToCol(int num){
	int col = num%8;
	return col;
}

int RowColToNum(int row, int col){
	int num = 8*row + col;
	return num;
}


void changePlayer(boardGame* board){
	assert(board!=NULL);
	if(board->curPlayer==0) board->curPlayer=1;
	else if (board->curPlayer==1) board->curPlayer=0;
}
