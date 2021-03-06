/*
 * gameWindowGUI.c
 *
 *  Created on: 14 ����� 2017
 *      Author: Itamar
 */

/**
 * GamwWindow summary:
 *
 * The Settings Window GUI sections. This functions are responsible for creating
 * the Settings window Data structure, handling the different events in this window etc.
 *
 *
 *
 * destroyGameRenderer				- Destroying only the renderer and textures
 * destroyGameWindow				- Destroying the GameWindow Structure
 * createGW							- Creating the GamwWindow structure
 * createGR							- Creating the Renderer and the textures
 * isClickOnSaveGame				- Checking if there was click on Save button
 * isClickOnLoadGameWindow			- Checking if there was click on Load button
 * isClickOnQuitGameWindow			- Checking if there was click on Quit button
 * isClickOnRestart					- Checking if there was click on Restart button
 * isClickOnUndo					- Checking if there was click on Undo button
 * isClickOnMainMenu				- Checking if there was click on MainMenu button
 * gameWindowHandleEvent			- Classifying different events in Game window
 * drawGameWindow					- Drawing the SettingsWindow
 * createGameLoadTexture			- Creating and Destroying the Load Texture (light/not light)
 * createGameUndoTexture			- Creating and Destroying the Undo Texture (light/not light)
 * createGameSaveTexture			- Creating and Destroying the Mode2 Texture (light/not light)
 * gameWindowHide					- Hiding the Window
 * gameWindowShow					- Showing the Window
 * drawGameWindowImproved			- Drawing the SettingsWindow supporting drag and drop
 * saveGameFromGUI					- Saving the Game into a local File
 * saveGameMessageBox				- Message box in case the user didn't save the game
 * fromPixToPos						- Converting from pixel in GUI to position in Board Game
 * isPixToPos						- Checking if the event has happened in the chess boundaries
 *
 *
 *
 *
 *
 */


#include "gameWindowGUI.h"
#include "gameParser.h"
#include "boardFuncs.h"
#include "gameCommands.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SQUARE 69
#define WIDTH 390
#define HEIGHT 52


/**
 *
 * Creating the GameWindow Renderer and textures using SDL.
 * In this part we create only renderer and buttons.
 *
 * @param gw - GameWindow Data structure
 * @param undoBool - if to light undo
 * @param loadBool - if to light load
 *
 * @return
 * void
 *
 */


