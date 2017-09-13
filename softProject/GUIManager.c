/*
 * GUIManager.c
 *
 *  Created on: 13 בספט׳ 2017
 *      Author: Itamar
 */


#include "GUIManager.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void quitGame(Manager* manager){
	if(manager!=NULL){
		destroyManager(manager);
		SDL_Quit();
		printf("Exiting...");
		exit(0);
	}
}




//void setNumPlayers(boardGame* board, int num);

