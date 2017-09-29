/*
 * settingParser.c
 *
 *  Created on: 19 баев„ 2017
 *      Author: Itamar
 */

/**
 * settingParser summary:
 *
 * A parser for the Settings Section in the game.
 * The Parser includes functions that accept inputs from the user, no long than 1024 Byte,
 * and parse them to specific commands for determining the game settings.
 * A summary of the supported functions is given below:
 *
 *
 *
 *
 * settingAcceptor		   	- Accepts input from the user's command line.
 * spParserIsInt           	- Checking if the String is made only of in Integers.
 * isFileExist		       	- Checking if a given file's path exists.
 * destroySettingStruct    	- Destroying the setting Structure.
 * initChessCommand        	- Initializing the Setting Struct with false and invalid values.
 * diffiDecider     		- parsing the game difficulty.
 * gameModeDecider     		- parsing how many players.
 * gameColorDecider    		- parsing the user's color in the game.
 * diffLevelToInt			- Converting from difficulty Command to an int.
 * settingParser            - The controller function which manage the commands.
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "settingParser.h"

#define BUFFER 1024


/**
 *
 *  Converting from Difficulty Command to the parallel Integer.
 *  @param cmd - the command message.
 *  @return
 *  -1, if the command is not Difficulty type.
 *  Integer between 1-5 if the command is right.
 *
 */
int diffLevelToInt(SETTING_COMMAND cmd){
	if(cmd==DIFFICULTY_1) return 1;
	else if(cmd==DIFFICULTY_2) return 2;
	else if(cmd==DIFFICULTY_3) return 3;
	else if(cmd==DIFFICULTY_4) return 4;
	else if(cmd==DIFFICULTY_5) return 5;
	else return -1;
}

/**
 *
 * Checking is a String is an Integer (consisted only from numbers).
 * @param str - the String above mentioned.
 * @return
 * false -  if a char is not an Integer.
 * true - if every char in the string is Integer.
 *
 */
bool spParserIsInt(const char* str){
    int index = 0;
    int validNum;
    while(str[index]!='\0'){
        if(str[index]=='\n'){
            index++;
            continue;
        }
        validNum = str[index]-'0';
        if(str[0]=='-' && strlen(str)>1 &&index==0){
            index++;
            continue;
        }
        else if(validNum<0 || validNum>9)return false;
        index++;
    }
    return true;
}

/**
 *
 * Converting from a String to game_mode Command (1 player to 2 players).
 * @param str - the String above mentioned.
 * @return
 * Command Message. if the string is illegal an Invalid Command Message will return.
 *
 */

SETTING_COMMAND gameModeDecider(char* str){
	assert(str!=NULL);
	bool isInt = spParserIsInt(str);
	if(!isInt) return INVALID_GAME_MODE;
	int num = atoi(str);
	if(num<1||num>2) return INVALID_GAME_MODE;
	else{
		switch(num){
			case 1:
				return GAME_MODE_1;
			case 2:
				return GAME_MODE_2;
			default:
				return INVALID_GAME_MODE;
			}
		}
	}



/**
 *
 * Converting from a String to user_color Command (black or white).
 * @param str - the String above mentioned.
 * @return
 * Command Message. if the string is illegal an Invalid Command Message will return.
 *
 */

SETTING_COMMAND gameColorDecider(char* str, int numPlayers){
	assert(str!=NULL);
	if (numPlayers==2) return INVALID_LINE1;
	bool isInt = spParserIsInt(str);
	if(!isInt) return INVALID_LINE1;
	int num = atoi(str);
	if(num<0||num>1) return INVALID_LINE1;
	else{
		switch(num){
			case 0:
				return USER_COL_0;
			case 1:
				return USER_COL_1;
			default:
				return INVALID_LINE1;
			}
		}
	}


/**
 *
 * Converting from a String to difficulty Command (1-5).
 * @param  str - the String above mentioned.
 * @param  Players - number of players in game (1 or 2)
 * @return
 * Command Message. if the string is illegal an Invalid Command Message will return.
 *
 */

SETTING_COMMAND diffiDecider(char* str, int Players){
	assert(str!=NULL);
	if (Players==2) return INVALID_LINE1;
	bool isInt = spParserIsInt(str);
	if(!isInt) return INVALID_DIFFICULT;
	int num = atoi(str);
	if(num<1||num>5) return INVALID_DIFFICULT;
	else{
		switch(num){
			case 1:
				return DIFFICULTY_1;
			case 2:
				return DIFFICULTY_2;
			case 3:
				return DIFFICULTY_3;
			case 4:
				return DIFFICULTY_4;
			case 5:
				return DIFFICULTY_5;
			default:
				return INVALID_DIFFICULT;
			}
		}
}


