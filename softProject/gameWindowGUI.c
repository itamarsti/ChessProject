/*
 * gameWindowGUI.c
 *
 *  Created on: 14 בספט׳ 2017
 *      Author: Itamar
 */

#include "gameWindowGUI.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void createGR(GameWindow* gw, bool undoBool, bool restartBool, bool saveBool
		, bool loadBool, bool mmBool, bool quitBool){
	assert(gw!=NULL); assert(gw->window!=NULL);
	SDL_Surface* surface = NULL;


	//printf("creating game renderer\n");
	// creating the game Window renderer
	if(gw->renderer!=NULL) SDL_DestroyRenderer(gw->renderer);
	gw->renderer = SDL_CreateRenderer(gw->window, -1, SDL_RENDERER_ACCELERATED);
	if (gw->renderer==NULL) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return ;
	}

	//Creating a background texture:
	surface= SDL_LoadBMP("./utilities/gameWindow/gameBackground4.bmp");
	if (surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	gw->bg = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->bg==NULL){
		printf("Could not create a backGrouns: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);
	//printf("creating game bg\n");
/*
	//Creating a chessBoard texture:
	surface= SDL_LoadBMP("./utilities/gameWindow/chessBoard2.bmp");
	if (surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	gw->cb = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->cb==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);
	//printf("creating game cb\n");
*/
	//Creating a undo texture:

	if(!undoBool) surface = SDL_LoadBMP("./utilities/gameWindow/undo.bmp");
	else if(undoBool) surface = SDL_LoadBMP("./utilities/gameWindow/undoClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->undo = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->undo==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);
	//printf("creating game undo\n");

	//Creating a restart texture:
	if(!restartBool)surface = SDL_LoadBMP("./utilities/gameWindow/restart.bmp");
	else if(restartBool)surface = SDL_LoadBMP("./utilities/gameWindow/restartClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->restart = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->restart==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//printf("creating game restart\n");

	//Creating a saveGame texture:

	if(!saveBool)surface = SDL_LoadBMP("./utilities/gameWindow/save.bmp");
	else if(saveBool)surface = SDL_LoadBMP("./utilities/gameWindow/saveClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->saveGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->saveGame==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//printf("creating game save\n");

	//Creating a Load Game texture:

	if(!loadBool) surface = SDL_LoadBMP("./utilities/gameWindow/load.bmp");
	else if(loadBool) surface = SDL_LoadBMP("./utilities/gameWindow/loadClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->loadGame = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->loadGame==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//printf("creating game load\n");

	//Creating a mainMenu texture:
	if(!mmBool) surface = SDL_LoadBMP("./utilities/gameWindow/mainMenu.bmp");
	else if(mmBool) surface = SDL_LoadBMP("./utilities/gameWindow/mainMenuClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->mainMenu = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->mainMenu==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);
	//printf("creating game mainmenu\n");

	//Creating a Quit texture:

	if(!quitBool) surface = SDL_LoadBMP("./utilities/gameWindow/quit.bmp");
	else if(quitBool) surface = SDL_LoadBMP("./utilities/gameWindow/quitClicked.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->quit = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->quit==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);
	//printf("creating game renderer\n");
	//printf("got till end GR\n");

	//Creating a blackKnight texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackKnight60.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackKnight = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackKnight==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a blackPawn texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackPawn60.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackPawn = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackPawn==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a blackBishop texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackBishop60.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackBishop = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackBishop==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);


	//Creating a blackRook texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackRook60.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackRook = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackRook==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a blackKing texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackKing60.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackKing = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackKing==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a blackQueen texture:

	surface = SDL_LoadBMP("./utilities/gameWindow/blackQueen60.bmp");
	if(surface==NULL){
		printf("Could not create a surface: %s\n", SDL_GetError());
		return;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
	gw->blackQueen = SDL_CreateTextureFromSurface(gw->renderer, surface);
	if (gw->blackQueen==NULL){
		printf("Could not create a texture: %s\n", SDL_GetError());
		destroyGameWindow(gw);
		return;
	}
	SDL_FreeSurface(surface);

	//Creating a whiteKnight texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteKnight60.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteKnight = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteKnight==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);


		//Creating a whitePawn texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whitePawn60.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whitePawn = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whitePawn==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);

		//Creating a whiteBishop texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteBishop60.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteBishop = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteBishop==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);


		//Creating a whiteRook texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteRook60.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteRook = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteRook==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);

		//Creating whiteKing texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteKing60.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteKing = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteKing==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);

		//Creating a whiteQueen texture:

		surface = SDL_LoadBMP("./utilities/gameWindow/whiteQueen60.bmp");
		if(surface==NULL){
			printf("Could not create a surface: %s\n", SDL_GetError());
			return;
		}
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255,0,255));
		gw->whiteQueen = SDL_CreateTextureFromSurface(gw->renderer, surface);
		if (gw->whiteQueen==NULL){
			printf("Could not create a texture: %s\n", SDL_GetError());
			destroyGameWindow(gw);
			return;
		}
		SDL_FreeSurface(surface);
}

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


	createGR(gw,false,false,false,false,false,false);
	return gw;
}

void drawGameWindow(GameWindow* gw, boardGame* board, char objPos, int xGap, int yGap){
	assert(board!=NULL); assert(board->boardArr!=NULL); assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	//printf("inside draw\n");

	if(gw==NULL){
		printf("gw is NULL");
		return;
	}
	assert(gw->window!=NULL); assert(gw->renderer!=NULL);
	SDL_Rect rec = { .x = 0, .y = 0, .w = 1000, .h = 650 };
	SDL_SetRenderDrawColor(gw->renderer, 255, 255, 255, 255);
	SDL_RenderClear(gw->renderer);
	SDL_RenderCopy(gw->renderer, gw->bg, NULL, &rec);
	//rec.x = 350; rec.y = 25; rec.w = 600;rec.h = 600;	//chessBoard message
	//SDL_RenderCopy(gw->renderer,gw->cb,NULL,&rec);

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
				if (objPos==BlackPawn){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->blackPawn,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackRook){
				if (objPos==BlackRook){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//BlackRook
				SDL_RenderCopy(gw->renderer,gw->blackRook,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackBishop){
				if (objPos==BlackBishop){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//BlackBishop
				SDL_RenderCopy(gw->renderer,gw->blackBishop,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackKnight){
				if (objPos==BlackKnight){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//BlackKnight
				SDL_RenderCopy(gw->renderer,gw->blackKnight,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackKing){
				if (objPos==BlackKing){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//BlackKing
				SDL_RenderCopy(gw->renderer,gw->blackKing,NULL,&rec);
			}
			else if(board->boardArr[i][j]==BlackQueen){
				if (objPos==BlackQueen){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->blackQueen,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhitePawn){
				if (objPos==WhitePawn){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whitePawn,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteRook){
				if (objPos==WhiteRook){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteRook,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteBishop){
				if (objPos==WhiteBishop){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteBishop,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteKnight){
				if (objPos==WhiteKnight){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteKnight,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteQueen){
				if (objPos==WhiteQueen){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteQueen,NULL,&rec);
			}
			else if(board->boardArr[i][j]==WhiteKing){
				if (objPos==WhiteKing){
					rec.x = (390 + j*69+xGap); rec.y = (52 + i*69+yGap); rec.w = 60 ;rec.h = 60;	//black pawn
				}
				else rec.x = (390 + j*69); rec.y = (52 + i*69); rec.w = 60 ;rec.h = 60;	//black pawn
				SDL_RenderCopy(gw->renderer,gw->whiteKing,NULL,&rec);
			}
		}
	}


	SDL_RenderPresent(gw->renderer);
	//printf("got till end of draw\n");
}


void destroyGameWindow(GameWindow* gw){
	if (gw==NULL) return;
	if (gw->window != NULL) SDL_DestroyWindow(gw->window);
	if (gw->renderer!=NULL) SDL_DestroyRenderer(gw->renderer);
	if (gw->loadGame!=NULL) SDL_DestroyTexture(gw->loadGame);
	if (gw->saveGame!=NULL) SDL_DestroyTexture(gw->saveGame);
	if (gw->restart!=NULL) SDL_DestroyTexture(gw->restart);
	if (gw->undo!=NULL) SDL_DestroyTexture(gw->undo);
	if (gw->mainMenu!=NULL) SDL_DestroyTexture(gw->mainMenu);
	if (gw->quit!=NULL)	SDL_DestroyTexture(gw->quit);
	if (gw->bg!=NULL) SDL_DestroyTexture(gw->bg);
	if (gw->cb!=NULL) SDL_DestroyTexture(gw->cb);
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
	free(gw);
}

void destroyGameRenderer(GameWindow* gw){
	if (gw==NULL) return;
	if (gw->window == NULL) return;
	if (gw->renderer!=NULL) SDL_DestroyRenderer(gw->renderer);
	if (gw->loadGame!=NULL) SDL_DestroyTexture(gw->loadGame);
	if (gw->saveGame!=NULL) SDL_DestroyTexture(gw->saveGame);
	if (gw->restart!=NULL) SDL_DestroyTexture(gw->restart);
	if (gw->undo!=NULL) SDL_DestroyTexture(gw->undo);
	if (gw->mainMenu!=NULL) SDL_DestroyTexture(gw->mainMenu);
	if (gw->quit!=NULL)	SDL_DestroyTexture(gw->quit);
	if (gw->bg!=NULL) SDL_DestroyTexture(gw->bg);
	if (gw->cb!=NULL) SDL_DestroyTexture(gw->cb);
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
				if(pos!=-1){
					return GAME_WINDOW_DRAG_OBJ;
				}
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
			if(isClickOnSaveGame(event->motion.x, event->motion.y)){
				return GAME_WINDOW_HOVER_SAVE_GAME;
			 }
			 else if(isClickOnLoadGameWindow(event->motion.x, event->motion.y)){
				 return GAME_WINDOW_HOVER_LOAD_GAME;
			 }
			 else if(isClickOnQuitGameWindow(event->motion.x, event->motion.y)){
				 return  GAME_WINDOW_HOVER_EVENT_QUIT;
			 }
			 else if(isClickOnRestart(event->motion.x, event->motion.y)){
				 return  GAME_WINDOW_HOVER_RESTART_GAME;
			 }
			 else if(isClickOnUndo(event->motion.x, event->motion.y)){
				 return  GAME_WINDOW_HOVER_UNDO;
			 }
			 else if(isClickOnMainMenu(event->motion.x, event->motion.y)){
				 return  GAME_WINDOW_HOVER_MAIN_MENU;
			 }
			 else if(isPixToPos(event->motion.x, event->motion.y)){
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


bool isClickOnUndo(int x, int y){
	if((x>=60 && x<=260)&& (y>=60&&y<=120)) return true;
	return false;
}

bool isClickOnRestart(int x, int y){
	if((x>=60 && x<=260)&& (y>=150&&y<=210)) return true;
	return false;
}

bool isClickOnSaveGame(int x, int y){
	if((x>=60 && x<=260)&& (y>=240&&y<=300)) return true;
	return false;
}

bool isClickOnLoadGameWindow(int x, int y){
	if((x>=60 && x<=260)&& (y>=330&&y<=390)) return true;
	return false;
}
bool isClickOnMainMenu(int x, int y){
	if((x>=60 && x<=260)&& (y>=420&&y<=480)) return true;
	return false;
}

bool isClickOnQuitGameWindow(int x, int y){
	if((x>=60 && x<=260)&& (y>=510&&y<=570)) return true;
	return false;
}


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


void gameWindowHide(GameWindow* gw){
	SDL_HideWindow(gw->window);
}

void gameWindowShow(GameWindow* gw){
	SDL_ShowWindow(gw->window);
}


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

int fromPixToPos(int x, int y){
	if((x>=386 && x<930) && (y>=50 && y<594)){
		int col = (x-386)/68;
		int row = (y-50)/68;
		int pos = RowColToNum(row,col);
		return pos;
	}
	return -1;
}

bool isPixToPos(int x, int y){
	if((x>=386 && x<930) && (y>=50 && y<594))return true;
	return false;
}
