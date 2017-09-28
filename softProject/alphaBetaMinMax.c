/*
 * alphaBetaMinMax.c
 *
 *  Created on: 10 בספט׳ 2017
 *      Author: Itamar
 */

#include <limits.h>
#include <stdbool.h>
#include <assert.h>
#include "gameParser.h"
#include "alphaBetaMinMax.h"
#include "boardFuncs.h"
#include "gameCommands.h"


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
        						if(scoreWinner>=recScore){
									undo(board,false,true);
									return scoreWinner;
								}
        					}
        					else if(minmax==false){
        						scoreWinner = recursiveFunc(board, !minmax, depth-1,minWinner);
        						if(scoreWinner<=minWinner){
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
    //printf("the score is:%d\n",score);
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
	//printf("inside alphaBetaMove\n");
	assert(board!=NULL); //assert(board->boardArr!=NULL);
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
        //gameCopy->simulate = true;
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
        				//printf("i=%d, j=%d, k=%d, l=%d\n",i,j,k,l);
        				if(moveObj(copy,RowColToNum(i,j),RowColToNum(k,l),false)){
        					//printf("valid move: i=%d, j=%d, k=%d, l=%d\n",i,j,k,l);
        					if(isWinner(copy)){
        						//printf("inside isWinner\n");
        						undo(copy,false,true);
        						destroyBoard(copy);
        						arrMoves[0] = RowColToNum(i,j);
        						arrMoves[1] = RowColToNum(k,l);
        						return arrMoves;
        					}
        					else if(minmax){
        						//printf("int_max is:%d\n", INT_MAX);
        						//printf("max_compare is:%d\n", maxCompare);
        						winnerScore = recursiveFunc(copy, !minmax, maxDepth-1, maxCompare);
        						//printf("the winner score1 is:%d\n",winnerScore);
        						if (winnerScore == INT_MAX){
									//printf("the winner score is int_max\n");
            						destroyBoard(copy);
            						arrMoves[0] = RowColToNum(i,j);
									arrMoves[1] = RowColToNum(k,l);
									return arrMoves;
        						}
        						else if(winnerScore>=maxCompare){
        							//printf("in here 1\n");
        							maxCompare = winnerScore;
        							arrMoves[0]=RowColToNum(i,j);
        							arrMoves[1]= RowColToNum(k,l);
            						//printf("arrMoves[0] is:%d\n",arrMoves[0]);
            						//printf("arrMoves[1] is:%d\n",arrMoves[1]);
        						}
        						//else printf("done with winner score\n");
        					}
        					else if(!minmax){
								winnerScore = recursiveFunc(copy, !minmax, maxDepth-1, minCompare);
        						//printf("the winner score2 is:%d\n",winnerScore);
								if (winnerScore == INT_MIN){
									//printf("the winner score is int_min\n");
									destroyBoard(copy);
									arrMoves[0] = RowColToNum(i,j);
									arrMoves[1] = RowColToNum(k,l);
									return arrMoves;
								}
								else if(winnerScore<=minCompare){
									//printf("in here 2\n");
									minCompare = winnerScore;
        							arrMoves[0]=RowColToNum(i,j);
        							arrMoves[1]= RowColToNum(k,l);
        							//printf("arrMoves[0] is:%d\n",arrMoves[0]);
									//printf("arrMoves[1] is:%d\n",arrMoves[1]);
								}
							}
        					//printf("before undo\n");
        					undo(copy,false,true);
        					//printf("after undo\n");
        				}
        			}
        		}
        	}
        }
        //printf("before destroy board\n");
    	destroyBoard(copy);
    	//printf("after destroy board\n");
    	//printf("the winner score is: %d\n", winnerScore);
	}
	return arrMoves;
}



void moveAIobj(boardGame* board){
	//printf("at the beggining of move AI OBJEcCT\n");
	assert(board!=NULL); //assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	//printf("after the asserts og aiobject\n");
	int* moveArr = (int*) AlphaBetaMove(board, board->diffLevel);
	//printf("inside moveAiObj\n");
	//printf("the suggest pos is: %d, the suggest dest is:%d\n",moveArr[0],moveArr[1]);
	//printf("before valid of moveAiObj\n");
	bool valid = moveObj(board,moveArr[0],moveArr[1],false);
	//if(!valid) printf("not valid\n");
	//if(valid) printf("computer move is not!!! valid\n");
	if(valid){
		computerMoveMessage(board,moveArr[0],moveArr[1]);
		if(!isMyKingSafe(board)){		//checking if the opponent king's is threatened
			//printf("there is a risk on the king");
			if(isCheckMate(board)){
				free(moveArr);
				terminateGame(board,true, false);
			}
			printCheckMessage(board->curPlayer,board->userCol, board->gameMode);
			//printf("we got yill here");
		}
		else if (isCheckMate(board)){
			free(moveArr);
			terminateGame(board,false, true);
		}
	}
	//printf("at the end of moveaiObj\n");
	free(moveArr);
}
