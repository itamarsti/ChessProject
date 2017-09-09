/*
 * alphaBetaMinMax.c
 *
 *  Created on: 10 בספט׳ 2017
 *      Author: Itamar
 */

#include <limits.h>
#include "SPMiniMaxNode.h"
#include "boardFuncs.h"
#include "gameCommands.h"
#include "moveOps.h"
#include <stdbool.h>
#include <assert.h>



int recursiveFunc(boardGame* board ,bool minmax,unsigned int depth, int recScore){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	int minWinner = INT_MAX;
	int maxWinner = INT_MIN;
	if (depth==0)return score(board);
    else{
        int scoreWinner;
        int player = board->curPlayer;
        //bool edge = true;			//is there an edge?!
        for(int i=0;i<ROW;i++){
        	for (int j=0;j<COL;j++){
        		if((player==1 && !isWhitePlayer(board->boardArr[i][j]))||
				   (player==0 && !isBlackPlayer(board->boardArr[i][j]))||
				   board->boardArr[i][j]==UNDERSCORE) continue;
        		for(int k=0;k<ROW;k++){
        			for (int l=0; l<COL;l++){
        				if(moveObj(board, RowColToNum(i,j), RowColToNum(k,l),false)){
        					if(isWinner(board)){
        						if(minmax==true){
        							undo(board,false,true);
        							return INT_MAX;
        						}
        						else if (minmax==false){
        							undo(board,false,true);
									return INT_MIN;
        						}
        					}
        					else if(minmax==true){
        						scoreWinner = recursiveFunc(board, !minmax, depth-1,maxWinner);
        						if(scoreWinner>maxWinner){
									maxWinner = scoreWinner;
								}
        						if(scoreWinner>=recScore){
									undo(board,false,true);
									return scoreWinner;
								}
        					}
        					else if(minmax==false){
        						scoreWinner = recursiveFunc(board, !minmax, depth-1,minWinner);
        						if(scoreWinner<minWinner){
									minWinner = scoreWinner ;
								}
        						if(scoreWinner<=recScore){
                					undo(board,false,true);
                					return scoreWinner;
        						}
        					}
        					undo(board,false,true);
        				}
        			}
        		}
        	}
        }
	if(minmax) return maxWinner;
	else return minWinner;
    }
}


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



int* AlphaBetaMove(boardGame* board,unsigned int maxDepth){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	bool minmax = true;
	int maxCompare = INT_MIN;
	int minCompare = INT_MAX;
    int* arrMoves = (int*) malloc(sizeof(int)*2);	//alocating place size of 2 ints
	if (maxDepth<=0){
		arrMoves[0] =-1; arrMoves[1]= -1;
		return arrMoves; 		// check this
	}
	else{
        int WinnerIndex = -1;
        int winnerScore;
        boardGame* copy = copyBoard(board);
        assert(copy!=NULL); assert(copy->boardArr!=NULL);
        assert(copy->history!=NULL); assert(copy->history->elements!=NULL);
        //gameCopy->simulate = true;
        // bool maxPlayer = false;
        int player = board->curPlayer;
        //if(copy->curPlayer==0) maxPlayer=true;
        for(int i=0;i<ROW;i++){
        	for(int j=0; j<COL;j++){
        		if((player==1 && !isWhitePlayer(board->boardArr[i][j]))||
				   (player==0 && !isBlackPlayer(board->boardArr[i][j]))||
				   board->boardArr[i][j]==UNDERSCORE) continue;
        		for (int k=0;k<ROW;k++){
        			for(int l=0;l<COL;l++){
        				if(moveObj(copy,RowColToNum(i,j),RowColToNum(k,l),false)){
        					if(isWinner(board)){
        						undo(copy,false,true);
        						destroyBoard(copy);
        						arrMoves[0] = RowColToNum(i,j);
        						arrMoves[1] = RowColToNum(k,l);
        						return arrMoves;
        					}
        					else if(player==0){
        						winnerScore = recursiveFunc(board , !minmax, maxDepth-1, maxCompare);
        						if (winnerScore == INT_MAX){
            						destroyBoard(copy);
            						arrMoves[0] = RowColToNum(i,j);
									arrMoves[1] = RowColToNum(k,l);
									return arrMoves;
        						}
)
        					}
        				}
        			}
        		}
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


