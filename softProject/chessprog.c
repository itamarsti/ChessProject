/*
 * chessprog.c
 *
 *  Created on: 9 баев„ 2017
 *      Author: Itamar
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "boardFuncs.h"
#include "settingParser.h"
#include "moveOps.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);
    char* var =(char*) commandsAcc();
    ChessCommand* cc = (ChessCommand*) cmdParser(var);
    if(cc->cmd==START)printf("\nstart succeeded");
    else if(cc->cmd==GAME_MODE_1)printf("\nGAME_MODE_1 succeeded");
    else if(cc->cmd==GAME_MODE_2)printf("\nGAME_MODE_2 succeeded");
    else if(cc->cmd==DIFFICULTY_1)printf("\nDIFFICULTY_1 succeeded");
    else if(cc->cmd==DIFFICULTY_2)printf("\nDIFFICULTY_2 succeeded");
    else if(cc->cmd==DIFFICULTY_3)printf("\nDIFFICULTY_3 succeeded");
    else if(cc->cmd==DIFFICULTY_4)printf("\nDIFFICULTY_4 succeeded");
    else if(cc->cmd==DIFFICULTY_5)printf("\nDIFFICULTY_5 succeeded");
    else if(cc->cmd==INVALID_DIFFICULT)printf("\nINVALID_DIFFICULT succeeded");
    else if(cc->cmd==USER_COL_0)printf("\nUSER_COL_0 succeeded");
    else if(cc->cmd==USER_COL_1)printf("\nUSER_COL_1 succeeded");
    else if(cc->cmd==LOAD_FILE){
    	printf("\nLOAD_FILE succeeded");
    	printf("\nthe path is: %s",cc->path);
    }
    else if(cc->cmd==INVALID_LINE1)printf("\nINVALID_LINE1 succeeded");
    else if(cc->cmd==INVALID_FILE)printf("\nINVALID_FILE succeeded");
    else if(cc->cmd==DEFAULT)printf("\nDEFAULT succeeded");
    else if(cc->cmd==PRINT_SETTINGS)printf("\nPRINT_SETTINGS succeeded");
    else if(cc->cmd==QUIT1)printf("\nQUIT1 succeeded");




	return 0;
}
