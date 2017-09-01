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


bool movePawn(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool secRow = false;
	if (rowPos==1 || rowPos==6) secRow=true;
	if (board->curPlayer==0){			//black player case
		if(rowDest==rowPos+1 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest){
			switchObj(board,rowPos,colPos,rowDest, colDest,BlackPawn);
			return true;
		}
		else if (secRow){
			if(rowDest==rowPos+2 && board->boardArr[rowDest][colDest]==UNDERSCORE
					&& board->boardArr[rowPos+1][colDest]==UNDERSCORE && colPos==colDest){
				switchObj(board,rowPos,colPos,rowDest, colDest,BlackPawn);
				return true;
			}
		}
		else if (rowDest==rowPos+1 && (colPos==colDest+1 || colPos==colDest-1)&&
				islower(board->boardArr[rowDest][colDest])){
			switchObj(board,rowPos,colPos,rowDest, colDest,BlackPawn);
			return true;
			}
		}
	else if (board->curPlayer==1){			//white player case
		if(rowDest==rowPos-1 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest){
			switchObj(board,rowPos,colPos,rowDest, colDest,WhitePawn);
			return true;
		}
		else if (secRow){
			if(rowDest==rowPos-2 && board->boardArr[rowDest][colDest]==UNDERSCORE
					&& colPos==colDest && board->boardArr[rowPos-1][colDest]==UNDERSCORE){
				switchObj(board,rowPos,colPos,rowDest, colDest,WhitePawn);
				return true;
			}
		}
		else if (rowDest==rowPos-1 && (colPos==colDest+1 || colPos==colDest-1)&&
				isupper(board->boardArr[rowDest][colDest])){
			switchObj(board,rowPos,colPos,rowDest, colDest,WhitePawn);
			return true;
			}
		}
	printf("Illegal move\n");
	return false;

}

bool moveRook(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos!=rowDest && colPos!=colDest){
		printf("Illegal move\n");
		return false;
	}
	else if((board->curPlayer==0 && isupper(board->boardArr[rowDest][colDest]))
			|| (board->curPlayer==1 && islower(board->boardArr[rowDest][colDest]))){
		printf("Illegal move\n");
		return false;
	}
	else{
		valid = isValidHorAndVar(board, rowPos, colPos, rowDest, colDest);
		if (valid==false){
			printf("Illegal move\n");
			return false;
		}
		else{
			switchAndCheck(board,rowPos,colPos, rowDest, colDest, BlackRook, WhiteRook);
			return true;
		}
	}
}

bool moveBishop(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos==rowDest || colPos==colDest){
		printf("Illegal move\n");
		return false;
	}
	valid = isValidDiagonal(board, rowPos, colPos,rowDest,colDest);
	if (valid==false){
		printf("Illegal move\n");
		return false;
	}
	valid = switchAndCheck(board,rowPos,colPos, rowDest, colDest, BlackBishop, WhiteBishop);
	return valid;
}


bool moveKnight(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if((rowPos==rowDest+2 || rowPos==rowDest-2)&& (colPos==colDest+1||colPos==colDest-1)){
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKnight, WhiteKnight);
		return valid;
	}
	else if((rowPos==rowDest+1 || rowPos==rowDest-1)&& (colPos==colDest+2||colPos==colDest-2)){
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKnight, WhiteKnight);
		return valid;
	}
	printf("Illegal move\n");
	return false;

}
bool moveKing(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if(abs(rowPos-rowDest)>1 || abs(colPos-colDest)>1){
		printf("king cant move");
		printf("Illegal move\n");
		return false;
	}
	else{
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKing, WhiteKing);
		return valid;
	}
}


bool moveQueen(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if (rowPos==rowDest || colPos==colDest){
		if(isValidHorAndVar(board, rowPos, colPos,rowDest,colDest)){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackQueen, WhiteQueen);
			return valid;
		}
	}
	if (abs(rowPos-rowDest)==abs(colPos-colDest)){
		if(isValidDiagonal(board, rowPos, colPos,rowDest,colDest)){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackQueen, WhiteQueen);
			return valid;
		}
	}
	printf("Illegal move\n");
	return false;
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

