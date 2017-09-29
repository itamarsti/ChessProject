/*
 * chessprog.c
 *
 *  Created on: 9 баев„ 2017
 *      Author: Itamar
 */

#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "chessprog.h"



/**
 * chessprog summary:
 *
 * The opening part of the game.
 *
 * main	- responsible for choosing if console/GUI and also runs the main Loop of the console mode.
 *
 *
 */

/**
 *
 *
 * Determine if we are going to play in GUI mode or in console mode.
 * Also, in case of console mode, runing the main game loop using the settingFlow and gameFlow
 * functions.
 * @param argc - number of inputs in the commandLine.
 * @param argv - the commandLine options. argv[0] the program name, argv[1],
 * 					("-g" for GUI, "-c" for console).
 * @return 0 (no meaning).
 *
 *
 */
int main(int argc, char* argv[]) {
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);
	bool resetBool = false;
	bool consoleBool = false;
	if(argc==1 || (argc==2 && strcmp(argv[1],"-c")==0)) consoleBool = true;
	else if(argc==2 && strcmp(argv[1],"-g")==0) consoleBool = false;
	if(!consoleBool){
		guiMain();
	}
	else if(consoleBool){
		while(1){
			boardGame* mainBoard = createBoard();
			initBoard(mainBoard, true);
			mainSettingFlow(mainBoard);				//setting Function. Continues when user type "Start".
			resetBool = false;
			if((mainBoard->gameMode==1)&& mainBoard->curPlayer==mainBoard->userCol) printBoard(mainBoard);
			while(!resetBool){
				if(mainBoard->gameMode==1){
					if(mainBoard->curPlayer!=mainBoard->userCol){
						moveAIobj(mainBoard, true);
						printBoard(mainBoard);
					}
					else if(mainBoard->curPlayer==mainBoard->userCol){
						resetBool = mainGameFlow(mainBoard);	//we changed the turns so now we also checking the opponent's king
					}
				}
				else if (mainBoard->gameMode==2){
					printBoard(mainBoard);
					resetBool = mainGameFlow(mainBoard);	//we changed the turns so now we also checking the opponent's king
				}
			}
		}
	}
	return 0;
}
