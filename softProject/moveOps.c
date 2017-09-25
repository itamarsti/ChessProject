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


bool movePawn(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	//printf("move pawn was acted\n");
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	bool secRow = false;
	if ((rowPos==1 && board->curPlayer==0) || (rowPos==6 && board->curPlayer==1)) secRow=true;
	if (board->curPlayer==0){			//black player case
		if(rowDest==rowPos+1 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
			//if(valid) printf( "valid");
			return valid;
		}
		else if((rowDest==rowPos+2 && board->boardArr[rowDest][colDest]==UNDERSCORE
					&& board->boardArr[rowPos+1][colDest]==UNDERSCORE && colPos==colDest)
				&& secRow){
				valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
				//if(valid) printf( "valid");
				return valid;
			}
		else if (rowDest==rowPos+1 && (colPos==colDest+1 || colPos==colDest-1)&&
				islower(board->boardArr[rowDest][colDest])){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
			//if(valid) printf( "valid");
			return valid;
			}
		}
	else if (board->curPlayer==1){			//white player case
		if(rowDest==rowPos-1 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
			//if(valid) printf( "valid");
			return valid;
		}
		else if((rowDest==rowPos-2 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest && board->boardArr[rowPos-1][colDest]==UNDERSCORE)
				 && secRow){
				valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
				//if(valid) printf( "valid");
				return valid;
			}
		else if (rowDest==rowPos-1 && (colPos==colDest+1 || colPos==colDest-1)&&
				isBlackPlayer(board->boardArr[rowDest][colDest])){
			//printf("was in this term\n");
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
			//if(valid) printf( "valid");
			return valid;
			}
		}
	if(doPrint) printf("Illegal move\n");
	return false;

}

bool moveRook(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos!=rowDest && colPos!=colDest){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	if((board->curPlayer==0 && isupper(board->boardArr[rowDest][colDest]))
			|| (board->curPlayer==1 && islower(board->boardArr[rowDest][colDest]))){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	valid = isValidHorAndVar(board, rowPos, colPos, rowDest, colDest);
	if (valid==false){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	valid = switchAndCheck(board,rowPos,colPos, rowDest, colDest, BlackRook, WhiteRook, doPrint);
	return valid;
}

bool moveBishop(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos==rowDest || colPos==colDest){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	valid = isValidDiagonal(board, rowPos, colPos,rowDest,colDest);
	if (valid==false){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	valid = switchAndCheck(board,rowPos,colPos, rowDest, colDest, BlackBishop, WhiteBishop, doPrint);
	return valid;
}


bool moveKnight(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if((rowPos==rowDest+2 || rowPos==rowDest-2)&& (colPos==colDest+1||colPos==colDest-1)){
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKnight, WhiteKnight, doPrint);
		return valid;
	}
	else if((rowPos==rowDest+1 || rowPos==rowDest-1)&& (colPos==colDest+2||colPos==colDest-2)){
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKnight, WhiteKnight, doPrint);
		return valid;
	}
	if(doPrint) printf("Illegal move\n");
	return false;

}
bool moveKing(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if(abs(rowPos-rowDest)>1 || abs(colPos-colDest)>1){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	else{
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKing, WhiteKing, doPrint);
		return valid;
	}
}


bool moveQueen(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	//printf("move queen was acted\n");
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if (rowPos==rowDest || colPos==colDest){
		//printf("straight was acted\n");
		if(isValidHorAndVar(board, rowPos, colPos,rowDest,colDest)){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackQueen, WhiteQueen, doPrint);
			return valid;
		}
	}
	else if (abs(rowPos-rowDest)==abs(colPos-colDest)){
		//printf("diagonal was acted\n");
		if(isValidDiagonal(board, rowPos, colPos,rowDest,colDest)){
			//printf("isvalidDiagnoal is true\n");
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackQueen, WhiteQueen, doPrint);
			//if(valid) printf("switch and check is true\n");
			//if(!valid) printf("switch and check false\n");
			return valid;
		}
	}
	if(doPrint) printf("Illegal move\n");
	return false;
}


