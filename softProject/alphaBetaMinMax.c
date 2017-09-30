/*
 * alphaBetaMinMax.c
 *
 *  Created on: 10 בספט׳ 2017
 *      Author: Itamar
 */


/**
 * alphBetaMinMax summary:
 *
 * The Handling part of the miniMax and AI section.
 * Containing functions which their purpose is to stands for the Computer's strategy
 * and computing.
 *
 *
 *
 * recursiveFunc			- The recursive function of MiniMax
 * score					- Scoring the game by it's states
 * scoreFuncId				- The scores for each object
 * AlphaBetaMove			- The main Brain of the MiniMax who operates the recursive function
 * moveAIobj				- Operates the compute's move using MiniMax Alpha-Beta pruning.
 *
 *
 *
 */


#include <limits.h>
#include <stdbool.h>
#include <assert.h>
#include "gameParser.h"
#include "alphaBetaMinMax.h"
#include "boardFuncs.h"
#include "gameCommands.h"




/**
 *
 * This function is the main recursive function which responsible for the MiniMax-Alpha-Beta pruning.
 * The function using the scoring function to determine which score is the best
 * for the the Mini-Max tree as taught.
 *
 * @param board - the Board Game Data structure.
 * @param minmax - determine if it's maximum or minimum node.
 * @param depth - the depth of the recursion.
 * @param recScore - recursive score for stopping and not calculating the whole tree
 *
 *
 * @return
 * The best score for maximum or minimum node.
 *
 */



