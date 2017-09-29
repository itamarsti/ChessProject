/*
 * gameParser.c
 *
 *  Created on: 19 баев„ 2017
 *      Author: Itamar
 */

#include "gameParser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>




/*
 * gameParser summary:
 *
 * A parser for the Settings Section in the game.
 * The Parser includes functions that accept inputs from the user, no long than 1024 Byte,
 * and parse them to specific commands for game actions.
 * A summary of the supported functions is given below:
 *
 *
 * isTri		   			- Asserting if string is in the form of "<char*,char*>
 * isFileCreated           	- Checking if the save path is illegal and the file can be created.
 * destroyGameStruct		- Destroying the game Command Structure.
 * gameAcceptor    			- Accepting inputs from user
 * gameParser        		- Managing the parsing from input String -> till game command Structure.
 * NumToRow     			- converting position between 0-63 to a row on boardGame.
 * NumToCol     			- converting position between 0-63 to a column on boardGame.
 * RowColToNum    			- converting row & column to position between 0-63.
 *
 *
 *
 */


#define BUFFER 1024

/**
 *
 *  Asserting that a String is of the form of "<Integer, Char>"
 *  @param str - the String
 *  @return
 *  -1, if the command is invalid (illegal format);
 *  0, if the string is in the form of <char*, char*>
 *  1 if it's in the right form of "<Integer, Char>"
 *
 *
 */
int isTri(char* str){
	assert(str!=NULL);
	int counter = 0;
	bool invalidPosition = false;
	if (str[0]!='<'){
		return -1;	//not tight format
	}
	counter++;
	while(str[counter]!=','){
		if(str[counter]=='\0') return -1;
		counter++;
	}
	if(counter==1) return -1;
	if(counter>2){
		invalidPosition =true;
	}
	int counterComma = counter;
	while(str[counter]!='>'){
		if(str[counter]=='\0') return -1;
		counter++;
	}
	if(counter == counterComma+1) return -1;
	if(counter >counterComma+2) invalidPosition =true;
	counter++;
	while(str[counter]!='\0'){
		if(str[counter]=='\r' || str[counter]=='\t' || str[counter]==' ' || str[counter]=='\n'){
			counter++;
			continue;
		}
		else{
			return -1;
		}
	}
	if ((int)(str[1]-'0')>=1 && (int)(str[1]-'0')<=8 && (int)str[3]>='A'
			&& (int)str[3]<='H' && invalidPosition==false) return 1;
	return 0;
}


/**
 *
 *  Asserting that a a given path of file can be created locally.
 *  @param path - the above mentioned path
 *  @return
 *  true if it's can be created, else - false.
 *
 *
 */
bool isFileCreated(const char* path){
	assert(path!=NULL);
	FILE* fp;
	char*realpath = (char*)malloc(sizeof(char)*strlen(path)+1);
	assert(realpath!=NULL);
	strcpy(realpath,path);
	fp=fopen(realpath,"w");
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
 *  Destroying the Game Command data structure.
 *  @param cmd - the data structure
 *  @return
 *  void.
 *
 *
 */

void destroyGameStruct(GameCommand* cmd){
	//printf("inside destroy game struct\n");
	assert(cmd!=NULL);
	if(cmd->cmd==SAVE){
		if(cmd->path!=NULL) free(cmd->path);
	}
	free(cmd);
}

/**
 *
 *  Accepting game inputs from the user.
 *  @return
 *  The user's input as a String.
 *
 *
 */


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

/**
 *
 *  Creating the data Structure of game Command and sets the right arguments in it,
 *  depends on the user's input (parsing from input to Game Command data structure).
 *  @param str - the user's input as a string
 *  @return
 *  GameCommand data Structure which contains the game's instructions.
 *
 *
 */
GameCommand* gameParser(const char* str){
	GameCommand* command = (GameCommand*)malloc(sizeof(GameCommand));
	assert(command!=NULL); assert(str!=NULL);
	setvbuf (stdout, NULL, _IONBF, 0);	fflush(stdout);
	command->cmd = INVALID_LINE2;
	command->validArg = false;
	char stringDup[1024] = {'i','n','t','i','a','l'};
	strcpy(stringDup,str);
	char *token = strtok(stringDup, "\t\r\n ");
	if(token==NULL)	return command;
	else if(strcmp(token, "quit")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL)command->cmd = QUIT2;}
	else if(strcmp(token, "undo")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL)command->cmd = UNDO;}
	else if(strcmp(token, "reset")==0){
		token = strtok(NULL, "\t\r\n ");
		if(token==NULL)command->cmd = RESET;}
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
			isPath = true;}
		token = strtok(NULL, "\t\r\n ");
		if(token!=NULL){
			command->cmd = INVALID_LINE2;
			command->validArg = false;
			if(isPath==true) free(command->path);}
		return command;}
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
								command->validArg = true;}
							else command->cmd = INVALID_LINE2;}}}
				else{
					command->cmd = INVALID_LINE2;}}}
		return command;}
	else if((strcmp(token, "get_moves")==0)){
		command->cmd = INVALID_LINE2;
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
				if(token==NULL){
					command->destination = RowColToNum(7-row,col);
					command->cmd = GET_MOVES;
					command->validArg = true;}
				else command->cmd = INVALID_LINE2;}}
		return command;}
	if(command->cmd==QUIT2 || command->cmd==UNDO || command->cmd==RESET) command->validArg=true;
	return command;
}

/**
 *
 *  Converting position between 0-63 on BoardGame to a specific row.
 *  @param num - Integer in the range of 0-63
 *  @return
 *  The row on BoardGame (Integer)
 *
 */

int NumToRow(int num){
	int row = num/8;
	return row;
}

/**
 *
 *  Converting position between 0-63 on BoardGame to a specific column.
 *  @param num - Integer in the range of 0-63
 *  @return
 *  The column on BoardGame (Integer)
 *
 */
int NumToCol(int num){
	int col = num%8;
	return col;
}


/**
 *
 *  Converting a given column & row to a position in range 0-63.
 *  @param row - Integer in the range of 0-7
 *  @param col - Integer in the range of 0-7
 *  @return
 *  position in the range of 0-63 (Integer)
 *
 */
int RowColToNum(int row, int col){
	int num = 8*row + col;
	return num;
}

