/*
 * chessprog.c
 *
 *  Created on: 9 баев„ 2017
 *      Author: Itamar
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "boardFuncs.h"
#include "settingCommands.h"
#include "moveOps.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);
	boardGame* mainBoard = createBoard();
	initBoard(mainBoard);
	printBoard(mainBoard);
	char str[] ="difficulty 1132";
	char * pch;
	printf ("Splitting string \"%s\" into tokens:\n",str);
	pch = (char*)strtok (str," ,.-");
	printf("\n%d\n",strlen(pch));
	printf ("%s\n",pch);
	char buffer[strlen(pch)+1];
	strcpy(buffer,pch);
	if(strcmp(buffer,"difficulty")==0){
		printf("lala");
	}
	pch = (char*)strtok (NULL, " ,.-");
	printf("\n%d\n",strlen(pch));
	printf ("%s\n",pch);


	return 0;
}
