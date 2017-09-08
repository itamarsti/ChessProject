#include <limits.h>
#include "SPMiniMaxNode.h"
#include <stdbool.h>
#define OFFSET 3

/**
int recursiveFunc(SPFiarGame* game,bool minmax,unsigned int depth){
    if (depth==0)return score(game);
    else{
        int scoreWinner;
        int minWinner =INT_MAX;
        int maxWinner = INT_MIN;
        bool edge = true;
        for(int i=0; i<SP_FIAR_GAME_N_COLUMNS;i++){				//if you don't win in your move
            if (spFiarGameIsValidMove(game,i)){
                edge = false;
                spFiarGameSetMove(game,i);
                char win = spFiarCheckWinner(game);			//winning case
                if(win == SP_FIAR_GAME_PLAYER_1_SYMBOL || win == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    if(minmax==false){				//checking for winner
                        spFiarGameUndoPrevMove(game);
                        return INT_MIN;
                    }
                    else if (minmax==true){
                        spFiarGameUndoPrevMove(game);
                        return INT_MAX;
                    }
                }
                if(minmax==false){
                    scoreWinner = recursiveFunc(game,!minmax,depth-1);
                    if(scoreWinner<minWinner){
                        minWinner=scoreWinner;
                    }
                }
                else if (minmax==true){
                    scoreWinner = recursiveFunc(game,!minmax,depth-1);
                    if(scoreWinner>maxWinner){
                        maxWinner=scoreWinner;
                    }
                }
                spFiarGameUndoPrevMove(game);
            }
        }
        if (edge) return score(game);
        if(minmax==false){return minWinner;}
        else{return maxWinner;}
    }
}

**/


int score(boardGame* board){
    assert(board!=NULL); assert(board->boardArr!=NULL);
    assert(board->history!=NULL); assert(board->history->elements!=NULL);
    int score = 0;
    char symbol;
    for(int i=0;i<ROW;i++){
    	for(int j=0;j<COL;j++){
    		symbol = board->boardArr[i][j];
    		score+=scoreFuncId(symbol);

    		}
    	}
    return score;
}


int scoreFuncId(char symbol){
	if(symbol == BlackPawn) return 1;
	else if(symbol == WhitePawn) return -1;
	else if(symbol == BlackBishop) return 3;
	else if(symbol == WhiteBishop) return -3;
	else if(symbol == BlackKnight) return 3;
	else if(symbol == WhiteKnight) return -3;
	else if(symbol == BlackRook) return 5;
	else if(symbol == WhiteRook) return -5;
	else if(symbol == BlackQueen) return 9;
	else if(symbol == WhiteQueen) return -9;
	else if(symbol == BlackKing) return 100;
	else if(symbol == WhiteKing) return -100;
	else return 0;
}