int recursiveFunc(boardGame* board ,bool minmax,unsigned int depth, int recScore){
	assert(board!=NULL); //assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	int minWinner = INT_MAX;
	int maxWinner = INT_MIN;
	if ((depth==0)|| isTie(board))return score(board);
    else{
        int scoreWinner;
        int player = board->curPlayer;
        for(int i=ROW;i>=0;i--){
        	for (int j=COL; j>=0;j--){
        		if((player==1 && !isWhitePlayer(board->boardArr[i][j]))||
				   (player==0 && !isBlackPlayer(board->boardArr[i][j]))||
				   board->boardArr[i][j]==UNDERSCORE) continue;
        		for(int k=ROW;k>=0;k--){
        			for (int l=COL; l>=0;l--){
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
        						if(scoreWinner>=maxWinner){
									maxWinner = scoreWinner;
								}
        						if(scoreWinner>recScore &&  recScore!=INT_MIN ){
									undo(board,false,true);
									return scoreWinner;
								}
        					}
        					else if(minmax==false){
        						scoreWinner = recursiveFunc(board, !minmax, depth-1,minWinner);
        						if(scoreWinner<=minWinner){
									minWinner = scoreWinner ;
								}
        						if(scoreWinner<recScore && recScore!=INT_MAX){
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



/**
 *
 * The scoring function. Goes over each cell on board Game and checks it's symbol.
 * Later, using the scoreFuncId to determine if to add or to subtract (opponent's tool)
 * from the general results.
 *
 * @param board - the Board Game Data structure.e
 *
 *
 * @return
 * The score of the board Game state.
 *
 */

int score(boardGame* board){
    assert(board!=NULL); //assert(board->boardArr!=NULL);
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

/**
 *
 * This function get symbol and returns it's value on the boardGame to determine the
 * general score.
 *
 * @param symbol - the symbol on boardGame
 *
 *
 * @return
 * The defined scoring value.
 */

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


/**
 *
 * This function is the operates and managing the MiniMax-Alpha-Beta pruning.
 * The function using the recursion function to determine which score is the best
 * for the the Mini-Max tree, and returns the specific place to move to on board.
 *
 * @param board - the Board Game Data structure.
 * @param depth - the depth of the recursion.
 *
 *
 * @return
 * An Integer Array that includes the positions and destineation for the move function.
 *
 */



int* AlphaBetaMove(boardGame* board,unsigned int maxDepth){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	bool minmax = true;
	int maxCompare = INT_MIN;
	int minCompare = INT_MAX;
    int* arrMoves = (int*) malloc(2*sizeof(int));	//allocating place size of 2 ints
	if (maxDepth<=0){
		arrMoves[0] =-1; arrMoves[1]= -1;
		return arrMoves; 		// check this
	}
	else{
        int winnerScore;
        boardGame* copy = (boardGame*) copyBoard(board);
        assert(copy!=NULL); assert(copy->boardArr!=NULL);
        assert(copy->history!=NULL); assert(copy->history->elements!=NULL);
        // bool maxPlayer = false;
        if(copy->curPlayer==1) minmax = false;
        //if(copy->curPlayer==0) maxPlayer=true;
        for(int i=ROW;i>=0;i--){
        	for(int j=COL; j>=0;j--){
        		if((!minmax && !isWhitePlayer(copy->boardArr[i][j]))||
				   (minmax && !isBlackPlayer(copy->boardArr[i][j]))||
				   copy->boardArr[i][j]==UNDERSCORE) continue;
        		for (int k=ROW;k>=0;k--){
        			for(int l=COL; l>=0;l--){
        				if(moveObj(copy,RowColToNum(i,j),RowColToNum(k,l),false)){
        					if(isWinner(copy)){
        						undo(copy,false,true);
        						destroyBoard(copy);
        						arrMoves[0] = RowColToNum(i,j); arrMoves[1] = RowColToNum(k,l);
        						return arrMoves;}
        					else if(minmax){
        						winnerScore = recursiveFunc(copy, !minmax, maxDepth-1, maxCompare);
        						if (winnerScore == INT_MAX){
            						destroyBoard(copy);
            						arrMoves[0] = RowColToNum(i,j); arrMoves[1] = RowColToNum(k,l);
									return arrMoves;
        						}
        						else if(winnerScore>=maxCompare){
        							maxCompare = winnerScore;
        							arrMoves[0]=RowColToNum(i,j);arrMoves[1]= RowColToNum(k,l);
        						}}
        					else if(!minmax){
								winnerScore = recursiveFunc(copy, !minmax, maxDepth-1, minCompare);
								if (winnerScore == INT_MIN){
									destroyBoard(copy);
									arrMoves[0] = RowColToNum(i,j);
									arrMoves[1] = RowColToNum(k,l);
									return arrMoves;
								}
								else if(winnerScore<=minCompare){
									minCompare = winnerScore;
        							arrMoves[0]=RowColToNum(i,j);
        							arrMoves[1]= RowColToNum(k,l);
								}
							}
        					undo(copy,false,true);}}}}}
    	destroyBoard(copy);}
	return arrMoves;
}


/**
 *
 * This function is responsible for the computer's move.
 * the function using the alpha-beta function mentioned above to determine the position
 * and destination for the computer's move. Also doing the checking of the checkmate/check/tie
 * states.
 *
 * @param board - the Board Game Data structure.
 * @param checkActive - if to activate the check/checkmate/tie cehcing section.
 *
 *
 * @return
 * void. doing the move.
 *
 */


void moveAIobj(boardGame* board, bool checkActive){
	assert(board!=NULL); //assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	int* moveArr = (int*) AlphaBetaMove(board, board->diffLevel);
	bool valid = moveObj(board,moveArr[0],moveArr[1],false);
	if(valid && checkActive){
		computerMoveMessage(board,moveArr[0],moveArr[1]);
		if(!isMyKingSafe(board)){		//checking if the opponent king's is threatened
			if(isCheckMate(board)){
				free(moveArr);
				terminateGame(board,true, false);
			}
			printCheckMessage(board->curPlayer,board->userCol, board->gameMode);
		}
		else if (isCheckMate(board)){
			free(moveArr);
			terminateGame(board,false, true);
		}
	}
	free(moveArr);
}
