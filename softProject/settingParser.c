/*
 * settingParser.c
 *
 *  Created on: 19 баев„ 2017
 *      Author: Itamar
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "settingParser.h"
#include "boardFuncs.h"

#define BUFFER 1024



int diffLevelToInt(SETTING_COMMAND cmd){
	if(cmd==DIFFICULTY_1) return 1;
	else if(cmd==DIFFICULTY_2) return 2;
	else if(cmd==DIFFICULTY_3) return 3;
	else if(cmd==DIFFICULTY_4) return 4;
	else if(cmd==DIFFICULTY_5) return 5;
	else return -1;
}


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

bool isFileExist(const char* path){
	assert(path!=NULL);
	FILE* fp;
	char*realpath = (char*)malloc(sizeof(char)*strlen(path)+1);
	assert(realpath!=NULL);
	strcpy(realpath,path);
	fp=fopen(realpath,"r");
	if(fp==NULL){
		fclose(fp);
		free(realpath);
		return false;
	}
	fclose(fp);
	free(realpath);
	return true;
}


void destroySettingStruct(ChessCommand* cmd){
	assert(cmd!=NULL);
	if(cmd->path!=NULL) free(cmd->path);
	free(cmd);
}

char* settingAcceptor(){

	char* input = (char*)malloc(sizeof(char)*BUFFER);
	char* errorDet = fgets(input,BUFFER,stdin); //handle the case errorDet=NULL;
	if(errorDet==NULL){
		printf("ERROR: fgets function has faild");
		free(errorDet);
		free(input);
	}
	return input;
	}


ChessCommand* settingParser(const char* str, int numPlayers){
	ChessCommand* command = (ChessCommand*)malloc(sizeof(ChessCommand));
	assert(command!=NULL);
	assert(str!=NULL);
	command->validArg = true;
	char stringDup[1024];
	strcpy(stringDup,str);
	char *token = strtok(stringDup, "\t\r\n ");
	int decider = 0;
	if(token==NULL) {
		command->cmd = INVALID_LINE1;
		command->validArg = false;
		return command;
	}
	else if(strcmp(token, "start")==0)command->cmd = START;
	else if(strcmp(token, "quit")==0)command->cmd = QUIT1;
	else if(strcmp(token, "default")==0)command->cmd = DEFAULT;
	else if(strcmp(token, "print_setting")==0)command->cmd = PRINT_SETTINGS;
	else if((strcmp(token, "game_mode")==0)||(strcmp(token, "difficulty")==0)
			||(strcmp(token, "user_color")==0)){
		if ((strcmp(token, "game_mode")==0)) decider = 1;
		else if ((strcmp(token, "difficulty")==0)) decider = 2;
		else if ((strcmp(token, "user_color")==0)) decider = 3;
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL || !spParserIsInt(token)){
			command->cmd = INVALID_LINE1;
			command->validArg = false;
			return command;
		}
		SETTING_COMMAND cmd;
		if (decider==1) cmd = gameModeDecider(token);
		else if(decider==2) cmd = diffiDecider(token,numPlayers);
		else if (decider==3) cmd = gameColorDecider(token, numPlayers);
		command->cmd = cmd;
		if((cmd==INVALID_DIFFICULT)|| (cmd==INVALID_GAME_MODE)|| cmd==INVALID_LINE1){
			command->validArg = false;
			return command;
		}
	}
	else if((strcmp(token, "load")==0)){
		token = strtok(NULL, "\t\r\n");
		if(!isFileExist(token)){
			command->cmd = INVALID_FILE;
			command->validArg = false;
			return command;
		}
		command->path = (char*)malloc(sizeof(char)*(strlen(token)+1));
		strcpy(command->path,token);
		//int n = strlen(token)-1;
		command->cmd = LOAD_FILE;
	}
	else{
		command->cmd = INVALID_LINE1;
		command->validArg = false;

	}
	return command;
}


