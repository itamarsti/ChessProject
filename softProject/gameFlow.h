/*
 * gameFlow.h
 *
 *  Created on: 26 баев„ 2017
 *      Author: Itamar
 */

#ifndef GAMEFLOW_H_
#define GAMEFLOW_H_

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




bool cmdToActGame(boardGame* board, GameCommand* cmd, char* input);
bool mainGameFlow(boardGame* board);

#endif /* GAMEFLOW_H_ */
