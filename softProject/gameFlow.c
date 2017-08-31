/*
 * gameFlow.c
 *
 *  Created on: 26 ����� 2017
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
#include "settingParser.h"




bool cmdToActGame(boardGame* board, GameCommand* cmd){
	assert(board!=NULL);
	assert(cmd!=NULL);
	bool validMove = false;
	if (cmd->cmd==MOVE) validMove = moveObj(board,cmd);
	else if(cmd->cmd==UNDO){
		undo(board);
		undo(board);
	}
	else if(cmd->cmd==SAVE) saveFile(board,cmd->path);
	return validMove;
}



bool mainGameFlow(boardGame* board){
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	char* input;
	GameCommand* cmd;
	bool loopBreaker = false;
	moveMessage( board);
	while(!loopBreaker){
		input = gameAcceptor();
		assert(input!=NULL);
		cmd = gameParser(input);
		assert(cmd!=NULL);
		if(cmd->validArg){
			if(cmd->cmd==RESET || cmd->cmd==QUIT2){
				free(input);
				if(cmd->cmd==QUIT2){
					destroyGameStruct(cmd);
					quit(board);
				}
				else{							//in case of RESET
					destroyGameStruct(cmd);
					reset(board);
					return true;
				}

			}
			loopBreaker = cmdToActGame(board,cmd);		//dont forget game_moves
		}
		else if (!cmd->validArg){
				if(cmd->cmd==INVALID_SAVE) printf("File cannot be created or modified\n");
				else if (cmd->cmd==INVALID_LINE2) printf("Illegal Command\n");
			}
			continue;
		}
	free(input);
	destroyGameStruct(cmd);
	return false;
}



