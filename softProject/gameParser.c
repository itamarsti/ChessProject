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



int isTri(char* str){
	assert(str!=NULL);
	int counter = 0;
	bool invalidPosition = false;
	if (str[0]!='<'){
		//printf("not starts with < char\n");
		return -1;	//not tight format
	}
	//printf("the char is:%c	 the counter is:%d\n",str[counter],counter);
	counter++;
	while(str[counter]!=','){
		//printf("the char is:%c	 the counter is:%d\n",str[counter],counter);
		if(str[counter]=='\0') return -1;
		counter++;
	}
	if(counter==1) return -1;
	if(counter>2){
		//printf("invalidPosition was changed in the first time\n");
		invalidPosition =true;
	}
	int counterComma = counter;
	while(str[counter]!='>'){
		//printf("the char is:%c	 the counter is:%d\n",str[counter],counter);
		if(str[counter]=='\0') return -1;
		counter++;
	}
	//printf("the char is:%c	 the counter is:%d\n",str[counter],counter);
	if(counter == counterComma+1) return -1;
	if(counter >counterComma+2) invalidPosition =true;
	counter++;
	while(str[counter]!='\0'){
		//printf("the char is:%c	 the counter is:%d\n",str[counter],counter);
		//printf("in while loop\n");
		if(str[counter]=='\r' || str[counter]=='\t' || str[counter]==' ' || str[counter]=='\n'){
			counter++;
			continue;
		}
		else{
			return -1;
		}
	}
	//printf("the row is:%d, the col is:%d \n",(str[1]-'0'),(int)str[3]-'A');
	if ((int)(str[1]-'0')>=1 && (int)(str[1]-'0')<=8 && (int)str[3]>='A'
			&& (int)str[3]<='H' && invalidPosition==false) return 1;
	return 0;
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
	return input;
	}





GameCommand* gameParser(const char* str){
	GameCommand* command = (GameCommand*)malloc(sizeof(GameCommand));
	assert(command!=NULL); assert(str!=NULL);
	command->validArg = true;
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	char stringDup[1024];
	strcpy(stringDup,str);
	char *token = strtok(stringDup, "\t\r\n ");
	if(token==NULL) {
		printf("NULL");
		command->cmd = INVALID_LINE2;
		command->validArg = false;
		return command;
	}
	else if(strcmp(token, "quit")==0) command->cmd = QUIT2;
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
	else if(strcmp(token, "move")==0){
		command->validArg = false;
		token = strtok(NULL, "\t\r\n ");
		if(token!=NULL){
			int val = isTri(token);
			if(val==-1) command->cmd = INVALID_LINE2;
			else if(val==1|| val==0){
				if(val==0)command->cmd = INVALID_POSITION;
				int row = (int) token[1]-'1';
				int col = (int) token[3]-'A';
				command->position = RowColToNum(7-row,col);
				token = strtok(NULL, "\t\r\n ");
				//printf("in here\n");
				if(strcmp(token, "to")==0){
					token = strtok(NULL, "\t\r\n ");
					if(token!=NULL){
						if(isTri(token)==-1) command->cmd = INVALID_LINE2;
						else if(isTri(token)==0) command->cmd = INVALID_POSITION;
						else if(isTri(token)==1){
							int row = token[1]-'1';
							int col = token[3]-'A';
							token = strtok(NULL, "\t\r\n ");
							if(token==NULL){
								command->destination = RowColToNum(7-row,col);
								command->cmd = MOVE;
								command->validArg = true;
							}
							else command->cmd = INVALID_LINE2;
						}
					}
				}
				else{
					//printf("in here\n");
					command->cmd = INVALID_LINE2;
				}
			}
		}
	}
	else if((strcmp(token, "get_moves")==0)){
			command->cmd = INVALID_LINE2;
			command->validArg = false;
			token = strtok(NULL, "\t\r\n ");
			if(token!=NULL && isTri(token)){
				int row = token[1]-'1';
				int col = token[3]-'A';
				command->position = RowColToNum(7-row,col);
				command->destination = 64;
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
