/*
 * alphaBetaMinMax.h
 *
 *  Created on: 10 בספט׳ 2017
 *      Author: Itamar
 */

#ifndef ALPHABETAMINMAX_H_
#define ALPHABETAMINMAX_H_


#include "boardFuncs.h"
#include "gameCommands.h"
#include "gameParser.h"


int recursiveFunc(boardGame* board ,bool minmax,unsigned int depth, int recScore);
int score(boardGame* board);
int scoreFuncId(char symbol);
int* AlphaBetaMove(boardGame* board,unsigned int maxDepth);
void moveAIobj(boardGame* board);

#endif /* ALPHABETAMINMAX_H_ */
