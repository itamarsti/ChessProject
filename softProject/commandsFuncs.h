/*
 * commandsFuncs.h
 *
 *  Created on: 11 баев„ 2017
 *      Author: Itamar
 */

#ifndef COMMANDSFUNCS_H_
#define COMMANDSFUNCS_H_

#include <stdbool.h>
typedef enum {
	START,
	GAME_MODE_1,
	GAME_MODE_2,
	DIFFICULTY_1,
	DIFFICULTY_2,
	DIFFICULTY_3,
	DIFFICULTY_4,
	DIFFICULTY_5,
	USER_COL_0,
	USER_COL_1,
	LOAD_FILE,
	DEFAULT,
	PRINT_SETTINGS,
	QUIT1,
	INVALID_LINE1
} SETTING_COMMAND;

typedef struct t_command {
	SETTING_COMMAND cmd;
	bool validArg; //is set to true if the line contains a valid argument
} ChessCommand;


char* commandsAcc();

ChessCommand commandParser(const char* str);

#endif /* COMMANDSFUNCS_H_ */
