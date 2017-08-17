/*
 * settingCommands.c
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "settingCommands.h"
#define BUFFER 1024



char* commandsAcc(){
    setvbuf (stdout, NULL, _IONBF, 0);
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	fflush(stdout);
	char input[BUFFER];
	char* errorDet;
	errorDet = fgets(input,BUFFER,stdin); //handle the case errorDet=NULL;
	printf("the string is %s\n",input);
	printf("the String length is:%d",strlen(input));
	return input;
	}


ChessCommand commandParser(const char* str){
	ChessCommand command;
	command.validArg = true;
	char stringDup[1024];
	strcpy(stringDup,str);
	char *token = strtok(stringDup, "\t\r\n ");
	if(token==NULL){
		command.cmd = INVALID_LINE1;
		command.validArg = false;}
	else if(strcmp(token, "start")==0){
		command.cmd = START;}
	else if(strcmp(token, "game_mode 1")==0){
		command.cmd = GAME_MODE_1;}
	else if(strcmp(token, "game_mode 2")==0){
		command.cmd = GAME_MODE_2;}
	else if(strcmp(token, "difficulty 1")==0){
		command.cmd = DIFFICULTY_1;}
	else if(strcmp(token, "difficulty 2")==0){
		command.cmd = DIFFICULTY_2;}
	else if(strcmp(token, "difficulty 3")==0){
		command.cmd = DIFFICULTY_3;}
	else if(strcmp(token, "difficulty 4")==0){
		command.cmd = DIFFICULTY_4;}
	else if(strcmp(token, "difficulty 5")==0){
		command.cmd = DIFFICULTY_5;}
	else if(strcmp(token, "user_color 0")==0){
		command.cmd = USER_COL_0;}
	else if(strcmp(token, "user_color 1")==0){
		command.cmd = USER_COL_1;}
	else if(strcmp(token, "load 5")==0){
		command.cmd = LOAD_FILE;}
	else if(strcmp(token, "default")==0){
		command.cmd = DEFAULT;}
	else if(strcmp(token, "print_setting")==0){
		command.cmd = PRINT_SETTINGS;}
	else if(strcmp(token, "quit")==0){
		command.cmd = QUIT1;}
	else{
		command.cmd = INVALID_LINE1;
		command.validArg = false;}
	return command;
}

int diffLevelToInt(SETTING_COMMAND cmd){
	if(cmd==DIFFICULTY_1) return 1;
	else if(cmd==DIFFICULTY_2) return 2;
	else if(cmd==DIFFICULTY_3) return 3;
	else if(cmd==DIFFICULTY_4) return 4;
	else if(cmd==DIFFICULTY_5) return 5;
	else return -1;
}