bool switchAndCheck(boardGame* board, int rowPos, int colPos, int rowDest, int colDest,char obj1, char obj2){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	if((board->curPlayer==0) && (board->boardArr[rowDest][colDest]==UNDERSCORE ||
		islower(board->boardArr[rowDest][colDest]))){
			switchObj(board, rowPos, colPos, rowDest, colDest,obj1);
			return true;
		}
	else if((board->curPlayer==1) && (board->boardArr[rowDest][colDest]==UNDERSCORE ||
		isupper(board->boardArr[rowDest][colDest]))){
			switchObj(board, rowPos, colPos, rowDest, colDest,obj2);
			return true;
		}
	else{
		printf("Illegal move\n");
		return false;
	}
}

void switchObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, char obj){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	board->boardArr[rowPos][colPos] = UNDERSCORE;
	board->boardArr[rowDest][colDest] = obj;
}

bool moveObj(boardGame* board, GameCommand* command){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(command!=NULL);
	fflush(stdout);
	bool validMove = false;
	int rowPos = NumToRow(command->position);
	int colPos = NumToCol(command->position);
	int rowDest = NumToRow(command->destination);
	int colDest = NumToCol(command->destination);
	if ((rowPos<0|| rowPos>7 || colPos<0|| colPos>7 || rowDest<0|| rowDest>7 || colDest<0|| colDest>7)||
		(board->boardArr[rowPos][colPos]==UNDERSCORE)){
			printf("Invalid position on the board\n");
			return false;
	}
	else if ((board->curPlayer==0) && islower(board->boardArr[rowPos][colPos])){	//black and lower
		printf("The specified position does not contain your piece\n");
		return false;
	}
	else if ((board->curPlayer==1) && isupper(board->boardArr[rowPos][colPos])){	//white and upper
		printf("The specified position does not contain your piece\n");
		return false;
	}
	else if(rowPos==rowDest && colPos==colDest){
		printf("Illegal move\n");
		return false;
	}
	char obj = board->boardArr[rowPos][colPos];
		 if (obj=='M' || obj =='m') validMove = movePawn(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='R' || obj =='r') validMove = moveRook(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='B' || obj =='b') validMove = moveBishop(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='N' || obj =='n') validMove = moveKnight(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='K' || obj =='k') validMove = moveKing(board,rowPos,colPos,rowDest,colDest);
	else if (obj=='Q' || obj =='q') validMove = moveQueen(board,rowPos,colPos,rowDest,colDest);
    if(!validMove) return validMove;
    else if(validMove) addMoveToHistory(board,rowPos,colPos,rowDest,colDest);
    printf("move was done\n");
	validMove = isMyKingSafe(board);
	if (validMove) changePlayer(board);
	else if(!validMove){
		undo(board,false,false);		//no need to change player
		printf("Illegal move\n");
	}
	return validMove;
}

bool isMyKingSafe(boardGame* board){
	assert(board!=NULL);
	bool safe = false;
	int position = -1;
	if(board->curPlayer==1){
		position = trackKingPosition(board, WhiteKing);
		if(position==-1){
			printf("whiteKing wasn't found");
			return true;
		}
		safe = safeArea(board, position,WhiteKing);
		if(!safe) printf("not safe\n");
	}
	else if (board->curPlayer==0){
		position = trackKingPosition(board, BlackKing);
		if(position==-1){
			printf("whiteKing wasn't found");
			return true;
		}
		safe = safeArea(board, position,BlackKing);
	}
	return safe;
}

bool safeArea(boardGame* board,int position,char symbol){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	int row = NumToRow(position);
	int col = NumToCol(position);
	bool safe = true;
	printf("safe straight\n");
	if((safe = isSafeStraight(board,row, col, symbol))==false) return false;	//covers queen&rook
	printf("safe diagnoal\n");
	if((safe = isSafeDiagnoal(board,row, col, symbol))==false) return false;	//covers queen&bishop
	printf("safe kingAndKnight\n");
	if((safe = isSafeFromKingAndKnight(board,row, col, symbol))==false) return false;	//covers king&knight
	printf("safe pawn\n");
	if((safe = isSafeFromPawn(board,row, col, symbol))==false) return false;	//covers pawn
	return true;
}

