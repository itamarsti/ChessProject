/*
 * gameCommands.h
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */

#ifndef GAMECOMMANDS_H_
#define GAMECOMMANDS_H_

#include <stdbool.h>

typedef enum {
	MOVE,
	GET_MOVES,
	SAVE,
	UNDO,
	RESET,
	QUIT,
	INVALID_LINE
} GAME_COMMAND;


#endif /* GAMECOMMANDS_H_ */