/**
 *
 * Checking if a path (String) is exist or not
 * @param path - the path above mentioned.
 * @return
 * False - if the file in the path is not exist.
 * True - otherwise.
 *
 */

bool isFileExist(const char* path){
	assert(path!=NULL);
	FILE* fp;
	char*realpath = (char*)malloc(sizeof(char)*strlen(path)+1);
	assert(realpath!=NULL);
	strcpy(realpath,path);
	fp=fopen(realpath,"r");
	if(fp==NULL){
		free(realpath);
		return false;
	}
	fclose(fp);
	free(realpath);
	return true;
}

/**
 *
 * Destroying the structure holding the commands and free the memory.
 * @param  cmd - the data structure.
 * @return
 * no Return value.
 *
 */

void destroySettingStruct(ChessCommand* cmd){
	assert(cmd!=NULL);
	if(cmd->cmd==LOAD_FILE){
		if(cmd->path!=NULL) free(cmd->path);
	}
	free(cmd);
}


/**
 *
 * Accepting user's input from the comamand line.
 * @return
 * returns the user's input as a string.
 *
 */
char* settingAcceptor(){
	char* input = (char*)malloc(sizeof(char)*BUFFER);
	char* errorDet = fgets(input,BUFFER,stdin); //handle the case errorDet=NULL;
	if(errorDet==NULL){
		printf("ERROR: fgets function has failed\n");
		free(input);
	}
	return input;
}

/**
 *
 * Initializing the cmd Data Structure by creating space in memory
 * and giving "invalid" values for the variables.
 *
 * @return
 * pointer to ChessCommand Data Structure.
 *
 */
ChessCommand* initChessCommand(){
	ChessCommand* command = (ChessCommand*) malloc(sizeof(ChessCommand));
	assert(command!=NULL);
	command->validArg = true;
	command->cmd = INVALID_LINE1;
	return command;
}


/**
 *
 *
 * The main parsing function which managing the parsing data structure.
 * @param str - the user's input
 * @param numPlayers - the game Mode (1 players as default or 2 players)
 * @return
 * Chess Command data Structure with the correct values and commands.
 *
 */

ChessCommand* settingParser(const char* str, int numPlayers){
	ChessCommand* command = (ChessCommand*)initChessCommand();
	assert(command!=NULL); assert(str!=NULL);
	char stringDup[1024] = {'i','n','i','t','i','a','l'};
	strcpy(stringDup,str);
	char *token = strtok(stringDup, "\t\r\n ");
	int decider = 0;
	command->validArg = false;
	if(token==NULL) return command;
	else if(strcmp(token, "start")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL) command->cmd = START;}
	else if(strcmp(token, "quit")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL )command->cmd = QUIT1;}
	else if(strcmp(token, "default")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL) command->cmd = DEFAULT;}
	else if(strcmp(token, "print_setting")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL) command->cmd = PRINT_SETTINGS;}
	else if((strcmp(token, "game_mode")==0)||(strcmp(token, "difficulty")==0) ||(strcmp(token, "user_color")==0)){
		if ((strcmp(token, "game_mode")==0)) decider = 1;
		else if ((strcmp(token, "difficulty")==0)) decider = 2;
		else if ((strcmp(token, "user_color")==0)) decider = 3;
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL)	return command;
		SETTING_COMMAND cmd = INVALID_LINE1;
		if (decider==1) cmd = gameModeDecider(token);
		else if(decider==2) cmd = diffiDecider(token,numPlayers);
		else if (decider==3) cmd = gameColorDecider(token, numPlayers);
		command->cmd = cmd;
		if((cmd==INVALID_DIFFICULT)|| (cmd==INVALID_GAME_MODE)|| cmd==INVALID_LINE1){
			command->validArg = false;
			return command;}
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL) command->validArg = true;
		else{
			command->validArg = false;
			command->cmd = INVALID_LINE1;}
		return command;}
	else if((strcmp(token, "load")==0)){
		bool isPath = false;
		token = strtok(NULL, "\t\r\n ");
		bool exist = isFileExist(token);
		if(!exist) command->cmd = INVALID_FILE;
		else if(exist){
			command->path = (char*)malloc(sizeof(char)*(strlen(token)+1));
			strcpy(command->path,token);
			command->cmd = LOAD_FILE;
			command->validArg = true;
			isPath = true;}
		token = strtok(NULL, "\t\r\n ");
		if(token!=NULL){
			command->cmd = INVALID_LINE1;
			command->validArg = false;
			if(isPath==true) free(command->path);}}
	if(command->cmd==QUIT1 || command->cmd==DEFAULT  || command->cmd==PRINT_SETTINGS || command->cmd==START){
		command->validArg = true;}
	return command;
}


