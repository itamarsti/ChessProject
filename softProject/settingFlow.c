/*
 * settingFlow.c
 *
 *  Created on: 24 баев„ 2017
 *      Author: Itamar
 */

#include "boardFuncs.h"
#include "settingParser.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool cmdToActSetting(boardGame* board, ChessCommand* command){
	assert(board!=NULL);
	assert(command!=NULL);
	if(command->cmd==START) return true;
	else if(command->cmd==DIFFICULTY_1) setDifficult(board, 1);
	else if (command->cmd==DIFFICULTY_2) setDifficult(board, 2);
	else if (command->cmd==DIFFICULTY_3) setDifficult(board, 3);
	else if (command->cmd==DIFFICULTY_4) setDifficult(board, 4);
	//else if (command->cmd==DIFFICULTY_5) setDifficult(board, 5);
	else if (command->cmd==USER_COL_0) setColor(board,0);
	else if (command->cmd==USER_COL_1) setColor(board, 1);
	else if (command->cmd==GAME_MODE_1) setNumPlayers(board, 1);
	else if (command->cmd==GAME_MODE_2) setNumPlayers(board, 2);
	else if (command->cmd==DEFAULT) setDefault(board);
	else if	(command->cmd==PRINT_SETTINGS)boardPrintSet(board);
	else if (command->cmd ==LOAD_FILE)loadFile(board,command);
	//printf("in settingFlow load serction\n");
	return false;
	}



void mainSettingFlow(boardGame* board){
	assert(board!=NULL);
	//assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements);
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	bool startBool = false;
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	while(!startBool){
		//printf("in the loop of settings flow\n");
		char* string = (char*) settingAcceptor();
		assert(string!=NULL);
		//printf("befor settingcmd\n");
		ChessCommand* cmd = (ChessCommand*) settingParser(string,board->gameMode);
		//printf("after cmdsettings");
		assert(cmd!=NULL);
		if(cmd->validArg==false){
			if ((cmd->cmd==INVALID_DIFFICULT)|| (cmd->cmd==INVALID_GAME_MODE)
					|| (cmd->cmd==INVALID_FILE)){
				invalidSettingPrint(cmd->cmd);
				destroySettingStruct(cmd);
				free(string);
			}
			else if(cmd->cmd==INVALID_LINE1){			//what to do in that case???
				printf("ERROR: Invalid Command\n");
				destroySettingStruct(cmd);
				free(string);
				continue;
			}
		}
		else if (cmd->validArg==true){
			if(cmd->cmd==QUIT1){
				free(string);
				destroySettingStruct(cmd);
				quit(board);
			}
			else if (cmd->cmd==DIFFICULTY_5){
				printf("Expert level not supported, please choose a value between 1 to 4:\n");
				destroySettingStruct(cmd);
				continue;
			}
			//printf("cefore startBool\n");
			startBool=cmdToActSetting(board, cmd);
			//printf("after startbool\n");
		}
		//printf("before free\n");
		free(string);
		//printf("before destroy\n");
		destroySettingStruct(cmd);
		//printf("after destroy");
	}
	return;
}

