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
	bool consoleBool = false;
	if(!consoleBool){
		boardGame* mainBoard = createBoard();
		initBoard(mainBoard);
		guiMain(mainBoard);
	}
	else if(consoleBool){
		while(1){
			boardGame* mainBoard = createBoard();
			initBoard(mainBoard);
			mainSettingFlow(mainBoard);				//setting Function. Continues when user type "Start".
			while(!resetBool){
				printBoard(mainBoard);
				if(mainBoard->gameMode==1){
					if(mainBoard->curPlayer!=mainBoard->userCol){
						//printf("ready to start moveAiObj\n");
						moveAIobj(mainBoard);
					}
					else if(mainBoard->curPlayer==mainBoard->userCol){
					resetBool = mainGameFlow(mainBoard);	//we changed the turns so now we also checking the opponent's king
					}
				}
				else if (mainBoard->gameMode==2){
					resetBool = mainGameFlow(mainBoard);	//we changed the turns so now we also checking the opponent's king
				}
			}
			resetBool = false;

		}

	}


	return 0;
}
