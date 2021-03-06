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
#include "boardFuncs.h"
#include "settingParser.h"
#include "gameFlow.h"


/**
 * gameFlow summary:
 *
 * The Handling part of the game section.
 * Containing functions which their purpose is to translate commands inputs
 * to a game Action relative to the Game Board.
 *
 *
 * cmdToActGame		   	- Activating the relevant function based on the game command type.
 * mainGameFlow          - The main loop of the game section and responsible for
 * 							  the game flow (from gameCommand - to a Game action).
 *
 *
 */



/**
 *
 *
 * Managing some gameBoard command to actions based on the relevant commands.
 * The commands are move, quit, reset, undo, get_moves and save.
 * @param board - the Board Game Data structure.
 * @param cmd - the Game command Data structure.
 * @param input - the user's input.
 * @return
 * True - if valid action has happened that will cause a progress in the game (undo and move);
 * False - if the command will not cause a progress (such as save, get moves or illegal move).
 *notice!! also includes the checking if there was a check/checkmate/tie at the end of every turn.
 *
 */


bool cmdToActGame(boardGame* board, GameCommand* cmd, char* input){
	assert(board!=NULL); assert(cmd!=NULL);	assert(board->history!=NULL);	assert(board->history->elements!=NULL);
	bool validMove=false; bool isMate = false; bool isTie= false;
	if (cmd->cmd==MOVE){
		validMove = moveObj(board,cmd->position,cmd->destination, true);
		if(validMove){
			if(!isMyKingSafe(board)){		//checking if the opponent king's is threatened
				if((isMate = isCheckMate(board))==true){
					free(input);
					destroyGameStruct(cmd);
					terminateGame(board,true, false);
				}
				printCheckMessage(board->curPlayer,board->userCol, board->gameMode);
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
		if(spArrayListIsEmpty(board->history) || board->history->actualSize==4){
			printf("Empty history, move cannot be undone\n");
			return false;
		}
		undo(board,true,true);
		undo(board,true,true);
		printBoard(board);
		return true;
	}
	else if(cmd->cmd==SAVE) saveFile(board,cmd->path);
	else if(cmd->cmd==GET_MOVES) getMovesFunc(board,cmd->position);
	return validMove;
}


/**
 *
 *
 * Managing every turn actions based on the relevant commands.
 * The function responsible the activate the request for the user's input,
 * setting it in the CommandGame data structure and handling the command with external function.
 * @param board - the Board Game Data structure.
 * @return
 * True - if reset action was requested.
 * False - for every other action (besides quit which will cause to terminating the game).
 *
 */
bool mainGameFlow(boardGame* board){
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	if(board==NULL){
		printf("ERROR: board is NULL");
		exit(0);
	}
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	bool loopBreaker = false;
	while(!loopBreaker){
		moveMessage(board);
		char* input = (char*) gameAcceptor();
		assert(input!=NULL);
		GameCommand* cmd = (GameCommand*) gameParser(input);
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



