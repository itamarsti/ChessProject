/*
 * boardFuncs.c
 *
 *  Created on: 11 ·‡Â‚◊ 2017
 *      Author: Itamar
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "settingParser.h"
#include "SPArrayList.h"
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
#define HISTORY 24

boardGame* createBoard(){
	boardGame* board = (boardGame*)malloc(sizeof(boardGame));
	assert(board!=NULL);
	for (int i=0;i<ROW;i++){
		for (int j=0;j<COL;j++){
			board->boardArr[i][j]=UNDERSCORE;
		}
	}
	board->history = (SPArrayList*)spArrayListCreate(HISTORY);
	assert(board->history!=NULL);
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
	board->gameMode = 1;			//1- 1 player; 2- 2 players
	board->diffLevel = 2;			//difficult level
	board->userCol = 1;				//1 - white; 0 - black;
	board->curPlayer = 1;			//1 = white player, 0 = black player
}

void printBoard(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	if(board->gameMode==2 || (board->gameMode==1 )){
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
	else return;
}

void destroyBoard(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	spArrayListDestroy(board->history);
	free(board->boardArr);
	free(board);
}


void setDifficult(boardGame* board, int num){
	assert(board!=NULL);
	board->diffLevel = num;
}

void setColor(boardGame* board, int num){
	assert(board!=NULL);
	board->userCol = num;
}

void setNumPlayers(boardGame* board, int num){
	assert(board!=NULL);
	board->gameMode = num;
	printf("Game mode is set to %d players\n",board->gameMode);
}

void boardPrintSet(boardGame*board){
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	printf("SETTINGS:\n");
	if(board->gameMode==2){
		printf("GAME MODE: %d\n",board->gameMode);
		return;}
	else{
		printf("GAME MODE: %d\n",board->gameMode);
		printf("DIFFICULTY_LVL: %d\n",board->diffLevel);
		if(board->userCol==0){
			printf("USER_CLR: BLACK\n");
		}
		else if (board->userCol==1){
			printf("USER_CLR: WHITE\n");
		}
		return;
	}
}

boardGame* copyBoard(boardGame*board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	boardGame* copy = createBoard();
	assert(copy!=NULL);
	assert(copy->boardArr!=NULL);
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			copy->boardArr[i][j]=board->boardArr[i][j];
		}
	}
	SPArrayList* histCopy = spArrayListCreate(HISTORY);
	histCopy->actualSize = board->history->actualSize;
	histCopy->maxSize = board->history->maxSize;
	for(int i=0;i<board->history->actualSize;i++){
		histCopy->elements[i] = board->history->elements[i];
	}
	copy->curPlayer=board->curPlayer;
	copy->diffLevel=board->diffLevel;
	copy->gameMode=board->gameMode;
	copy->userCol = board->userCol;
	copy->history = histCopy;
	return copy;
}

void setDefault(boardGame* board){
	assert(board!=NULL);
	board->gameMode = 1;			//1- 1 player; 2- 2 players
	board->diffLevel = 2;			//difficult level
	board->userCol = 1;				//1 - white; 0 - black;
	board->curPlayer = 1;
	printf("setting to default was completed\n");
}

void invalidSettingPrint(SETTING_COMMAND cmd){
	if (cmd==INVALID_DIFFICULT)printf ("Wrong difficulty level. The value should be between 1 to 5\n");
	else if (cmd==INVALID_GAME_MODE) printf("Wrong game mode\n");
	else if (cmd==INVALID_FILE) printf("Eror: File doesnít exist or cannot be opened\n");
}

void loadFile(boardGame*board, ChessCommand* cmd){
	assert(board!=NULL); assert(board->boardArr!=NULL);assert(cmd!=NULL); assert(cmd->path!=NULL);
	char* path = (char*)cmd->path;
	assert(path!=NULL);
	FILE* file = (FILE*) fopen(path,"r");
	assert(file!=NULL);
	char buffer[1024];
	char* token;
	fscanf(file, "%[^\n]\n", buffer);	//xml version & encoding
	fscanf(file, "%[^\n]\n", buffer); 	//	game
	fscanf(file, "%[^\n]\n", buffer);	//current turn
	board->curPlayer = (int) buffer[14]-'0';
	fscanf(file, "%[^\n]\n", buffer);	//game mode
	board->gameMode = (int) buffer[11]-'0';
	if(board->gameMode==2){
		fscanf(file, "%[^\n]\n", buffer);	//difficulty turn
		token = strtok(buffer," <>");
		if(strcmp(token,"difficulty ")){
			int difficulty = (int)buffer[12]-'0';
			board->diffLevel = difficulty;
		}
		fscanf(file, "%[^\n]\n", buffer);	//game_color turn
		token = strtok(buffer," <>");
		if(strcmp(token,"game_color ")){
			int gameCol = (int)buffer[12]-'0';
			board->userCol = gameCol;
		}
	}
	fscanf(file, "%[^\n]\n", buffer);	//board
	for(int i=0;i<ROW;i++){
		fscanf(file, "%[^\n]\n", buffer); //row
		for(int j=7;j<7+COL;j++){
			board->boardArr[i][j-7] = (char)buffer[j];
		}
	}
	fclose(file);




}
