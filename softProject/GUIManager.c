/*
 * GUIManager.c
 *
 *  Created on: 13 בספט׳ 2017
 *      Author: Itamar
 */


#include "GUIManager.h"


void quitMainWindow(Manager* manager){
	if(manager!=NULL){
		destroyManager(manager);
		SDL_Quit();
		printf("Exiting...");
		exit(0);
	}
}

