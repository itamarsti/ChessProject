/*
 * chessprog.c
 *
 *  Created on: 9 баев„ 2017
 *      Author: Itamar
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "boardFuncs.h"
#include "commandsFuncs.h"
#include "moveOps.h"

int main(int argc, char* argv[]) {
	boardGame* mainBoard = createBoard();
	initBoard(mainBoard);
	printBoard(mainBoard);
	moveObj(mainBoard,6,1,4,1);
	moveObj(mainBoard,7,1,5,2);
	moveObj(mainBoard,5,2,4,4);
	moveObj(mainBoard,7,2,6,1);
	moveObj(mainBoard,6,1,1,6);
	moveObj(mainBoard,7,3,7,1);
	moveObj(mainBoard,7,1,5,1);
	moveObj(mainBoard,5,1,1,5);
	moveObj(mainBoard,7,4,7,3);
	moveObj(mainBoard,7,3,7,2);
	moveObj(mainBoard,7,2,7,1);
	moveObj(mainBoard,7,1,6,1);
	moveObj(mainBoard,6,1,5,1);
	moveObj(mainBoard,5,1,4,0);














	printf("\n");
	printBoard(mainBoard);







	return 0;
}
