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
#include "gameFlow.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(int argc, char* argv[]) {
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);
	bool resetBool = false;
    while(1){
    	boardGame* mainBoard = createBoard();
		initBoard(mainBoard);
		mainSettingFlow(mainBoard);				//setting Function. Continues when user type "Start".
		while(!resetBool){
			printBoard(mainBoard);
			resetBool = mainGameFlow(mainBoard);
		}
		resetBool = true;
    }



	return 0;
}
