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
#include "gameCommands.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "GUI.h"


int main(int argc, char* argv[]) {
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);
	bool resetBool = false;

    while(1){
    	boardGame* mainBoard = createBoard();
		initBoard(mainBoard);
		guiMain(mainBoard);
		mainSettingFlow(mainBoard);				//setting Function. Continues when user type "Start".
		while(!resetBool){
			printBoard(mainBoard);
			resetBool = mainGameFlow(mainBoard);	//we changed the turns so now we are checking the opponent's king
			if(!isMyKingSafe(mainBoard))printCheckMessage(mainBoard->curPlayer);
		resetBool = true;
		}
    }
	return 0;
}
