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
#include "settingFlow.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(int argc, char* argv[]) {
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);
    while(1){
    	bool resetBool = false;
    	boardGame* mainBoard = createBoard();
		initBoard(mainBoard);
		mainSettingFlow(mainBoard);				//setting Function. Continues when user type "Start".
		while(!resetBool){
			printBoard(mainBoard);
			mainGameFlow(board);
		}
    }



	return 0;
}