bool isValidDiagonal(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if (abs(rowPos-rowDest)!=abs(colPos-colDest))return valid;
	if(rowPos<rowDest && colPos<colDest){
			for(int i=rowPos+1, j=colPos+1; i<rowDest;i++,j++){
				if(board->boardArr[i][j]!=UNDERSCORE){
					return valid;
				}
			}
		}
	if(rowPos<rowDest && colPos>colDest){
		for(int i=rowPos+1, j=colPos-1; i<rowDest;i++,j--){
			if(board->boardArr[i][j]!=UNDERSCORE){
				return valid;
			}
		}
	}
	if(rowPos>rowDest && colPos<colDest){
		for(int i=rowPos-1, j=colPos+1; i>rowDest;i--,j++){
			if(board->boardArr[i][j]!=UNDERSCORE){
				return valid;
			}
		}
	}
	if(rowPos>rowDest && colPos>colDest){
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
			for(int i=colPos-1;i>colDest;i--){
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

bool switchAndCheck(boardGame* board, int rowPos, int colPos, int rowDest, int colDest,char obj1, char obj2, bool print){
	//printf("switch and check was acted from %d,%d to %d,%d", rowPos, colPos, rowDest, colDest);
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	boardGame* copy = copyBoard(board);
	assert(copy!=NULL); assert(copy->boardArr!=NULL);
	if((board->curPlayer==0) && (board->boardArr[rowDest][colDest]==UNDERSCORE ||
		islower(board->boardArr[rowDest][colDest]))){
			//printf("is my king safe 0 was acted");
			switchObj(copy, rowPos, colPos, rowDest, colDest,obj1,false);
			valid = isMyKingSafe(copy);
			//if(!valid) printf("king is not safe for move from %d,%d to %d,%d", rowPos, colPos, rowDest, colDest);
			destroyBoard(copy);
			if(valid){
				switchObj(board, rowPos, colPos, rowDest, colDest,obj1,true);
				return true;
			}
		}
	else if((board->curPlayer==1) && (board->boardArr[rowDest][colDest]==UNDERSCORE ||
		isupper(board->boardArr[rowDest][colDest]))){
		//printf("is my king safe 1 was acted");
		switchObj(copy, rowPos, colPos, rowDest, colDest,obj2,false);
		valid = isMyKingSafe(copy);
		//if(!valid) printf("the king is not safe");
		destroyBoard(copy);
		if(valid){
			switchObj(board, rowPos, colPos, rowDest, colDest,obj2,true);
			return true;
		}
	}
	if(print) printf("Illegal move\n");
	return false;
}

void switchObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, char obj,bool chaPla){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	addMoveToHistory(board,rowPos,colPos,rowDest,colDest);
	board->boardArr[rowPos][colPos] = UNDERSCORE;
	board->boardArr[rowDest][colDest] = obj;
	if(chaPla) changePlayer(board);
}

bool moveObj(boardGame* board,int position, int destination,bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool validMove = false;
	//printf("the position is:%d, the destinetion is:%d\n",position,destination);
	int rowPos = NumToRow(position);
	int colPos = NumToCol(position);
	int rowDest = NumToRow(destination);
	int colDest = NumToCol(destination);
	if ((rowPos<0|| rowPos>7 || colPos<0|| colPos>7 || rowDest<0|| rowDest>7 || colDest<0|| colDest>7)){
		if(doPrint) printf("Invalid position on the board\n");
		return false;
	}
	else if ((board->curPlayer==0) && (islower(board->boardArr[rowPos][colPos])
			|| board->boardArr[rowPos][colPos]==UNDERSCORE)){	//black and lower
		if(doPrint) printf("The specified position does not contain your piece\n");
		return false;
	}
	else if ((board->curPlayer==1) && (isupper(board->boardArr[rowPos][colPos])
			|| board->boardArr[rowPos][colPos]==UNDERSCORE)){	//white and upper
		if(doPrint)printf("The specified position does not contain your piece\n");
		return false;
	}
	else if(rowPos==rowDest && colPos==colDest){
		if(doPrint)printf("Illegal move\n");
		return false;
	}
	char obj = board->boardArr[rowPos][colPos];
		 if (obj=='M' || obj =='m') validMove = movePawn(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj=='R' || obj =='r') validMove = moveRook(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj=='B' || obj =='b') validMove = moveBishop(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj=='N' || obj =='n') validMove = moveKnight(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj=='K' || obj =='k') validMove = moveKing(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj=='Q' || obj =='q') validMove = moveQueen(board,rowPos,colPos,rowDest,colDest, doPrint);
	return validMove;	//change player and add move to history are in switchObj func.
}

bool isMyKingSafe(boardGame* board){

	assert(board!=NULL);
	bool safe = false;
	int position = -1;
	if(board->curPlayer==1){
		//printf("ismyKingSafe1 Function was activated\n");
		position = trackKingPosition(board, WhiteKing);
		if(position==-1){
			printf("whiteKing wasn't found"); // never suppose to act
			return true;
		}
		safe = safeArea(board, position,WhiteKing);
		//if(safe) printf("it's safe  here 1\n");
		//if(!safe) printf("it's not safe here1\n");

	}
	else if (board->curPlayer==0){
		//printf("ismyKingSafe 0 Function was activated\n");
		position = trackKingPosition(board, BlackKing);
		if(position==-1){
			printf("whiteKing wasn't found");  //never suppose to act
			return true;
		}
		safe = safeArea(board, position,BlackKing);
		//if(safe) printf("it's safe here 0\n");
		//if(!safe) printf("it's not safe here0\n");
	}
	//if(safe) printf("the king is safe\n");
	return safe;
}

bool safeArea(boardGame* board,int position,char symbol){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	int row = NumToRow(position);
	int col = NumToCol(position);
	bool safe = true;
	if((safe = isSafeStraight(board,row, col, symbol))==false) return false;	//covers queen&rook
	if((safe = isSafeDiagnoal(board,row, col, symbol))==false) return false;	//covers queen&bishop
	if((safe = isSafeFromKingAndKnight(board,row, col, symbol))==false) return false;	//covers king&knight
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
	int i = 1;
	if(symbol==WhiteKing){
		while (row+i<ROW && col+i<COL){
			if(board->boardArr[row+i][col+i]==UNDERSCORE) i++;
			else if(board->boardArr[row+i][col+i]==BlackBishop||board->boardArr[row+i][col+i]==BlackQueen)
				return false;
			else break;
		}
		i = 1;
		while (row-i>=0 && col+i<COL){
			if(board->boardArr[row-i][col+i]==UNDERSCORE) i++;
			else if(board->boardArr[row-i][col+i]==BlackBishop||board->boardArr[row-i][col+i]==BlackQueen)
				return false;
			else break;
		}
		i = 1;
		while (row-i>=0 && col-i>=0){
			if(board->boardArr[row-i][col-i]==UNDERSCORE) i++;
			else if(board->boardArr[row-i][col-i]==BlackBishop||board->boardArr[row-i][col-i]==BlackQueen)
				return false;
			else break;
		}
		i = 1;
		while (row+i<ROW && col-i>=0){
			if(board->boardArr[row+i][col-i]==UNDERSCORE) i++;
			else if(board->boardArr[row+i][col-i]==BlackBishop||board->boardArr[row+i][col-i]==BlackQueen)
				return false;
			else break;
		}
	}
	else if(symbol==BlackKing){
		while (row+i<ROW && col+i<COL){
			if(board->boardArr[row+i][col+i]==UNDERSCORE) i++;
			else if(board->boardArr[row+i][col+i]==WhiteBishop||board->boardArr[row+i][col+i]==WhiteQueen)
				return false;
			else break;
		}
		i = 1;
		while (row-i>=0 && col+i<COL){
			if(board->boardArr[row-i][col+i]==UNDERSCORE) i++;
			else if(board->boardArr[row-i][col+i]==WhiteBishop||board->boardArr[row-i][col+i]==WhiteQueen)
				return false;
			else break;
		}
		i = 1;
		while (row-i>=0 && col-i>=0){
			if(board->boardArr[row-i][col-i]==UNDERSCORE) i++;
			else if(board->boardArr[row-i][col-i]==WhiteBishop||board->boardArr[row-i][col-i]==WhiteQueen)
				return false;
			else break;
		}
		i = 1;
		while (row+i<ROW && col-i>=0){
			if(board->boardArr[row+i][col-i]==UNDERSCORE) i++;
			else if(board->boardArr[row+i][col-i]==WhiteBishop||board->boardArr[row+i][col-i]==WhiteQueen)
				return false;
			else break;
		}
	}
	return true;
}

bool isSafeFromKingAndKnight(boardGame* board,int row, int col,char symbol){
	if(symbol==WhiteKing){
		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(board->boardArr[i][j]==BlackKing){
					if ((abs(i-row)==1 && abs(j-col)==1)|| (abs(i-row)==1 && abs(j-col)==0)
						||(abs(i-row)==0 && abs(j-col)==1))return false;
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
					if ((abs(i-row)==1 && abs(j-col)==1)|| (abs(i-row)==1 && abs(j-col)==0)
						||(abs(i-row)==0 && abs(j-col)==1))return false;
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
	spArrayListAddLast(board->history, RowColToNum(rowPos,colPos));
	spArrayListAddLast(board->history, (int) board->boardArr[rowPos][colPos]);
	spArrayListAddLast(board->history, RowColToNum(rowDest,colDest));
	spArrayListAddLast(board->history, (int) board->boardArr[rowDest][colDest]);
	return;
}

