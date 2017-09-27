/*
 * chessprog.c
 *
 *  Created on: 9 ����� 2017
 *      Author: Itamar
 */

#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "chessprog.h"

int main(int argc, char* argv[]) {
    setvbuf (stdout, NULL, _IONBF, 0);
    fflush(stdout);

	bool resetBool = false;
	bool consoleBool = true;
	if(argc==1 || (argc==2 && strcmp(argv[1],"-c")==0)) consoleBool = true;
	else if(argc==2 && strcmp(argv[1],"-g")==0) consoleBool = false;
	if(!consoleBool){
		guiMain();
	}
	else if(consoleBool){
		while(1){
			//printf("before creating\n");
			boardGame* mainBoard = createBoard();
			//printf("before init\n");
			initBoard(mainBoard, true);
			//printf("before settings\n");
			mainSettingFlow(mainBoard);				//setting Function. Continues when user type "Start".
			resetBool = false;
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

		}
	}

	return 0;
}
