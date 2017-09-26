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
#include "boardFuncs.h"
#include "settingParser.h"
#include "gameFlow.h"




bool cmdToActGame(boardGame* board, GameCommand* cmd, char* input){
	assert(board!=NULL);
	assert(cmd!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	bool validMove, isMate, isTie= false;
	if (cmd->cmd==MOVE){
		validMove = moveObj(board,cmd->position,cmd->destination, true);
		if(validMove){
			//printf("checking the opponent state checkmate/tie\n");
			if(!isMyKingSafe(board)){		//checking if the opponent king's is threatened
				//printf("there is a risk on the king");
				if((isMate = isCheckMate(board))==true){
					//printf("the is checkMate");
					free(input);
					destroyGameStruct(cmd);
					terminateGame(board,true, false);
				}
				printCheckMessage(board->curPlayer);
				//printf("we got yill here");
			}
			else if ((isTie = isCheckMate(board))==true){
				free(input);
				destroyGameStruct(cmd);
				terminateGame(board,false, true);
			}
		}
	}
	else if(cmd->cmd==UNDO){
		if(board->gameMode==2){
			printf("Undo command not available in 2 players mode\n");
			return false;
		}
		if(spArrayListIsEmpty(board->history)){
			printf("Empty history, move cannot be undone\n");
			return false;
		}
		undo(board,true,true);
		undo(board,true,true);
		return true;
	}
	else if(cmd->cmd==SAVE) saveFile(board,cmd->path);
	else if(cmd->cmd==GET_MOVES) getMovesFunc(board,cmd->position);
	return validMove;
}



bool mainGameFlow(boardGame* board){
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	if(board==NULL){
		printf("board is NULL");
		exit(0);
	}
	//assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	bool loopBreaker = false;
	while(!loopBreaker){
		moveMessage(board);
		char* input = (char*) gameAcceptor();
		assert(input!=NULL);
		GameCommand* cmd = (GameCommand*) gameParser(input);
		assert(cmd!=NULL);
		printf("we have nice gameParser struct\n");
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
			loopBreaker = cmdToActGame(board,cmd, input);
		}
		else if (!cmd->validArg){
				if(cmd->cmd==INVALID_SAVE) printf("File cannot be created or modified\n");
				else if(cmd->cmd==INVALID_POSITION) printf("Invalid position on the board\n");
				else if (cmd->cmd==INVALID_LINE2) printf("ERROR: Illegal Command\n");
		}
		free(input);
		destroyGameStruct(cmd);
		continue;
	}
	return false;
}



