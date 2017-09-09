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
#include "gameParser.h"
#include "settingParser.h"
#include "moveOps.h"
include SPMiniMax



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

void quit(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	free(board->history->elements);
	free(board->history);
	free(board->boardArr);
	free(board);
	printf("Exiting...\n");
	exit(0);
}

void reset(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	spArrayListDestroy(board->history);
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	destroyBoard(board);
	printf("Restarting...\n");
	return;
}



void saveFile(boardGame* board, const char* path){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(path!=NULL);
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	if(!isFileCreated(path)){
			printf("File cannot be created or modified\n");
			return;
		}
	FILE* file = (FILE*) fopen(path,"w");
	assert(file!=NULL);
	fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",file);
	fputs("<game>\n",file);
	fprintf(file,"\t<current_turn>%d</current_turn>\n",board->curPlayer);
	fprintf(file,"\t<game_mode>%d</game_mode>\n",board->gameMode);
	if(board->gameMode==2){
		fprintf(file,"\t<difficulty>%d</difficulty>\n",board->diffLevel);
		fprintf(file,"\t<user_color>%d</user_color>\n",board->userCol);
	}
	fputs("\t<board>\n",file);
	for(int i=0;i<ROW;i++){
		fprintf(file,"\t\t<row_%d>",8-i);
		for (int j=0;j<COL;j++){
			fprintf(file,"%c",board->boardArr[i][j]);
		}
		fprintf(file,"</row_%d>\n",8-i);
	}
	fputs("\t</board>\n",file);
	fputs("</game>",file);
	fclose(file);
}





void exUndo(boardGame* board,bool printActivate){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	int index = board->history->actualSize-1;
	char objDest = (char)board->history->elements[index];
	int posDest = board->history->elements[index-1];
	char objSource = (char)board->history->elements[index-2];
	int posSource = board->history->elements[index-3];
	board->boardArr[NumToRow(posDest)][NumToCol(posDest)] = objDest;
	board->boardArr[NumToRow(posSource)][NumToCol(posSource)] = objSource;
	if(printActivate){
		char po = (char) (NumToCol(posSource)+'A');
		char de = (char) (NumToCol(posDest)+'A');
		if(board->curPlayer==0){
			if(printActivate) printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",
			BLACK,8-NumToRow(posSource),po,8-NumToRow(posDest),de);
		}
		else if(board->curPlayer==1){
			if(printActivate)printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",
			WHITE,8-NumToRow(posSource),po,8-NumToRow(posDest),de);
		}
	}
	return;
}


void undo(boardGame* board, bool printActivate, bool playerChangeAcivate){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	if (playerChangeAcivate)changePlayer(board);
	exUndo(board,printActivate);
	for(int i=0;i<4;i++){
		spArrayListRemoveLast(board->history);
	}
	return;
}

void moveMessage(boardGame* board){
	assert(board!=NULL);
	if(board->gameMode==2){
		if(board->curPlayer==0) printf("%s player - enter your move:\n",BLACK);
		else if(board->curPlayer==1) printf("%s player - enter your move:\n",WHITE);
	}
	else if(board->gameMode==1){
		if(board->curPlayer==board->userCol){
			printf("%s player - enter your move:\n",WHITE);
		}
		else return;
	}
}

void printCheckMessage(int player){
	if(player==1) printf("Check: %s King is threatened!\n",WHITE);
	else if(player==0) printf("Check: %s King is threatened!\n",BLACK);
}

bool isCheckMate(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	bool valid = false;
	if(board->curPlayer==0){
		for(int i=0; i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(isBlackPlayer(board->boardArr[i][j])){
					valid = isThereOptionMove(board,i,j);
					if(valid) return false;
				}
			}
		}
	}
	else if(board->curPlayer==1){
		for(int i=0; i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(isWhitePlayer(board->boardArr[i][j])){
					valid = isThereOptionMove(board,i,j);
					if(valid) return false;
				}
			}
		}
	}
	return true;
}

bool isThereOptionMove(boardGame* board,int row,int col){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	boardGame* copy = copyBoard(board);
	assert(copy!=NULL);
	assert(copy->boardArr!=NULL);
	assert(copy->history!=NULL);
	assert(copy->history->elements!=NULL);
	bool valid = false;
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			valid = moveObj(copy,RowColToNum(row,col),RowColToNum(i,j),false);
			if(valid){
				destroyBoard(copy);
				return true;
			}				// no need to undo/destroy cause if !valid - no move was done
		}
	}
	destroyBoard(copy);
	return false;
}


void terminateGame(boardGame* board, bool mate, bool tie){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	if(mate){
		if(board->curPlayer==0){
			printf("Checkmate! %s player wins the game\n",WHITE);
		}
		else if(board->curPlayer==1){
			printf("Checkmate! %s player wins the game\n",BLACK);
		}
		destroyBoard(board);
		exit(0);
	}
	else if (tie){
		if(board->gameMode==2)printf("The game is tied\n");
		else if(board->gameMode==1) printg("The game ends in a tie\n");
		destroyBoard(board);
		exit(0);
	}
}

bool isWhitePlayer(char c){
	if (c=='n' || c=='b' || c=='m' || c=='r' || c=='k' || c=='q') return true;
	return false;
}

