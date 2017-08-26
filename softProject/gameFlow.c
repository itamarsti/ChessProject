/*
 * gameFlow.c
 *
 *  Created on: 26 баев„ 2017
 *      Author: Itamar
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "gameCommands.h"
#include "gameParser.h"
#include "moveOps.h"
#include "boardFuncs.h"


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
		return ;
		}
		else if(cmd->cmd==UNDO) undo(board);
		else if (cmd->cmd==MOVE) moveObj(board,cmd);
	}
	free(input);
	destroyGameStruct(cmd);
	return false;

}

bool cmdToActGame(boardGame* board, GameCommand* cmd){
	assert(board!=NULL);
	assert(cmd!=NULL);
	if(cmd->cmd==UNDO) undo(board);
	else if (cmd->cmd==MOVE) moveObj(board,cmd);
	else if(cmd->cmd==SAVE) saveFile(board,cmd);


}