void createGR(GameWindow* gw, bool undoBool, bool loadBool){
	assert(gw!=NULL); assert(gw->window!=NULL);
	SDL_Surface* surface = NULL;

	// creating the game Window renderer
	gw->renderer = SDL_CreateRenderer(gw->window, -1, SDL_RENDERER_ACCELERATED);
	if (gw->renderer==NULL) {
		printf("Could not create a renderer in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return ;
	}

	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/gameWindow/gameBackgrounFinal.bmp");
	if (surface==NULL){
		printf("Could not create a background surface in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	gw->bg = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->bg==NULL){
		printf("Could not create a backGround texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating an undo texture:
	if(!undoBool) surface = SDL_LoadBMP("./utilities/gameWindow/undo.bmp");
	else if(undoBool) surface = SDL_LoadBMP("./utilities/gameWindow/undoClicked.bmp");
	if(surface==NULL){
		printf("Could not create a undo surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->undo = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->undo==NULL){
		printf("Could not create a undo texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a restart texture:
	surface = SDL_LoadBMP("./utilities/gameWindow/restartClicked.bmp");
	if(surface==NULL){
		printf("Could not create a restart surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->restart = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->restart==NULL){
		printf("Could not create a restart texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a saveGame texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/save.bmp");
	if(surface==NULL){
		printf("Could not create a save surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->saveGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->saveGame==NULL){
		printf("Could not create a save texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a Load Game texture:

	if(!loadBool) surface = SDL_LoadBMP("./utilities/gameWindow/load.bmp");
	else if(loadBool) surface = SDL_LoadBMP("./utilities/gameWindow/loadclicked.bmp");
	if(surface==NULL){
		printf("Could not create a load surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->loadGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->loadGame==NULL){
		printf("Could not create a load texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a mainMenu texture:
	surface = SDL_LoadBMP("./utilities/gameWindow/mainMenuClicked.bmp");
	if(surface==NULL){
		printf("Could not create a mainMenu surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->mainMenu = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->mainMenu==NULL){
		printf("Could not create a mainMenu texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a Quit texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/quitClicked.bmp");
	if(surface==NULL){
		printf("Could not create a quit surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->quit = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->quit==NULL){
		printf("Could not create a quit texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a blackKnight texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackKnight60.bmp");
	if(surface==NULL){
		printf("Could not create a  blackNight surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackKnight = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackKnight==NULL){
		printf("Could not create a blackNight texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a blackPawn texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackPawn60.bmp");
	if(surface==NULL){
		printf("Could not create a blackPawn surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackPawn = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackPawn==NULL){
		printf("Could not create a blackPawn texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a blackBishop texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackBishop60.bmp");
	if(surface==NULL){
		printf("Could not create a blackBishop surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackBishop = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackBishop==NULL){
		printf("Could not create a blackBoshop texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a blackRook texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackRook60.bmp");
	if(surface==NULL){
		printf("Could not create a blackRook surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackRook = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackRook==NULL){
		printf("Could not create a blackRook texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a blackKing texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackKing60.bmp");
	if(surface==NULL){
		printf("Could not create a blackKing surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackKing = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackKing==NULL){
		printf("Could not create a blackKing texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a blackQueen texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackQueen60.bmp");
	if(surface==NULL){
		printf("Could not create a blackQueen surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackQueen = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackQueen==NULL){
		printf("Could not create a blackQueen texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a whiteKnight texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteKnight60.bmp");
		if(surface==NULL){
			printf("Could not create a whiteKnight surface in GameWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteKnight = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteKnight==NULL){
			printf("Could not create a whiteKnight texture in GameWindow: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);


		//Creating a whitePawn texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whitePawn60.bmp");
		if(surface==NULL){
			printf("Could not create a whitePawn surface in GameWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whitePawn = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whitePawn==NULL){
			printf("Could not create a whitePawn texture in GameWindow: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);

		//Creating a whiteBishop texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteBishop60.bmp");
		if(surface==NULL){
			printf("Could not create a whiteBishop surface in GameWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteBishop = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteBishop==NULL){
			printf("Could not create a whiteBishop texture in GameWindow: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);


		//Creating a whiteRook texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteRook60.bmp");
		if(surface==NULL){
			printf("Could not create a whiteRook surface in GameWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteRook = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteRook==NULL){
			printf("Could not create a whiteRook texture in GameWindow: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);

		//Creating whiteKing texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteKing60.bmp");
		if(surface==NULL){
			printf("Could not create a whiteKing surface in GameWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteKing = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteKing==NULL){
			printf("Could not create a whiteKing texture in GameWindow: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);

		//Creating a whiteQueen texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteQueen60.bmp");
		if(surface==NULL){
			printf("Could not create a whiteQueen surface in GameWindow: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteQueen = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteQueen==NULL){
			printf("Could not create a whiteQueen texture in GameWindow: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);
}


/**
 *
 * Creating the GameWindow structure using SDL.
 * In this part we create a window, renderer and buttons.
 *
 * @return
 * GameWindow pointer of the data Structure
 *
 */

GameWindow* createGW(){
	GameWindow* gw = (GameWindow*) malloc(sizeof(GameWindow));
	if(gw==NULL){
		printf("Couldn't create GameMainWindow struct\n");
		return NULL ;
	}
	// creating the game Window Object
	gw->window = (SDL_Window*) SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1000, 650, SDL_WINDOW_OPENGL);
	if (gw->window==NULL){
		printf("Could not create window: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return NULL ;
	}
	int load = numOfFilesInDir();
	if(load==0) createGR(gw,false,false);
	else if(load!=0) createGR(gw,false,true);
	return gw;
}


/**
 *
 * Drawing the window and presents it to the user.
 *
 * @param gw - Game Window data structure
 * @param board - BoardGame Data Structure
 * @return
 * void
 *
 */


void drawGameWindow(GameWindow* gw, boardGame* board){
	assert(board!=NULL); assert(board->boardArr!=NULL); assert(board->history!=NULL);
	assert(board->history->elements!=NULL);

	if(gw==NULL){
		printf("Error: GameWindow is NULL\n");
		return;
	}
	assert(gw->window!=NULL); assert(gw->renderer!=NULL);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_SetRenderDrawColor(gw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(gw->renderer);
	SDL_RenderCopy(gw->renderer, gw->bg, NULL, &rec);
	rec.x = 60; rec.y = 60; rec.w = 200;rec.h = 60;	//undo message
	SDL_RenderCopy(gw->renderer,gw->undo,NULL,&rec);
	rec.x = 60; rec.y = 150; rec.w = 200;rec.h = 60;	//restart message
	SDL_RenderCopy(gw->renderer,gw->restart,NULL,&rec);
	rec.x = 60; rec.y = 240; rec.w = 200;rec.h = 60;	//save message
	SDL_RenderCopy(gw->renderer,gw->saveGame,NULL,&rec);
	rec.x = 60; rec.y = 330; rec.w = 200;rec.h = 60;	//load message
	SDL_RenderCopy(gw->renderer,gw->loadGame,NULL,&rec);
	rec.x = 60; rec.y = 420; rec.w = 200;rec.h = 60;	//mainMenu message
	SDL_RenderCopy(gw->renderer,gw->mainMenu,NULL,&rec);
	rec.x = 60; rec.y = 510; rec.w = 200;rec.h = 60;	//quit message
	SDL_RenderCopy(gw->renderer,gw->quit,NULL,&rec);
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			if(board->boardArr[i][j]==BlackPawn){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->blackPawn,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackRook){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//BlackRook
				SDL_RenderCopy(gw->renderer,gw->blackRook,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackBishop){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//BlackBishop
				SDL_RenderCopy(gw->renderer,gw->blackBishop,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackKnight){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//BlackKnight
				SDL_RenderCopy(gw->renderer,gw->blackKnight,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackKing){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//BlackKing
				SDL_RenderCopy(gw->renderer,gw->blackKing,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackQueen){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->blackQueen,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhitePawn){
				 rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whitePawn,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteRook){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteRook,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteBishop){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteBishop,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteKnight){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteKnight,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteQueen){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteQueen,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteKing){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteKing,NULL,&rec);
			}
		}
	}
	SDL_RenderPresent(gw->renderer);
}


/**
 *
 * Destroying the GameWindow data structure with it's elements and free the memory.
 *
 * @param gw - Game Window data structure
 *
 * @return
 * void
 *
 */



void destroyGameWindow(GameWindow* gw){
	if (gw==NULL) return;
	if (gw->saveGame!=NULL) SDL_DestroyTexture(gw->saveGame);
	if (gw->loadGame!=NULL) SDL_DestroyTexture(gw->loadGame);
	if (gw->restart!=NULL) SDL_DestroyTexture(gw->restart);
	if (gw->undo!=NULL) SDL_DestroyTexture(gw->undo);
	if (gw->mainMenu!=NULL) SDL_DestroyTexture(gw->mainMenu);
	if (gw->quit!=NULL)	SDL_DestroyTexture(gw->quit);
	if(gw->blackPawn!=NULL) SDL_DestroyTexture(gw->blackPawn);
	if(gw->blackRook!=NULL) SDL_DestroyTexture(gw->blackRook);
	if(gw->blackKnight!=NULL) SDL_DestroyTexture(gw->blackKnight);
	if(gw->blackBishop!=NULL) SDL_DestroyTexture(gw->blackBishop);
	if(gw->blackQueen!=NULL) SDL_DestroyTexture(gw->blackQueen);
	if(gw->blackKing!=NULL) SDL_DestroyTexture(gw->blackKing);
	if(gw->whitePawn!=NULL) SDL_DestroyTexture(gw->whitePawn);
	if(gw->whiteRook!=NULL) SDL_DestroyTexture(gw->whiteRook);
	if(gw->whiteBishop!=NULL) SDL_DestroyTexture(gw->whiteBishop);
	if(gw->whiteKnight!=NULL) SDL_DestroyTexture(gw->whiteKnight);
	if(gw->whiteQueen!=NULL) SDL_DestroyTexture(gw->whiteQueen);
	if(gw->whiteKing!=NULL) SDL_DestroyTexture(gw->whiteKing);
	if (gw->bg!=NULL) SDL_DestroyTexture(gw->bg);
	if (gw->renderer!=NULL) SDL_DestroyRenderer(gw->renderer);
	if (gw->window != NULL) SDL_DestroyWindow(gw->window);
	free(gw);
}


/**
 *
 * Destroying the GameWindow renderer and textures.
 *
 * @param gw - Game Window data structure
 *
 * @return
 * void
 *
 */

void destroyGameRenderer(GameWindow* gw){
	if (gw==NULL) return;
	if (gw->window == NULL) return;
	if (gw==NULL) return;
	if (gw->saveGame!=NULL) SDL_DestroyTexture(gw->saveGame);
	if (gw->loadGame!=NULL) SDL_DestroyTexture(gw->loadGame);
	if (gw->restart!=NULL) SDL_DestroyTexture(gw->restart);
	if (gw->undo!=NULL) SDL_DestroyTexture(gw->undo);
	if (gw->mainMenu!=NULL) SDL_DestroyTexture(gw->mainMenu);
	if (gw->quit!=NULL)	SDL_DestroyTexture(gw->quit);
	if(gw->blackPawn!=NULL) SDL_DestroyTexture(gw->blackPawn);
	if(gw->blackRook!=NULL) SDL_DestroyTexture(gw->blackRook);
	if(gw->blackKnight!=NULL) SDL_DestroyTexture(gw->blackKnight);
	if(gw->blackBishop!=NULL) SDL_DestroyTexture(gw->blackBishop);
	if(gw->blackQueen!=NULL) SDL_DestroyTexture(gw->blackQueen);
	if(gw->blackKing!=NULL) SDL_DestroyTexture(gw->blackKing);
	if(gw->whitePawn!=NULL) SDL_DestroyTexture(gw->whitePawn);
	if(gw->whiteRook!=NULL) SDL_DestroyTexture(gw->whiteRook);
	if(gw->whiteBishop!=NULL) SDL_DestroyTexture(gw->whiteBishop);
	if(gw->whiteKnight!=NULL) SDL_DestroyTexture(gw->whiteKnight);
	if(gw->whiteQueen!=NULL) SDL_DestroyTexture(gw->whiteQueen);
	if(gw->whiteKing!=NULL) SDL_DestroyTexture(gw->whiteKing);
	if (gw->bg!=NULL) SDL_DestroyTexture(gw->bg);
	if (gw->renderer!=NULL) SDL_DestroyRenderer(gw->renderer);
}




GAME_WINDOW_EVENT gameWindowHandleEvent(GameWindow* gw, SDL_Event* event){
	int pos = 0;
	if (event == NULL || gw == NULL ) {
		return GAME_WINDOW_INVALID;
	}
	switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:
			if(event->button.button ==SDL_BUTTON_LEFT){
				pos = fromPixToPos(event->button.x, event->button.y);
				if(pos!=-1)	return GAME_WINDOW_DRAG_OBJ;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if(fromPixToPos(event->button.x, event->button.y)!=-1){
				return GAME_WINDOW_PUSH_OBJ;
			 }
			 else if(isClickOnSaveGame(event->button.x, event->button.y)){
				 return GAME_WINDOW_PUSH_SAVE_GAME;
			 }
			 else if(isClickOnLoadGameWindow(event->button.x, event->button.y)){
				 return GAME_WINDOW_PUSH_LOAD_GAME;
			 }
			 else if(isClickOnQuitGameWindow(event->button.x, event->button.y)){
				 return  GAME_WINDOW_PUSH_EVENT_QUIT;
			 }
			 else if(isClickOnRestart(event->button.x, event->button.y)){
				 return  GAME_WINDOW_PUSH_RESTART_GAME;
			 }
			 else if(isClickOnUndo(event->button.x, event->button.y)){
				 return  GAME_WINDOW_PUSH_UNDO;
			 }
			 else if(isClickOnMainMenu(event->button.x, event->button.y)){
				 return  GAME_WINDOW_PUSH_MAIN_MENU;
			 }
			 else if(event->button.button ==SDL_BUTTON_LEFT){
				if(isPixToPos(event->button.x, event->button.y)){
					return GAME_WINDOW_PUSH_OBJ;
				}
			}
			break;
		case SDL_MOUSEMOTION:
			 if(isPixToPos(event->motion.x, event->motion.y)){
				 return GAME_WINDOW_HOVER_OBJ;
			 }
			 break;
		case SDL_WINDOWEVENT:
			if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
				return GAME_WINDOW_PUSH_EVENT_QUIT;
			}
			break;
		default:
			return GAME_WINDOW_EVENT_NONE;
		}
	return GAME_WINDOW_EVENT_NONE;
}

/**
 *
 * This function checks if there was an event in the boundaries of the Undo Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the Undo Button boundaries, false otherwise.
 *
 */


bool isClickOnUndo(int x, int y){
	if((x>=60 && x<=260)&& (y>=60&&y<=120)) return true;
	return false;
}


/**
 *
 * This function checks if there was an event in the boundaries of the Restart Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the Restart Button boundaries, false otherwise.
 *
 */


bool isClickOnRestart(int x, int y){
	if((x>=60 && x<=260)&& (y>=150&&y<=210)) return true;
	return false;
}


/**
 *
 * This function checks if there was an event in the boundaries of the SaveGame Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the SaveGame Button boundaries, false otherwise.
 *
 */


bool isClickOnSaveGame(int x, int y){
	if((x>=60 && x<=260)&& (y>=240&&y<=300)) return true;
	return false;
}


/**
 *
 * This function checks if there was an event in the boundaries of the LoadGame Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the LoadGame Button boundaries, false otherwise.
 *
 */


bool isClickOnLoadGameWindow(int x, int y){
	if((x>=60 && x<=260)&& (y>=330&&y<=WIDTH)) return true;
	return false;
}

/**
 *
 * This function checks if there was an event in the boundaries of the MainMenu Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the MainMenu Button boundaries, false otherwise.
 *
 */


bool isClickOnMainMenu(int x, int y){
	if((x>=60 && x<=260)&& (y>=420&&y<=480)) return true;
	return false;
}


/**
 *
 * This function checks if there was an event in the boundaries of the QuitGame Button
 *
 * @param x - horizontal coordinate (the x axe of a pixel in the window)
 * @param y - vertical coordinate (the y axe of a pixel in the window)
 *
 * @return
 * true if the coordinates were in the QuitGame Button boundaries, false otherwise.
 *
 */


bool isClickOnQuitGameWindow(int x, int y){
	if((x>=60 && x<=260)&& (y>=510&&y<=570)) return true;
	return false;
}


/**
 *
 * This function is Saving the game to a local directory and manipulating the files
 * such that there will be at maximum 5 saves sorted by file created time.
 *
 * @param gw - GameWindow data structure
 * @param numOfFiles - number of saves that are already exists
 * @return
 * void
 *
 */

void saveGameFromGUI(boardGame* game, int numOfFiles){
	assert(game!=NULL); assert(game->boardArr!=NULL);
	const char* savePath = (char*) "./utilities/loadedGames/game1.xml";
	if(numOfFiles==5){
		remove("./utilities/loadedGames/game5.xml");
		rename("./utilities/loadedGames/game4.xml","./utilities/loadedGames/game5.xml");
		rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game4.xml");
		rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game3.xml");
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==4){
		rename("./utilities/loadedGames/game4.xml","./utilities/loadedGames/game5.xml");
		rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game4.xml");
		rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game3.xml");
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==3){
		rename("./utilities/loadedGames/game3.xml","./utilities/loadedGames/game4.xml");
		rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game3.xml");
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==2){
		rename("./utilities/loadedGames/game2.xml","./utilities/loadedGames/game3.xml");
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==1){
		rename("./utilities/loadedGames/game1.xml","./utilities/loadedGames/game2.xml");
		saveFile(game, savePath);
	}
	else if (numOfFiles==0){
		saveFile(game, savePath);
	}
	printf("saved the file\n");
	return;
}


/**
 *
 * This function hiding the GameWindow
 *
 * @param gw - GameWindow data structure
 *
 * @return
 * void
 *
 */

void gameWindowHide(GameWindow* gw){
	SDL_HideWindow(gw->window);
}


/**
 *
 * This function showing the GameWindow
 *
 * @param gw - GameWindow data structure
 *
 * @return
 * void
 *
 */

void gameWindowShow(GameWindow* gw){
	SDL_ShowWindow(gw->window);
}


/**
 *
 * This function is the message box asking the user if he wants to save the game.
 *
 *
 * @return
 * integer between 0-2:
 * 		0: don't save
 * 		1: save
 * 		2: cancel the message and do nothing
 *
 */

int saveGameMessageBox(){
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ 1, 1, "yes" },
		{ 2, 2, "cancel" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		"Save Messagebox", /* .title */
		"Do you want to save the current Game?", /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return -1;
	}
	if (buttonid == -1) {
		SDL_Log("no selection");
	} else {
		SDL_Log("selection was %s", buttons[buttonid].text);
	    }
	return buttonid;
}

/**
 *
 * This function translating coordinates on gameBoard GUI to a position in the Game Board
 * Data structure
 *
 * @param x - the x axe on the gameBoard
 * @param y - the y axe on the gameBoard
 * @return
 * position on GameBoard (console) - number between 0-63
 * else: -1
 *
 */

int fromPixToPos(int x, int y){
	if((x>=386 && x<930) && (y>=50 && y<594)){
		int col = (x-386)/68;
		int row = (y-50)/68;
		int pos = RowColToNum(row,col);
		return pos;
	}
	return -1;
}

/**
 *
 * This function checks coordinates on gameBoard GUI if they are belong to the gameBoard
 *
 * @param x - the x axe on the gameBoard
 * @param y - the y axe on the gameBoard
 * @return
 *
 *true if the coordinate fits to the gameBoard, false otherwise.
 *
 */

bool isPixToPos(int x, int y){
	if((x>=386 && x<930) && (y>=50 && y<594))return true;
	return false;
}


/**
 *
 * Drawing the window and presents it to the user - the improved version which supports
 * drag and drop
 *
 * @param gw - Game Window data structure
 * @param board - BoardGame Data Structure
 * @param p1 - source position
 * @param p2 - destination position
 * @return
 * void
 *
 */

void drawGameWindowImproved(GameWindow* gw, boardGame* board, SDL_Point* p1, SDL_Point* p2){
	assert(board!=NULL); assert(board->boardArr!=NULL); assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	if(gw==NULL){
		printf("ERROR: GameWindow is NULL inside drawGWimproved\n");
		return;
	}
	assert(gw->window!=NULL); assert(gw->renderer!=NULL);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_SetRenderDrawColor(gw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(gw->renderer);
	SDL_RenderCopy(gw->renderer, gw->bg, NULL, &rec);
	rec.x = 60; rec.y = 60; rec.w = 200;rec.h = 60;	//undo message
	SDL_RenderCopy(gw->renderer,gw->undo,NULL,&rec);
	rec.x = 60; rec.y = 150; rec.w = 200;rec.h = 60;	//restart message
	SDL_RenderCopy(gw->renderer,gw->restart,NULL,&rec);
	rec.x = 60; rec.y = 240; rec.w = 200;rec.h = 60;	//save message
	SDL_RenderCopy(gw->renderer,gw->saveGame,NULL,&rec);
	rec.x = 60; rec.y = 330; rec.w = 200;rec.h = 60;	//load message
	SDL_RenderCopy(gw->renderer,gw->loadGame,NULL,&rec);
	rec.x = 60; rec.y = 420; rec.w = 200;rec.h = 60;	//mainMenu message
	SDL_RenderCopy(gw->renderer,gw->mainMenu,NULL,&rec);
	rec.x = 60; rec.y = 510; rec.w = 200;rec.h = 60;	//quit message
	SDL_RenderCopy(gw->renderer,gw->quit,NULL,&rec);
	int row = NumToRow(fromPixToPos(p1->x,p1->y));
	int col = NumToCol(fromPixToPos(p1->x,p1->y));
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			if(i==row && j==col && board->boardArr[i][j]!=UNDERSCORE
					&& fromPixToPos(p1->x,p1->y)!=-1 && fromPixToPos(p2->x,p2->y)!=-1){
				rec.x = (WIDTH + j*SQUARE - p1->x + p2->x); rec.y = (HEIGHT + i*SQUARE - p1->y + p2->y); rec.w = 60 ;rec.h = 60;
				if(board->boardArr[i][j]==BlackPawn) SDL_RenderCopy(gw->renderer,gw->blackPawn,NULL,&rec);
				else if(board->boardArr[i][j]==BlackRook) SDL_RenderCopy(gw->renderer,gw->blackRook,NULL,&rec);
				else if(board->boardArr[i][j]==BlackBishop) SDL_RenderCopy(gw->renderer,gw->blackBishop,NULL,&rec);
				else if(board->boardArr[i][j]==BlackKnight) SDL_RenderCopy(gw->renderer,gw->blackKnight,NULL,&rec);
				else if(board->boardArr[i][j]==BlackKing) SDL_RenderCopy(gw->renderer,gw->blackKing,NULL,&rec);
				else if(board->boardArr[i][j]==BlackQueen) SDL_RenderCopy(gw->renderer,gw->blackQueen,NULL,&rec);
				else if(board->boardArr[i][j]==WhitePawn) SDL_RenderCopy(gw->renderer,gw->whitePawn,NULL,&rec);
				else if(board->boardArr[i][j]==WhiteRook) SDL_RenderCopy(gw->renderer,gw->whiteRook,NULL,&rec);
				else if(board->boardArr[i][j]==WhiteBishop) SDL_RenderCopy(gw->renderer,gw->whiteBishop,NULL,&rec);
				else if(board->boardArr[i][j]==WhiteKnight) SDL_RenderCopy(gw->renderer,gw->whiteKnight,NULL,&rec);
				else if(board->boardArr[i][j]==WhiteKing) SDL_RenderCopy(gw->renderer,gw->whiteKing,NULL,&rec);
				else if(board->boardArr[i][j]==WhiteQueen) SDL_RenderCopy(gw->renderer,gw->whiteQueen,NULL,&rec);
				continue;
			}
			else if(board->boardArr[i][j]==BlackPawn){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->blackPawn,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackRook){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//BlackRook
				SDL_RenderCopy(gw->renderer,gw->blackRook,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackBishop){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//BlackBishop
				SDL_RenderCopy(gw->renderer,gw->blackBishop,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackKnight){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//BlackKnight
				SDL_RenderCopy(gw->renderer,gw->blackKnight,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackKing){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//BlackKing
				SDL_RenderCopy(gw->renderer,gw->blackKing,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackQueen){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->blackQueen,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhitePawn){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whitePawn,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteRook){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteRook,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteBishop){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteBishop,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteKnight){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteKnight,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteQueen){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteQueen,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteKing){
				rec.x = (WIDTH + j*SQUARE); rec.y = (HEIGHT + i*SQUARE); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteKing,NULL,&rec);
			}
		}
	}
	SDL_RenderPresent(gw->renderer);
}

/**
 *
 * This function destroy and creates back again the "Load" Button.
 *
 * @param gw - LoadWindow data structure
 * @param loadBool - if to light the load
 *
 *
 * @return
 * void
 *
 */

void createGameLoadTexture(GameWindow* gw, bool loadBool){
	assert(gw!=NULL); assert(gw->window!=NULL); assert(gw->renderer!=NULL);
	SDL_Surface* surface = NULL;
	SDL_DestroyTexture(gw->loadGame);
	if(!loadBool) surface = SDL_LoadBMP("./utilities/gameWindow/load.bmp");
	else if(loadBool) surface = SDL_LoadBMP("./utilities/gameWindow/loadclicked.bmp");
	if(surface==NULL){
		printf("Could not create a load surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->loadGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->loadGame==NULL){
		printf("Could not create a load texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

}

/**
 *
 * This function destroy and creates back again the "Undo" Button.
 *
 * @param gw - LoadWindow data structure
 * @param undoBool - if to light the undo
 *
 *
 * @return
 * void
 *
 */


void createGameUndoTexture(GameWindow* gw, bool undoBool){
	assert(gw!=NULL); assert(gw->window!=NULL); assert(gw->renderer!=NULL);
	SDL_Surface* surface = NULL;
	SDL_DestroyTexture(gw->undo);
	if(!undoBool) surface = SDL_LoadBMP("./utilities/gameWindow/undo.bmp");
	else if(undoBool) surface = SDL_LoadBMP("./utilities/gameWindow/undoClicked.bmp");
	if(surface==NULL){
		printf("Could not create a undo surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->undo = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->undo==NULL){
		printf("Could not create a undo texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);
}

/**
 *
 * This function destroy and creates back again the "Save" Button.
 *
 * @param gw - LoadWindow data structure
 * @param saveBool - if to light the save
 *
 *
 * @return
 * void
 *
 */


void createGameSaveTexture(GameWindow* gw, bool saveBool){
	assert(gw!=NULL); assert(gw->window!=NULL); assert(gw->renderer!=NULL);
	SDL_Surface* surface = NULL;
	SDL_DestroyTexture(gw->saveGame);
	if(!saveBool)surface = SDL_LoadBMP("./utilities/gameWindow/save.bmp");
	else if(saveBool)surface = SDL_LoadBMP("./utilities/gameWindow/saveClicked.bmp");
	if(surface==NULL){
		printf("Could not create a save surface in GameWindow: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->saveGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->saveGame==NULL){
		printf("Could not create a save texture in GameWindow: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);
}

