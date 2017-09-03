/*
 * gameCommands.c
 *
 *  Created on: 17 ����� 2017
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
	int posDSource = board->history->elements[index-3];
	board->boardArr[NumToRow(posDest)][NumToCol(posDest)] = objDest;
	board->boardArr[NumToRow(posDSource)][NumToCol(posDSource)] = objSource;
	if(printActivate){
		if(board->curPlayer==0){
			printf("Undo move for player %s : <%d,%d> -> <%d,%d>\n",
			BLACK,NumToRow(posDSource)+1,NumToCol(posDSource)+1,NumToRow(posDest)+1,NumToCol(posDest)+1);
		}
		else if(board->curPlayer==1){
			printf("Undo move for player %s : <%d,%d> -> <%d,%d>\n",
			WHITE,NumToRow(posDSource)+1,NumToCol(posDSource)+1,NumToRow(posDest)+1,NumToCol(posDest)+1);
		}
	}
	return;
}


void undo(boardGame* board,bool printActivate, bool playerChangeAcivate){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	exUndo(board,printActivate);
	for(int i=board->history->actualSize-1; i>board->history->actualSize-5;i--){
		spArrayListRemoveAt(board->history,i);
	}
	board->history->actualSize-=4;
	if (playerChangeAcivate)changePlayer(board);
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
	else if(player==1) printf("Check: %s King is threatened!\n",BLACK);
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
			valid = moveObj(copy,RowColToNum(row,col),RowColToNum(i,j));
			if(valid){
				destroyBoard(copy);
				return true;
			}
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
		printf("The game is tied\n");
		destroyBoard(board);
		exit(0);
	}
}

bool isWhitePlayer(char c){
	if (c=='n' || c=='b' || c=='p' || c=='r' || c=='k' || c=='q') return true;
	return false;
}

bool isBlackPlayer(char c){
	if (c=='N' || c=='N' || c=='N' || c=='N' || c=='N' || c=='N') return true;
	return false;
}
