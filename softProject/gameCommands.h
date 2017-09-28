/*
 * gameCommands.h
 *
 *  Created on: 17 баев„ 2017
 *      Author: Itamar
 */

#ifndef GAMECOMMANDS_H_
#define GAMECOMMANDS_H_




#define BLACK "black"
#define WHITE "white"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "boardFuncs.h"
#include "gameParser.h"
#include "SPArrayList.h"


void undo(boardGame* board,bool printActivate, bool playerChangeAcivate);
void exUndo(boardGame* board,bool printActivate);
void changePlayer(boardGame* board);
void reset(boardGame* board);
void saveFile(boardGame* board, const char* path);
void moveMessage(boardGame* board);
void printCheckMessage(int player,int userCol, int gameMode);
bool isCheckMate(boardGame* board);
bool isThereOptionMove(boardGame* board,int row,int col);
void terminateGame(boardGame* board,bool mate, bool tie);
bool isWhitePlayer(char c);
bool isBlackPlayer(char c);
void getMovesFunc(boardGame* board,int position);
void getMovesPrintFunc(boardGame* copy, bool valid1, int rowDest, int colDest, int dest);
bool isWinner(boardGame* board);
bool isTie(boardGame* board);
void computerMoveMessage(boardGame* board, int position, int destination);
bool movePawn(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint);
bool moveBishop(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool moveRook(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool moveKnight(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool moveKing(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool moveQueen(boardGame* board, int xPos, int yPos, int xDest, int yDest, bool doPrint);
bool isValidDiagonal(boardGame* board, int rowPos, int colPos, int rowDest, int colDest);
bool isValidHorAndVar(boardGame* board, int rowPos, int colPos, int rowDest, int colDest);
bool moveObj(boardGame* board,int position, int destination,bool doPrint);
void switchObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, char obj,bool changePlayer);
bool switchAndCheck(boardGame* board, int rowPos, int colPos, int rowDest, int colDest,char obj1, char obj2, bool print);
void addMoveToHistory(boardGame* board,int rowPos,int colPos,int rowDest,int colDest);
int trackKingPosition(boardGame* board, char symbol);
bool isMyKingSafe(boardGame* board);
bool safeArea(boardGame* board,int position,char symbol);
bool isSafeStraight(boardGame* board,int row, int col,char symbol);
bool isSafeDiagnoal(boardGame* board,int row, int col,char symbol);
bool isSafeFromKingAndKnight(boardGame* board,int row, int col,char symbol);
bool isSafeFromPawn(boardGame* board,int row, int col,char symbol);

#endif /* GAMECOMMANDS_H_ */