bool isSafeStraight(boardGame* board,int row, int col,char symbol){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	if(symbol==WhiteKing){
		for(int i=row+1;i<ROW;i++){
			if(board->boardArr[i][col]==UNDERSCORE) continue;
			else if(board->boardArr[i][col]==BlackRook||board->boardArr[i][col]==BlackQueen)
				return false;
			else break;
		}
		for(int i=row-1;i>=0;i--){
			if(board->boardArr[i][col]==UNDERSCORE) continue;
			else if(board->boardArr[i][col]==BlackRook||board->boardArr[i][col]==BlackQueen)
				return false;
			else break;
		}
		for(int i=col+1;i<COL;i++){
			if(board->boardArr[row][i]==UNDERSCORE) continue;
			else if(board->boardArr[row][i]==BlackRook||board->boardArr[row][i]==BlackQueen)
				return false;
			else break;
		}
		for(int i=col-1;i>=0;i--){
			if(board->boardArr[row][i]==UNDERSCORE) continue;
			else if(board->boardArr[row][i]==BlackRook||board->boardArr[row][i]==BlackQueen)
				return false;
			else break;
		}
	}
	else if(symbol==BlackKing){
		for(int i=row+1;i<ROW;i++){
			if(board->boardArr[i][col]==UNDERSCORE) continue;
			else if(board->boardArr[i][col]==WhiteRook||board->boardArr[i][col]==WhiteQueen)
				return false;
			else break;
		}
		for(int i=row-1;i>=0;i--){
			if(board->boardArr[i][col]==UNDERSCORE) continue;
			else if(board->boardArr[i][col]==WhiteRook||board->boardArr[i][col]==WhiteQueen)
				return false;
			else break;
		}
		for(int i=col+1;i<COL;i++){
			if(board->boardArr[row][i]==UNDERSCORE) continue;
			else if(board->boardArr[row][i]==WhiteRook||board->boardArr[row][i]==WhiteQueen)
				return false;
			else break;
		}
		for(int i=col-1;i>=0;i--){
			if(board->boardArr[row][i]==UNDERSCORE) continue;
			else if(board->boardArr[row][i]==WhiteRook||board->boardArr[row][i]==WhiteQueen)
				return false;
			else break;
		}
	}
	return true;
}


