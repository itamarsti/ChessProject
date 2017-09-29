/*
 * boardFuncs.c
 *
 *  Created on: 11 баев„ 2017
 *      Author: Itamar
 */

/**
 * boardFuncs summary:
 *
 * This parts includes all the functions which relevant to the GameBoard Structure,
 * settings commands, and board operational commands (such as quit).
 *
 *
 *
 * createBoard		   		- creating the gameBoard structure.
 * initBoard          		- initialing the gameBoard.
 * printBoard				- prints the gameBoard.
 * destroyBoard				- destroying the gameBoard Structure.
 * setDifficult				- setting the difficulty
 * setColor					- changing the user Color
 * boardPrintSet			- prints the current Settings as demand
 * setNumPlayers			- settings the number of players (1 or 2)
 * copyBoard				- copying the gameBoard Structure
 * setDefault				- defaulting the gameBoard settings
 * invalidSettingPrint		- prints message of invalid inputs
 * loadFile					- loading a XML File to to the gameBoard struct
 * quit						- doing Exit
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "settingParser.h"
#include "SPArrayList.h"
#include "boardFuncs.h"

#define HISTORY 24


/**
 *
 *
 * Creating the gameBoard Structure.
 * @return
 * Pointer to the BoardGame Structure.b
 *
 */


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


/**
 *
 *
 * Initialing the game board with specific objects (presented by chars) and initialing the settings to default
 * by demand.
 * @param board - the Board Game Data structure.
 * @param initSettings - true for default settings, false for doing nothing.
 * @return
 * void
 *
 */


void initBoard(boardGame* board, bool initSettings){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	for(int k=0;k<ROW;k++){
		for(int l=0;l<COL;l++){
			board->boardArr[k][l]=UNDERSCORE;
		}
	}
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
	if(initSettings){
		board->gameMode = 1;			//1- 1 player; 2- 2 players
		board->diffLevel = 2;			//difficult level
		board->userCol = 1;				//1 - white; 0 - black;
					//1 = white player, 0 = black player
	}
	board->curPlayer = 1;
	int j = board->history->actualSize-1;
	for(int i=j;i>=0;i--){
		spArrayListRemoveLast(board->history);
	}
}


/**
 *
 *
 * Printing the game Board as demand.
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */


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
		printf("  -----------------\n");
		printf("   ");
		printf("A B C D E F G H\n");
	}
	else return;
}

/**
 *
 *
 * Destroying the gameBoard and free the relevant memory that was allocated.
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */

void destroyBoard(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	spArrayListDestroy(board->history);
	free(board);
}

/**
 *
 *
 * Setting the difficulty level in the gameBoard data structure.
 *
 * @param board - the Board Game Data structure.
 * @param num - the difficulty level (int).
 * @return
 * void
 * notice!! the difficulty level is integer between 1-5.
 *
 */


void setDifficult(boardGame* board, int num){
	assert(board!=NULL);
	board->diffLevel = num;
}

/**
 *
 *
 * Setting the User Color in the gameBoard data structure.
 *
 * @param board - the Board Game Data structure.
 * @param num - the user color, 0 for white, 1 for black (int).
 * @return
 * void
 *
 */

void setColor(boardGame* board, int num){
	assert(board!=NULL);
	board->userCol = num;
}

/**
 *
 *
 * Setting the player's number in the gameBoard data structure.
 *
 * @param board - the Board Game Data structure.
 * @param num - 1 for 1-player, 2 for 2-players.
 * @return
 * void
 *
 *
 */

void setNumPlayers(boardGame* board, int num){
	assert(board!=NULL);
	board->gameMode = num;
	if(num==1) printf("Game mode is set to %d player\n",board->gameMode);
	else if(num==2) printf("Game mode is set to %d players\n",board->gameMode);
	if(num==1){
		board->diffLevel=2;
		board->userCol=1;
		board->curPlayer=1;
	}
}

/**
 *
 *
 * Printing the gameBoard Settings as demand.
 *
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */

void boardPrintSet(boardGame*board){
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	printf("SETTINGS:\n");
	if(board->gameMode==2){
		printf("GAME_MODE: %d\n",board->gameMode);
		return;}
	else{
		printf("GAME_MODE: %d\n",board->gameMode);
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


/**
 *
 *
 * Copying the gameBoard data structure to a new allocated memory, different from the original.
 *
 * @param board - the Board Game Data structure.
 * @return
 * boardGame Data Structure pointer of the copied gameBoard.
 *
 */


boardGame* copyBoard(boardGame*board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	boardGame* copy = (boardGame*)createBoard();
	assert(copy!=NULL);
	assert(copy->boardArr!=NULL);
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			copy->boardArr[i][j]=board->boardArr[i][j];
		}
	}
	spArrayListDestroy(copy->history);
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


/**
 *
 *
 * Setting the boardGame settings to Default (1-player mode, easy difficulty, white UserColor)
 *
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */


void setDefault(boardGame* board){
	assert(board!=NULL);
	board->gameMode = 1;			//1- 1 player; 2- 2 players
	board->diffLevel = 2;			//difficult level
	board->userCol = 1;				//1 - white; 0 - black;
	board->curPlayer = 1;
	//printf("setting to default was completed\n");
}
/**
 *
 *
 * Printing Invalid Setting Commands of different states.
 *
 * @param cmd - Invalid settingCommand message
 * @return
 * void
 *
 */


void invalidSettingPrint(SETTING_COMMAND cmd){
	if (cmd==INVALID_DIFFICULT)printf ("Wrong difficulty level. The value should be between 1 to 5\n");
	else if (cmd==INVALID_GAME_MODE) printf("Wrong game mode\n");
	else if (cmd==INVALID_FILE) printf("Error: File doesn't exist or cannot be opened\n");
}

/**
 *
 *
 * Loading file from legal path to the gameBoard
 *
 * @param board - the Board Game Data structure.
 * @param cmd - Settings data structure which contains the path destinetion to load from
 * @return
 * void
 *
 */


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
	if(board->gameMode==1){
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


/**
 *
 *
 * Quits from the program by destroying the gameBoard (free the memory) and prints "exit message".
 *
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */

void quit(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	destroyBoard(board);
	printf("Exiting...\n");
	exit(0);
}
