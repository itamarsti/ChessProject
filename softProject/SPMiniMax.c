#include <limits.h>
#include "SPMiniMax.h"
#include <stdlib.h>
#include <stdio.h>
#include "SPMiniMaxNode.h"
#include "boardFuncs.h"
#include "gameCommands.h"
#include <assert.h>

/*
 */
/*
int spAlphaBetaSuggestMove(boardGame* board,unsigned int maxDepth){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	int maxCompare = INT_MIN;
	int minCompare = INT_MAX;
	if (maxDepth<=0) return -1; 		// check this
    else{
        int WinnerIndex = -1;
        int winnerScore;
        boardGame* copy = copyBoard(board);
        assert(copy!=NULL); assert(copy->boardArr!=NULL);
        assert(copy->history!=NULL); assert(copy->history->elements!=NULL);
        //gameCopy->simulate = true;
        bool maxPlayer = false;
        int player = board->curPlayer;
        if(copy->curPlayer==0) maxPlayer=true;
        for(int i=0;i<ROW;i++){
        	for(int j=0; j<COL;j++){
        		if((player==1 && !isWhitePlayer(board->boardArr[i][j]))||
				   (player==0 && !isBlackPlayer(board->boardArr[i][j]))||
				   board->boardArr[i][j]==UNDERSCORE) continue;
        	}
            if (spFiarGameIsValidMove(gameCopy,i)){
                spFiarGameSetMove(gameCopy,i);
                char win = spFiarCheckWinner(gameCopy);
                if (win == SP_FIAR_GAME_PLAYER_1_SYMBOL || win == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    spFiarGameUndoPrevMove(gameCopy);
                    spFiarGameDestroy(gameCopy);
                    return i;
                }
                if(maxPlayer){
                    winnerScore = recursiveFunc(gameCopy,!maxPlayer, maxDepth -1);
                    if(winnerScore==INT_MAX) return i;
                    if(winnerScore>maxCompare){
                        maxCompare=winnerScore;
                        WinnerIndex = i;
                    }
                }
                else if (!maxPlayer){
                    winnerScore = recursiveFunc(gameCopy,!maxPlayer, maxDepth -1);
                    if(winnerScore==INT_MIN) return i;
                    if(winnerScore<minCompare){
                        minCompare=winnerScore;
                        WinnerIndex = i;

                    }
                }
                spFiarGameUndoPrevMove(gameCopy);
            }
        }
        spFiarGameDestroy(gameCopy);
        return WinnerIndex;				//do not forget to return in 1-base
    }
}
*/