bool isBlackPlayer(char c){
	if (c=='N' || c=='B' || c=='M' || c=='R' || c=='K' || c=='Q') return true;
	return false;
}


void getMovesFunc(boardGame* board,int position){
	//printf("getmovesFunc was acted\n");
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	int row = NumToRow(position);
	int col = NumToCol(position);
	if (position>63 || position<0 ){
		printf("Invalid position on the board\n");}
	//printf("current player is %d, the row is %d, the col is: %d\n",board->curPlayer,row,col);
	if(board->gameMode==2 || (board->gameMode==1 && board->diffLevel>=3)){
		printf("illegal move\n");
		return;
	}
	if (board->curPlayer==0 &&
			(isWhitePlayer(board->boardArr[row][col])|| board->boardArr[row][col]==UNDERSCORE))
		printf("The specified position does not contain %s player piece\n",BLACK);
	else if (board->curPlayer==1 &&
			(isBlackPlayer(board->boardArr[row][col])|| board->boardArr[row][col]==UNDERSCORE))
			printf("The specified position does not contain %s player piece\n",WHITE);
	else{
		bool valid,valid1 = false;
		int rowDest, colDest, dest =0;
		boardGame* copy = copyBoard(board);
		assert(copy!=NULL); assert(copy->boardArr!=NULL);
		assert(copy->history!=NULL); assert(copy->history->elements!=NULL);
		for(int i=7; i>=0;i--){
			rowDest = i;
			for (int j=0;j<COL;j++){
				colDest = j;
				if (rowDest==row && colDest==col) continue;
				dest = RowColToNum(rowDest,colDest);
				if((board->curPlayer==0 && isWhitePlayer(board->boardArr[rowDest][colDest]))
					||(board->curPlayer==1 && isBlackPlayer(board->boardArr[rowDest][colDest])))
					valid1 = true;		// need to be checked before the move action
				valid = moveObj(copy,position,dest, false);
				if(!valid){
					valid1 = false;
					continue;
				}
				else if (valid){				//if valid move == true
					getMovesPrintFunc(copy, valid1,rowDest, colDest, dest);
					undo(copy,false,true);		//if we are here, move was done
					}
				valid1 = false;
			}
		}
		destroyBoard(copy);
		}
	return;
	}

void getMovesPrintFunc(boardGame* copy, bool valid1, int rowDest, int colDest, int dest){
	assert(copy!=NULL);
	assert(copy->boardArr!=NULL);
	assert(copy->history!=NULL);
	assert(copy->history->elements!=NULL);
	bool valid2 = false;
	for(int k=0;k<ROW;k++){
		for(int l=0;l<COL;l++){
			valid2 = moveObj(copy,RowColToNum(k,l),dest, false);
			if(valid2==true && valid1==true){
				printf("<%d,%c>*^\n",8-rowDest,(char)(colDest+'a'));
				undo(copy,false,true);
				return;
			}
			else if (valid2==true && valid1==false){
				printf("<%d,%c>*\n",8-rowDest,(char)(colDest+'a'));
				undo(copy,false,true);
				return;
			}
		}
	}
	if (valid1==true)printf("<%d,%c>^\n",8-rowDest,(char)(colDest+'a'));
	else printf("<%d,%c>\n",8-rowDest,(char)(colDest+'a'));

}


bool isWinner(boardGame* board){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	bool isKingSafe = isMyKingSafe(board);
	bool checkMate = isCheckMate(board);
	if(isKingSafe==false && checkMate==true) return true;
	return false;
}


void moveAIobj(boardGame* board){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	int moveArr[2] = AlphaBetaMove(board);
	bool valid = moveObj(board,moveArr[0],moveArr[1],false);
	if(valid){
		computerMoveMessage(board,moveArr[0],moveArr[1]);
		if(!isMyKingSafe(board)){		//checking if the opponent king's is threatened
			//printf("there is a risk on the king");
			if(isCheckMate(board)){
				free(moveArr);
				terminateGame(board,true, false);
			}
			printCheckMessage(board->curPlayer);
			//printf("we got yill here");
		}
		else if (isCheckMate(board)){
			free(moveArr);
			terminateGame(board,false, true);
		}
	}
	free(moveArr);
}


void computerMoveMessage(boardGame* board, int position, int destination){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	int posRow = NumToRow(position); int posCol = NumToCol(position);
	int destRow = NumToRow(destination); int destCol = NumToCol(destination);
	printf("Computer: move ");
	if(board->boardArr[destRow][destCol]==BlackPawn) printf("pawn");
	else if(board->boardArr[destRow][destCol]==BlackBishop) printf("bishop");
	else if(board->boardArr[destRow][destCol]==BlackKnight) printf("knight");
	else if(board->boardArr[destRow][destCol]==BlackRook) printf("rook");
	else if(board->boardArr[destRow][destCol]==BlackQueen) printf("queen]");
	else if(board->boardArr[destRow][destCol]==BlackKing) printf("king");
	printf(" at <%d,%c> to <%d,%c>\n",8-posRow,(char)(posCol+'A'),8-destRow, (char)(destCol+'A'));


}
