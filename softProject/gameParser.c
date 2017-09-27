/*
 * gameParser.c
 *
 *  Created on: 19 ����� 2017
 *      Author: Itamar
 */

#include "gameParser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


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
		//Unneccessery fclose(fp);
		free(realpath);
		return false;
	}
	fclose(fp);
	free(realpath);
	return true;
}


void destroyGameStruct(GameCommand* cmd){
	//printf("inside destroy game struct\n");
	assert(cmd!=NULL);
	if(cmd->cmd==SAVE){
		if(cmd->path!=NULL) free(cmd->path);
	}
	free(cmd);
}



char* gameAcceptor(){
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);
	char* input = (char*)malloc(sizeof(char)*BUFFER);
	char* errorDet = fgets(input,BUFFER,stdin); //handle the case errorDet=NULL;
	if(errorDet==NULL){
		printf("ERROR: fgets has failed\n");
		//free(errorDet);
		free(input);
	}
	//printf("game acceptor works fine\n");
	return input;
	}





GameCommand* gameParser(const char* str){
	GameCommand* command = (GameCommand*)malloc(sizeof(GameCommand));
	assert(command!=NULL); assert(str!=NULL);
	command->validArg = true;
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	command->cmd = INVALID_LINE2;
	command->validArg = false;
	char stringDup[1024] = {'i','n','t','i','a','l'};
	//printf("stringDup is:%s\n", stringDup);
	strcpy(stringDup,str);
	//printf("stringDup is:%s\n", stringDup);
	char *token = strtok(stringDup, "\t\r\n ");
	if(token==NULL) {
		//printf("NULL");
		return command;
	}
	else if(strcmp(token, "quit")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL){
			command->cmd = QUIT2;
			command->validArg = true;
			return command;
		}
	}
	else if(strcmp(token, "undo")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL){
			command->cmd = UNDO;
			command->validArg = true;
			return command;
		}
	}
	else if(strcmp(token, "reset")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL){
			command->cmd = RESET;
			command->validArg = true;
			return command;
		}
	}
	else if((strcmp(token, "save")==0)){
		bool isPath = false;
		token = strtok(NULL, "\t\r\n ");
		bool isCreated = isFileCreated(token);
		if(!isCreated)command->cmd = INVALID_SAVE;
		else if(isCreated){
			command->path = (char*)malloc(sizeof(char)*(strlen(token)+1));
			strcpy(command->path,token);
			command->cmd = SAVE;
			command->validArg = true;
			isPath = true;
		}
		token = strtok(NULL, "\t\r\n ");
		if(token!=NULL){
			command->cmd = INVALID_LINE2;
			command->validArg = false;
			if(isPath==true) free(command->path);
		}
		return command;
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
		return command;
	}
	else if((strcmp(token, "get_moves")==0)){
		command->cmd = INVALID_LINE2;
		command->validArg = false;
		token = strtok(NULL, "\t\r\n ");
		if(token!=NULL){
			int val = isTri(token);
			//printf("the return number is:%d\n",val);
			if(val==-1) command->cmd = INVALID_LINE2;
			else if(val==1|| val==0){
				if(val==0)command->cmd = INVALID_POSITION;
				int row = (int) token[1]-'1';
				int col = (int) token[3]-'A';
				command->position = RowColToNum(7-row,col);
				token = strtok(NULL, "\t\r\n ");
				if(token==NULL){
					command->destination = RowColToNum(7-row,col);
					command->cmd = GET_MOVES;
					command->validArg = true;
				}
				else command->cmd = INVALID_LINE2;
			}
		}
		return command;
	}
	return command;
}


int NumToRow(int num){
	int row = num/8;
	return row;
}

int NumToCol(int num){
	int col = num%8;
	return col;
}

int RowColToNum(int row, int col){
	int num = 8*row + col;
	return num;
}

