/*
 * settingFlow.c
 *
 *  Created on: 24 баев„ 2017
 *      Author: Itamar
 */

#include "boardFuncs.h"
#include "settingParser.h"
#include "gameCommands.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gameParser.h"
#include "settingParser.h"

bool cmdToAct(boardGame* board, ChessCommand* command){
	assert(board!=NULL);
	assert(command!=NULL);
	if(command->cmd==START) return true;
	else if(command->cmd==DIFFICULTY_1) setDifficult(board, 1);
	else if (command->cmd==DIFFICULTY_2) setDifficult(board, 2);
	else if (command->cmd==DIFFICULTY_3) setDifficult(board, 3);
	else if (command->cmd==DIFFICULTY_4) setDifficult(board, 4);
	else if (command->cmd==DIFFICULTY_5) setDifficult(board, 5);
	else if (command->cmd==USER_COL_0) setColor(board,0);
	else if (command->cmd==USER_COL_1) setColor(board, 1);
	else if (command->cmd==GAME_MODE_1) setNumPlayers(board, 1);
	else if (command->cmd==GAME_MODE_2) setNumPlayers(board, 2);
	else if (command->cmd==DEFAULT) setDefault(board);
	else if	((command->cmd==QUIT1) || (command->cmd==INVALID_FILE)||(command->cmd==INVALID_LINE1)
			|| (command->cmd==INVALID_DIFFICULT)||(command->cmd==INVALID_GAME_MODE))
			return false;
	else if	(command->cmd==PRINT_SETTINGS)boardPrintSet(board);
	else if (command->cmd ==LOAD_FILE) return false; 	//handling that case
	return false;
	}



void mainSettingFlow(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements);
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	bool startBool = false;
	char* string;
	ChessCommand* cmd;
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	while(!startBool){
		string = settingAcceptor();
		assert(string!=NULL);
		cmd = settingParser(string,board->gameMode);
		assert(cmd!=NULL);
		if(cmd->validArg==false){
			if ((cmd->cmd==INVALID_DIFFICULT)|| (cmd->cmd==INVALID_GAME_MODE)){
				invalidSettingPrint(cmd->cmd);}
			else if(cmd->cmd==INVALID_LINE1){			//what to do in that case???
				printf("Illegal Command\n");
				continue;

			}
		}
		else if (cmd->validArg==true){
			startBool=cmdToAct(board, cmd);
			if(!startBool){
				if(cmd->cmd==QUIT1){
					free(string);
					destroySettingStruct(cmd);
					quit(board);
				}
			}
		}
		free(string);
		free(cmd);
	}
	return;
}

