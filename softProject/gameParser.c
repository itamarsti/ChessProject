/*
 * gameParser.c
 *
 *  Created on: 19 баев„ 2017
 *      Author: Itamar
 */

#include "boardFuncs.h"
#include "settingParser.h"
#include "gameParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "gameCommands.h"

#define BUFFER 1024

char* gameAcceptor(){
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);
	char* input = (char*)malloc(sizeof(char)*BUFFER);
	char* errorDet = fgets(input,BUFFER,stdin); //handle the case errorDet=NULL;
	if(errorDet==NULL){
		printf("fgets has faild");
		free(errorDet);
		free(input);
	}
	printf("the string is %s\n",input);
	printf("the String length is:%d",strlen(input));
	return input;
	}





GameCommand* gameParser(const char* str){
	GameCommand* command = (GameCommand*)malloc(sizeof(GameCommand));
	assert(command!=NULL);
	assert(str!=NULL);
	command->validArg = true;
	char stringDup[1024];
	strcpy(stringDup,str);
	char *token = strtok(stringDup, "\t\r\n ");
	if(token==NULL) {
		command->cmd = INVALID_LINE2;
		command->validArg = false;
		return command;
	}
	else if(strcmp(token, "quit")==0)command->cmd = QUIT2;
	else if(strcmp(token, "undo")==0)command->cmd = UNDO;
	else if(strcmp(token, "reset")==0)command->cmd = RESET;
	else if((strcmp(token, "save")==0)){
		token = strtok(NULL, "\t\r\n");
		if(!isFileCreated(token)){
			command->cmd = INVALID_SAVE;
			command->validArg = false;
			return command;
		}
		command->path = (char*)malloc(sizeof(char)*(strlen(token)+1));
		strcpy(command->path,token);
		command->cmd = SAVE;
	}
	else if(strcmp(token, "move")){
		command->cmd = INVALID_LINE2;
		command->validArg = false;
		token = strtok(NULL, "\t\r\n ");
		if(token!=NULL && isTri(token)){
			int row = token[1]-'0';
			int col = token[3]-'A';
			command->position = RowColToNum(row,col);
			token = strtok(NULL, "\t\r\n ");
			if(token!=NULL && isTri(token)){
				int row = token[1]-'0';
				int col = token[3]-'A';
				command->destination = RowColToNum(row,col);
				command->cmd = MOVE;
				command->validArg = true;
			}
		}
	}
	else if(strcmp(token, "get_moves")){
			command->cmd = INVALID_LINE2;
			command->validArg = false;
			token = strtok(NULL, "\t\r\n ");
			if(token!=NULL && isTri(token)){
				int row = token[1]-'0';
				int col = token[3]-'A';
				command->position = RowColToNum(row,col);
				command->destination = RowColToNum(row,col);
				command->cmd = GET_MOVES;
				command->validArg = true;
				}
			}
	else{
		command->cmd = INVALID_LINE2;
		command->validArg = false;
	}
	return command;
}

bool isTri(char* str){
	assert(str!=NULL);
	if (strlen(str)!=5) return false;
	if (str[0]!='<'||str[2]!=','||str[4]!='>')return false;
	if ((str[1]-'0')<0 || (str[1]-'0')>9 || str[3]<'A' || str[3]>'Z') return false;
	return true;
}

bool isFileCreated(const char* path){
	assert(path!=NULL);
	FILE* fp;
	char*realpath = (char*)malloc(sizeof(char)*strlen(path)+1);
	assert(realpath!=NULL);
	strcpy(realpath,path);
	fp=fopen(realpath,"w");
	if(fp==NULL){
		fclose(fp);
		free(realpath);
		return false;
	}
	fclose(fp);
	free(realpath);
	return true;
}


void destroyGameStruct(GameCommand* cmd){
	assert(cmd!=NULL);
	if(cmd->path!=NULL) free(cmd->path);
	free(cmd);
}