bool isSafeDiagnoal(boardGame* board,int row, int col,char symbol){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	bool loopBreaker1 = false;
	bool loopBreaker2 = false;
	bool loopBreaker3 = false;
	bool loopBreaker4 = false;
	if(symbol==WhiteKing){
		for (int i=row+1;i<ROW;i++){
			if(loopBreaker1) break;
			printf("first loop\n");
			for (int j=col+1;j<COL;j++){
				if(board->boardArr[i][j]==UNDERSCORE) continue;
				else if(board->boardArr[i][j]==BlackBishop||board->boardArr[i][j]==BlackQueen)
					return false;
				else{
					loopBreaker1 = true;
					break;}}
		}
		for (int i=row+1;i<ROW;i++){
			if(loopBreaker2) break;
			printf("2 loop\n");
			for (int j=col-1;j>=0;j--){
				if(board->boardArr[i][j]==UNDERSCORE) continue;
				else if(board->boardArr[i][j]==BlackBishop||board->boardArr[i][j]==BlackQueen)
					return false;
				else{
					loopBreaker2 = true;
					break;}}
				}
		for (int i=row-1;i>=0;i--){
			if(loopBreaker3) break;
			printf("3 loop\n");
			for (int j=col+1;j<COL;j++){
				if(board->boardArr[i][j]==UNDERSCORE) continue;
				else if(board->boardArr[i][j]==BlackBishop||board->boardArr[i][j]==BlackQueen)
					return false;
				else{
					loopBreaker3 = true;
					break;}}
		}		for (int i=row-1;i>=0;i--){
			if(loopBreaker4) break;
			printf("4 loop\n");
			for (int j=col-1;j>=0;j--){
				if(board->boardArr[i][j]==UNDERSCORE) continue;
				else if(board->boardArr[i][j]==BlackBishop||board->boardArr[i][j]==BlackQueen)
					return false;
				else{
					loopBreaker4 = true;
					break;}}
		}
	}
	else if(symbol==BlackKing){
		for (int i=row+1;i<ROW;i++){
			if(loopBreaker1) break;
			for (int j=col+1;j<COL;j++){
				if(board->boardArr[i][j]==UNDERSCORE) continue;
				else if(board->boardArr[i][j]==WhiteBishop||board->boardArr[i][j]==WhiteQueen)
					return false;
				else{
					loopBreaker1 = true;
					break;}}
		}
		for (int i=row+1;i<ROW;i++){
			if(loopBreaker2) break;
			for (int j=col-1;j>=0;j--){
				if(board->boardArr[i][j]==UNDERSCORE) continue;
				else if(board->boardArr[i][j]==WhiteBishop||board->boardArr[i][j]==WhiteQueen)
					return false;
				else{
					loopBreaker2 = true;
					break;}}
		}
		for (int i=row-1;i>=0;i--){
			if(loopBreaker3) break;
			for (int j=col+1;j<COL;j++){
				if(board->boardArr[i][j]==UNDERSCORE) continue;
				else if(board->boardArr[i][j]==WhiteBishop||board->boardArr[i][j]==WhiteQueen)
					return false;
				else{
					loopBreaker3 = true;
					break;}}
		}
		for (int i=row-1;i>=0;i--){
			if(loopBreaker4) break;
			for (int j=col-1;j>=0;j--){
				if(board->boardArr[i][j]==UNDERSCORE) continue;
				else if(board->boardArr[i][j]==WhiteBishop||board->boardArr[i][j]==WhiteQueen)
					return false;
				else{
					loopBreaker4 = true;
					break;}}
		}
	}
	return true;
}

bool isSafeFromKingAndKnight(boardGame* board,int row, int col,char symbol){
	if(symbol==WhiteKing){
		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(board->boardArr[i][j]==BlackKing){
					if (abs(i-row)==1 && abs(j-col)==1) return false;
				}
				if(board->boardArr[i][j]==BlackKnight){
					if ((abs(i-row)==2 && abs(j-col)==1)||(abs(i-row)==1 && abs(j-col)==2))
						return false;
				}
			}
		}
	}
	else if(symbol==BlackKing){
		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(board->boardArr[i][j]==WhiteKing){
					if (abs(i-row)==1 && abs(j-col)==1) return false;
				}
				if(board->boardArr[i][j]==WhiteKnight){
					if ((abs(i-row)==2 && abs(j-col)==1)||(abs(i-row)==1 && abs(j-col)==2))
						return false;
				}
			}
		}
	}
	return true;
}


bool isSafeFromPawn(boardGame* board,int row, int col,char symbol){
	if(symbol==WhiteKing){
		if(row>0){
			if(col>=1 && col<=6){
				if(board->boardArr[row-1][col-1]==BlackPawn ||
					board->boardArr[row-1][col+1]==BlackPawn)return false;
			}
			else if(col==0){
				if(board->boardArr[row-1][col+1]==BlackPawn) return false;
			}
			else if(col==7){
				if(board->boardArr[row-1][col-1]==BlackPawn) return false;
			}
		}
	}
	else if(symbol==BlackKing){
		if(row<7){
			if(col>=1 && col<=6){
				if(board->boardArr[row+1][col-1]==WhitePawn ||
					board->boardArr[row+1][col+1]==WhitePawn)return false;
			}
			else if(col==0){
				if(board->boardArr[row+1][col+1]==WhitePawn) return false;
			}
			else if(col==7){
				if(board->boardArr[row+1][col-1]==WhitePawn) return false;
			}
		}
	}
	return true;
}


int trackKingPosition(boardGame* board, char symbol){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	for (int i=0;i<ROW;i++){
		for (int j=0;j<COL;j++){
			if (board->boardArr[i][j]==symbol) return RowColToNum(i,j);
		}
	}
	return -1;				// in case the king wasn't found
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

