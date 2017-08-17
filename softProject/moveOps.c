/*
 * moveOps.c
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */

#include "moveOps.h"
#include "boardFuncs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "spArrayList.h"
#include "gameCommands.h"

#define MAX(x,y) (((x)>(y))?(x):(y))
#define MIN(x,y) (((x)>(y))?(y):(x))


void movePawn(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool secRow = false;
	if (rowPos==1 || rowPos==6) secRow=true;
	if (board->curPlayer==0){			//black player case
		if(rowDest==rowPos+1 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest){
			switchObj(board,rowPos,colPos,rowDest, colDest,BlackPawn);
			return;
		}
		else if (secRow){
			if(rowDest==rowPos+2 && board->boardArr[rowDest][colDest]==UNDERSCORE
					&& board->boardArr[rowPos+1][colDest]==UNDERSCORE && colPos==colDest){
				switchObj(board,rowPos,colPos,rowDest, colDest,BlackPawn);
				return;
			}
		}
		else if (rowDest==rowPos+1 && (colPos==colDest+1 || colPos==colDest-1)&&
				islower(board->boardArr[rowDest][colDest])){
			switchObj(board,rowPos,colPos,rowDest, colDest,BlackPawn);
			return;
			}
		}
	else if (board->curPlayer==1){			//white player case
		if(rowDest==rowPos-1 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest){
			switchObj(board,rowPos,colPos,rowDest, colDest,WhitePawn);
			return;
		}
		else if (secRow){
			if(rowDest==rowPos-2 && board->boardArr[rowDest][colDest]==UNDERSCORE
					&& colPos==colDest && board->boardArr[rowPos-1][colDest]==UNDERSCORE){
				switchObj(board,rowPos,colPos,rowDest, colDest,WhitePawn);
				return;
			}
		}
		else if (rowDest==rowPos-1 && (colPos==colDest+1 || colPos==colDest-1)&&
				isupper(board->boardArr[rowDest][colDest])){
			switchObj(board,rowPos,colPos,rowDest, colDest,WhitePawn);
			return;
			}
		}
	printf("Illegal move\n");
	return;

}

void moveRook(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos!=rowDest && colPos!=colDest){
		printf("Illegal move\n");
		return;
	}
	else if((board->curPlayer==0 && isupper(board->boardArr[rowDest][colDest]))
			|| (board->curPlayer==1 && islower(board->boardArr[rowDest][colDest]))){
		printf("Illegal move\n");
		return;
	}
	else{
		valid = isValidHorAndVar(board, rowPos, colPos, rowDest, colDest);
		if (valid==false){
			printf("Illegal move\n");
			return;
		}
		else{
			switchAndCheck(board,rowPos,colPos, rowDest, colDest, BlackRook, WhiteRook);
		}
	}
}

void moveBishop(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos==rowDest || colPos==colDest){
		printf("Illegal move\n");
		return;
	}
	valid = isValidDiagonal(board, rowPos, colPos,rowDest,colDest);
	if (valid==false){
		printf("Illegal move\n");
		return;
	}
	switchAndCheck(board,rowPos,colPos, rowDest, colDest, BlackBishop, WhiteBishop);
}


void moveKnight(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	if((rowPos==rowDest+2 || rowPos==rowDest-2)&& (colPos==colDest+1||colPos==colDest-1)){
		switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKnight, WhiteKnight);
		return;
	}
	else if((rowPos==rowDest+1 || rowPos==rowDest-1)&& (colPos==colDest+2||colPos==colDest-2)){
		switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKnight, WhiteKnight);
		return;
	}
	printf("Illegal move\n");
	return;

}
void moveKing(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	if(abs(rowPos-rowDest)>1 || abs(colPos-colDest)>1){
		printf("Illegal move\n");
		return;
	}
	else{
		switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKing, WhiteKing);
	}
}


void moveQueen(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	if (rowPos==rowDest || colPos==colDest){
		if(isValidHorAndVar(board, rowPos, colPos,rowDest,colDest)){
			switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackQueen, WhiteQueen);
			return;
		}
	}
	if (abs(rowPos-rowDest)==abs(colPos-colDest)){
		if(isValidDiagonal(board, rowPos, colPos,rowDest,colDest)){
			switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackQueen, WhiteQueen);
			return;
		}
	}
	printf("Illegal move\n");
	return;
}


