/*
 * gameFlow.c
 *
 *  Created on: 26 баев„ 2017
 *      Author: Itamar
 */


#include "boardFuncs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "gameCommands.h"
#include "gameParser.h"
#include "moveOps.h"


bool mainGameFlow(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements);
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	char* input;
	GameCommand* cmd;
	bool loopBreaker = false;
	if(board->curPlayer==0) printf("%s player - enter your move:\n",BLACK);
	else if(board->curPlayer==0) printf("%s player - enter your move:\n",WHITE);
	input = gameAcceptor();
	assert(input!=NULL);
	cmd = gameParser(input);
	assert(cmd!=NULL);
	if(cmd->validArg){
		if(cmd->cmd==RESET||(cmd->cmd==QUIT2)){
			free(input);
			destroyGameStruct(cmd);
			if(cmd->cmd==RESET){
				reset(board);
				return true;
			}
			else quit(board);
		}
		else if(cmd->cmd==UNDO) undo(board);
		else if (cmd->cmd==MOVE) moveObj(board,cmd);
	}
	free(input);
	destroyGameStruct(cmd);
	return false;


		GET_MOVES,
		SAVE,
		INVALID_SAVE,
		INVALID_LINE2
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


