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

void undo(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	if(board->gameMode==2){
		printf("Undo command not available in 2 players mode\n");
		return;
	}
}