bool isValidDiagonal(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);

	bool valid = false;
	if (abs(rowPos-rowDest)!=abs(colPos-colDest))return valid;
	else if(rowPos<rowDest && colPos<colDest){
			for(int i=rowPos+1, j=colPos+1; i<rowDest;i++,j++){
				if(board->boardArr[i][j]!=UNDERSCORE){
					return valid;
				}
			}
		}

	else if(rowPos<rowDest && colPos>colDest){
		for(int i=rowPos+1, j=colPos-1; i<rowDest;i++,j--){
			if(board->boardArr[i][j]!=UNDERSCORE){
				return valid;
			}
		}
	}
	else if(rowPos>rowDest && colPos<colDest){
		for(int i=rowPos-1, j=colPos+1; i>rowDest;i--,j++){
			if(board->boardArr[i][j]!=UNDERSCORE){
				return valid;
			}
		}
	}
	else if(rowPos>rowDest && colPos>colDest){
		for(int i=rowPos-1, j=colPos-1; i>rowDest;i--,j--){
			if(board->boardArr[i][j]!=UNDERSCORE){
				return valid;
			}
		}
	}
	return !valid;
}


bool isValidHorAndVar(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos==rowDest){
		if(colPos<colDest){
			for(int i=colPos+1;i<colDest;i++){
				if(board->boardArr[rowPos][i]!=UNDERSCORE){
					return valid;
				}
			}
		}
		else if(colDest<colPos){
			for(int i=colPos-1;i>colPos;i--){
				if(board->boardArr[rowPos][i]!=UNDERSCORE){
					return valid;
				}
			}
		}
	}
	else if (colPos==colDest){
		if (rowPos<rowDest){
			for(int i=rowPos+1;i<rowDest;i++){
				if (board->boardArr[i][colDest]!=UNDERSCORE){
					return valid;
				}
			}
		}
		else if(rowDest<rowPos){
			for(int i=rowPos-1;i>rowDest;i--){
				if (board->boardArr[i][colDest]!=UNDERSCORE){
					return valid;
				}
			}
		}
	}
	return !valid;
}

void switchAndCheck(boardGame* board, int rowPos, int colPos, int rowDest, int colDest,char obj1, char obj2){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	if((board->curPlayer==0) && (board->boardArr[rowDest][colDest]==UNDERSCORE ||
		islower(board->boardArr[rowDest][colDest]))){
			switchObj(board, rowPos, colPos, rowDest, colDest,obj1);
		}
	else if((board->curPlayer==1) && (board->boardArr[rowDest][colDest]==UNDERSCORE ||
		isupper(board->boardArr[rowDest][colDest]))){
			switchObj(board, rowPos, colPos, rowDest, colDest,obj2);
		}
	else{
		printf("Illegal move\n");
		return;
	}
}

void switchObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, char obj){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	board->boardArr[rowPos][colPos] = UNDERSCORE;
	board->boardArr[rowDest][colDest] = obj;
}

void moveObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	if ((rowPos<0|| rowPos>7 || colPos<0|| colPos>7 || rowDest<0|| rowDest>7 || colDest<0|| colDest>7)||
		(board->boardArr[rowPos][colPos]==UNDERSCORE)){
			printf("Invalid position on the board\n");
			return;
	}
	else if ((board->curPlayer==0) && islower(board->boardArr[rowPos][colPos])){	//black and lower
		printf("The specified position does not contain your piece\n");
		return;
	}
	else if ((board->curPlayer==1) && isupper(board->boardArr[rowPos][colPos])){	//white and upper
		printf("The specified position does not contain your piece\n");
		return;
	}
	else if(rowPos==rowDest && colPos==colDest){
		printf("Illegal move\n");
		return;
	}
	char obj = board->boardArr[rowPos][colPos];
		 if (obj=='M' || obj =='m') movePawn(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='R' || obj =='r') moveRook(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='B' || obj =='b') moveBishop(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='N' || obj =='n') moveKnight(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='K' || obj =='k') moveKing(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='Q' || obj =='q') moveQueen(board,rowPos,colPos,rowDest,colDest);
	addMoveToHistory(board,rowPos,colPos,rowDest,colDest);
	changePlayer(board);

}


void addMoveToHistory(boardGame* board,int rowPos,int colPos,int rowDest,int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	if(spArrayListIsFull(board->history)){
		for(int i=0;i<4;i++){
			spArrayListRemoveFirst(board->history);
		}
	}
	int index = board->history->actualSize-1;
	board->history->elements[index] = RowColToNum(rowPos,colPos);
	board->history->elements[index+1] = (int) board->boardArr[rowPos][colPos];
	board->history->elements[index+2] =RowColToNum(rowDest,colDest);
	board->history->elements[index+3] = (int) board->boardArr[rowDest][colDest];
	board->history->actualSize+=4;
	return;

}

