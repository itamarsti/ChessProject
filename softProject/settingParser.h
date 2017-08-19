/*
 * settingParser.h
 *
 *  Created on: 19 баев„ 2017
 *      Author: Itamar
 */

#ifndef SETTINGPARSER_H_
#define SETTINGPARSER_H_


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
	INVALID_DIFFICULT,
	USER_COL_0,
	USER_COL_1,
	LOAD_FILE,
	INVALID_FILE,
	DEFAULT,
	PRINT_SETTINGS,
	QUIT1,
	INVALID_LINE1
} SETTING_COMMAND;

typedef struct t_command {
	SETTING_COMMAND cmd;
	bool validArg; //is set to true if the line contains a valid argument
	char* path;
} ChessCommand;


char* commandsAcc();
ChessCommand commandParser(const char* str);
bool spParserIsInt(const char* str);
SETTING_COMMAND diffiDecider(char* str);
SETTING_COMMAND gameModeDecider(char* str);
SETTING_COMMAND gameColorDecider(char* str);
bool isFileExist(const char*path);

#endif /* SETTINGPARSER_H_ */
