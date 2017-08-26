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



void saveFile(boardGame* board, GameCommand* cmd){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(cmd!=NULL); assert(cmd->path!=NULL);
	char* path = cmd->path;
	FILE* file = (FILE*) fopen(path,"w");
	assert(file!=NULL);
	fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",file);
	fputs("<game>\n",file);
	fprintf(file,"\t<current_turn>%d</current_turn>\n",board->curPlayer);
	fprintf(file,"\t<game_mode>%d</game_mode>\n",board->gameMode);
	if(board->gameMode==1){
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
