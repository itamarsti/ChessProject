/*
 * gameCommands.c
 *
 *  Created on: 17 ����� 2017
 *      Author: Itamar
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gameCommands.h"
#include "boardFuncs.h"
#include "gameParser.h"


/**
 * gameCommands summary:
 *
 * This parts includes all the functions which relevant to the Game Moves and the Game flow
 * such as objects move operations, undo, saving, reseting, winner checks etc.
 *
 *
 * undo						- Committing undo action .
 * exUndo					- Executing the undo action.
 * changePlayer				- changes the playr's turn each turn.
 * reset					- Doing reset to the GameBoard.
 * saveFile					- Saving the current board status to a File.
 * moveMessage				- Printing message before every turn.
 * printCheckMessage		- Printing the "Check/checkmate/tie message".
 * isCheckMate				- Checking if there was a checkMate or tie.
 * isThereOptionMove		- Checking if were left options move to an object
 * terminateGame			- Terminating the game in case of CheckMate or tie
 * isWhitePlayer			- Checking if a position on board is occupied by a white player Object
 * isBlackPlayer			- Checking if a position on board is occupied by a black player Object
 * getMovesFunc				- Printing all the possible moves from a given position
 * getMovesPrintFunc		- Printing the get_moves function on the demanded format
 * isWinner					- Checking if there was a CheckMate
 * isTie					- Checking if there was a tie
 * computerMoveMessage		- Printing the computer move by the demanded format
 * movePawn					- Checking if a pawn move Object on board is valid and move it
 * moveBishop				- Checking if a Bishop's move Object on board is valid and move it
 * moveRook					- Checking if a Rook move Object on board is valid and move it
 * moveKnight				- Checking if a Knight move Object on board is valid and move it
 * moveKing					- Checking if a King move Object on board is valid and move it
 * moveQueen				- Checking if a Queen move Object on board is valid and move it
 * isValidDiagonal			- Checking if diagonal move on board is legal
 * isValidHorAndVar			- Checking if horizontal and vertical moves on board are legal
 * moveObj					- The main function which managing a move of an object on board game
 * switchObj				- Doing the actual move of an Object of any kind
 * switchAndCheck			- Checking if the king is safe and activating switchObj
 * addMoveToHistory			- Adding the move to the board game history.
 * trackKingPosition		- Checking where is the white/black king position
 * isMyKingSafe				- Checking if no opponent's object threatening the king
 * safeArea					- Managing the checks if the king is safe in different directions
 * isSafeStraight			- Checking if king is safe in straight direction
 * isSafeDiagnoal			- Checking if king is safe in diagonal direction
 * isSafeFromKingAndKnight	- Checking if king is safe from the opponent's king and knight
 * isSafeFromPawn			- Checking if king is safe from the opponent's pawn
 *
 *
 *
 */



/**
 *
 *
 * Changing the current Player on GameBoard Settings
 *
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */

void changePlayer(boardGame* board){
	assert(board!=NULL);
	if(board->curPlayer==0) board->curPlayer=1;
	else if (board->curPlayer==1) board->curPlayer=0;
}


/**
 *
 *
 * Doing restart to the game by destroying it and printing the relevant message
 *
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */
void reset(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	destroyBoard(board);
	printf("Restarting...\n");
	return;
}

/**
 *
 * Saving the current state of the Game Board to a given path
 *
 * @param board - the Board Game Data structure.
 * @param path - the path where we want to save the current state.
 * @return
 * void
 *
 */

void saveFile(boardGame* board, const char* path){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(path!=NULL);
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	if(!isFileCreated(path)){
			printf("File cannot be created or modified\n");
			return;
		}
	FILE* file = (FILE*) fopen(path,"w");
	assert(file!=NULL);
	fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",file);
	fputs("<game>\n",file);
	fprintf(file,"\t<current_turn>%d</current_turn>\n",board->curPlayer);
	fprintf(file,"\t<game_mode>%d</game_mode>\n",board->gameMode);
	if(board->gameMode==1){
		fprintf(file,"\t<difficulty>%d</difficulty>\n",board->diffLevel);
		fprintf(file,"\t<user_color>%d</user_color>\n",board->userCol);
	}
	fputs("\t<board>\n",file);
	for(int i=0;i<ROW;i++){
		fprintf(file,"\t\t<row_%d>",8-i);
		for (int j=0;j<COL;j++){
			fprintf(file,"%c",board->boardArr[i][j]);
		}
		fprintf(file,"</row_%d>\n",8-i);
	}
	fputs("\t</board>\n",file);
	fputs("</game>\n",file);
	fclose(file);
}


/**
 *
 * Doing the actual work of undo by using the history and replace the objects
 * on the Game board.
 *
 * @param board - the Board Game Data structure.
 * @param printActivate - true if we want to print the "undo action"
 * @return
 * void
 *
 */

void exUndo(boardGame* board,bool printActivate){
	assert(board!=NULL);
	//assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	int index = board->history->actualSize-1;
	char objDest = (char)board->history->elements[index];
	int posDest = board->history->elements[index-1];
	char objSource = (char)board->history->elements[index-2];
	int posSource = board->history->elements[index-3];
	board->boardArr[NumToRow(posDest)][NumToCol(posDest)] = objDest;
	board->boardArr[NumToRow(posSource)][NumToCol(posSource)] = objSource;
	if(printActivate){
		char po = (char) (NumToCol(posSource)+'A');
		char de = (char) (NumToCol(posDest)+'A');
		if(board->curPlayer==0){
			if(printActivate) printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",
			BLACK,8-NumToRow(posDest),de,8-NumToRow(posSource),po);
		}
		else if(board->curPlayer==1){
			if(printActivate)printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",
			WHITE,8-NumToRow(posDest),de,8-NumToRow(posSource),po);
		}
	}
	return;
}


/**
 *
 * Activating the Exundo function and deleting the last 4 details from the history.
 *
 * @param board - the Board Game Data structure.
 * @param printActivate - true if we want to see the exUndo prints
 * @param playerChangeActivate - true if we want change players turn after undo
 * @return
 * void
 *
 */

void undo(boardGame* board, bool printActivate, bool playerChangeAcivate){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	if (playerChangeAcivate)changePlayer(board);
	exUndo(board,printActivate);
	for(int i=0;i<4;i++){
		spArrayListRemoveLast(board->history);
	}
	return;
}

/**
 *
 * Printing the move Message of the user in the right format
 *
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */

void moveMessage(boardGame* board){
	assert(board!=NULL);
	if(board->gameMode==2){
		if(board->curPlayer==0) printf("%s player - enter your move:\n",BLACK);
		else if(board->curPlayer==1) printf("%s player - enter your move:\n",WHITE);
	}
	else if(board->gameMode==1){
		if(board->curPlayer==board->userCol){
			if(board->curPlayer==0) printf("%s player - enter your move:\n",BLACK);
			else if(board->curPlayer==1) printf("%s player - enter your move:\n",WHITE);
		}
		else return;
	}
}

/**
 *
 * Printing the check Message in case there was a "check".
 *
 * @param player - the current player.
 * @param userCol - the user color.
 * @param gameMode - the Game mode.
 * @return
 * void
 *
 */

void printCheckMessage(int player,int userCol, int gameMode){
	if(gameMode==1 && userCol==player)printf("Check!\n");
	else{
		if(player==1) printf("Check: %s King is threatened!\n",WHITE);
		else if(player==0) printf("Check: %s King is threatened!\n",BLACK);
	}
}

/**
 *
 * Checking if there are no legal moves on board (indication for checkMate/tie)
 *
 * @param board - the Board Game Data structure.
 * @return
 * true - if there is no valid move
 * false - if there is at least 1 valid move.
 *
 */


bool isCheckMate(boardGame* board){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	bool valid = false;
	if(board->curPlayer==0){
		for(int i=0; i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(isBlackPlayer(board->boardArr[i][j])){
					valid = isThereOptionMove(board,i,j);
					if(valid) return false;
				}
			}
		}
	}
	else if(board->curPlayer==1){
		for(int i=0; i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(isWhitePlayer(board->boardArr[i][j])){
					valid = isThereOptionMove(board,i,j);
					if(valid) return false;
				}
			}
		}
	}
	return true;
}

/**
 *
 * Checking if by a given row and column (position on board), there is move from it
 * to other valid destination.
 *
 * @param board - the Board Game Data structure.
 * @paran row - the row on board.
 * @param col - the column on board.
 * @return
 * true - if there is at least one valid move.
 * false - if there no moves at all.
 *
 */

bool isThereOptionMove(boardGame* board,int row,int col){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	boardGame* copy = copyBoard(board);
	assert(copy!=NULL);
	assert(copy->boardArr!=NULL);
	assert(copy->history!=NULL);
	assert(copy->history->elements!=NULL);
	bool valid = false;
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			valid = moveObj(copy,RowColToNum(row,col),RowColToNum(i,j),false);
			if(valid){
				destroyBoard(copy);
				return true;
			}				// no need to undo/destroy cause if !valid - no move was done
		}
	}
	destroyBoard(copy);
	return false;
}

/**
 *
 * Printing CheckMate or Tie message, destroying the board and exit the program.
 *
 * @param board - the Board Game Data structure.
 * @return
 * void
 *
 */

void terminateGame(boardGame* board, bool mate, bool tie){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	if(mate){
		if(board->curPlayer==0){
			printf("Checkmate! %s player wins the game\n",WHITE);
		}
		else if(board->curPlayer==1){
			printf("Checkmate! %s player wins the game\n",BLACK);
		}
		destroyBoard(board);
		exit(0);
	}
	else if (tie){
		if(board->gameMode==2)printf("The game is tied\n");
		else if(board->gameMode==1) printf("The game ends in a tie\n");
		destroyBoard(board);
		exit(0);
	}
}

/**
 *
 * Checking if a char is a white legal obj.
 *
 * @param c - char.
 * @return
 * true - if it's a white legal object, false - otherWise.
 *
 */

bool isWhitePlayer(char c){
	if (c==WhitePawn || c==WhiteRook || c==WhiteBishop || c==WhiteQueen
			|| c==WhiteKing || c==WhiteKnight) return true;
	return false;
}

/**
 *
 * Checking if a char is a black legal obj.
 *
 * @param c - char.
 * @return
 * true - if it's a black legal object, false - otherWise.
 *
 */

bool isBlackPlayer(char c){
	if (c==BlackPawn || c==BlackRook || c==BlackBishop || c==BlackQueen
				|| c==BlackKing || c==BlackKnight) return true;
		return false;
}


/**
 *
 * This function responsible to find and show all the possible moves of a given object on board,
 * or to print error if something is not right.
 * This function first do all the possible moves. If the move is valid it calls
 * another function to finish the job.
 *
 * @param board - the Board Game Data structure.
 * @param position - the symbol's/object's position on board (0-63)
 * @return
 * void
 *
 */


void getMovesFunc(boardGame* board,int position){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	int row = NumToRow(position);
	int col = NumToCol(position);
	if (position>63 || position<0 )	printf("Invalid position on the board\n");
	if(board->gameMode==2){
		printf("ERROR: the command is not available in 2-players mode\n");
		return;
	}
	if(board->gameMode==1 && board->diffLevel>=3){
		printf("ERROR: the command is not available in difficulty>2\n");
		return;
	}
	if (board->curPlayer==0 &&
			(isWhitePlayer(board->boardArr[row][col])|| board->boardArr[row][col]==UNDERSCORE))
		printf("The specified position does not contain %s player piece\n",BLACK);
	else if (board->curPlayer==1 &&
			(isBlackPlayer(board->boardArr[row][col])|| board->boardArr[row][col]==UNDERSCORE))
			printf("The specified position does not contain %s player piece\n",WHITE);
	else{
		bool valid,valid1 = false;
		int rowDest, colDest, dest =0;
		boardGame* copy = copyBoard(board);
		assert(copy!=NULL); assert(copy->boardArr!=NULL);
		assert(copy->history!=NULL); assert(copy->history->elements!=NULL);
		for(int i=7; i>=0;i--){
			rowDest = i;
			for (int j=0;j<COL;j++){
				colDest = j;
				if (rowDest==row && colDest==col) continue;
				dest = RowColToNum(rowDest,colDest);
				if((board->curPlayer==0 && isWhitePlayer(board->boardArr[rowDest][colDest]))
					||(board->curPlayer==1 && isBlackPlayer(board->boardArr[rowDest][colDest])))
					valid1 = true;		// need to be checked before the move action
				valid = moveObj(copy,position,dest, false);
				if(!valid){
					valid1 = false;
					continue;
				}
				else if (valid){				//if valid move == true
					getMovesPrintFunc(copy, valid1,rowDest, colDest, dest);
					undo(copy,false,true);		//if we are here, move was done
					}
				valid1 = false;
			}
		}
		destroyBoard(copy);
	}
return;
}

/**
 *
 * This function do the continue checks and prints the get_moves in the right format
 *  after the first move was given.
 *
 * @param copy - the Board Game Data structure.
 * @param rowDest - the symbol's/object's destination row on board (0-7) after the move
 * @param colDest  - the symbol's/object's destination column on board (0-7) after the move
 * @param dest - the destination to move to (the second move actually to check if there is a threat.
 * @return
 * void
 *
 */


void getMovesPrintFunc(boardGame* copy, bool valid1, int rowDest, int colDest, int dest){
	assert(copy!=NULL);
	assert(copy->boardArr!=NULL);
	assert(copy->history!=NULL);
	assert(copy->history->elements!=NULL);
	bool valid2 = false;
	for(int k=0;k<ROW;k++){
		for(int l=0;l<COL;l++){
			valid2 = moveObj(copy,RowColToNum(k,l),dest, false);
			if(valid2==true && valid1==true){
				printf("<%d,%c>*^\n",8-rowDest,(char)(colDest+'a'));
				undo(copy,false,true);
				return;
			}
			else if (valid2==true && valid1==false){
				printf("<%d,%c>*\n",8-rowDest,(char)(colDest+'a'));
				undo(copy,false,true);
				return;
			}
		}
	}
	if (valid1==true)printf("<%d,%c>^\n",8-rowDest,(char)(colDest+'a'));
	else printf("<%d,%c>\n",8-rowDest,(char)(colDest+'a'));
}


/**
 *
 * This function responsible to find and if there was a checkmate only.
 *
 * @param board - the Board Game Data structure.
 * @return
 * true - if there was a checkmate, false otherwise.
 *
 */


bool isWinner(boardGame* board){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	bool isKingSafe = isMyKingSafe(board);
	bool checkMate = isCheckMate(board);
	if(isKingSafe==false && checkMate==true) return true;
	return false;
}


/**
 *
 * This function responsible to find if there was a tie only.
 * @param board - the Board Game Data structure.
 * @return
 * true - if there was a tie, false otherwise.
 *
 */

bool isTie(boardGame* board){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	assert(board->history!=NULL); assert(board->history->elements!=NULL);
	bool isKingSafe = isMyKingSafe(board);
	bool checkMate = isCheckMate(board);
	if(isKingSafe==true && checkMate==true) return true;
	return false;
}

/**
 *
 * This function responsible to print the computer's move in the right format.
 *
 * @param board - the Board Game Data structure.
 * @param position - the symbol's/object's position on board (0-63)
 * @param destination  - the symbol's/object's destination on board (0-63)
 * @return
 * void
 *
 */

void computerMoveMessage(boardGame* board, int position, int destination){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	int posRow = NumToRow(position); int posCol = NumToCol(position);
	int destRow = NumToRow(destination); int destCol = NumToCol(destination);
	printf("Computer: move ");
	char c = board->boardArr[destRow][destCol];
	if(c==BlackPawn|| c==WhitePawn) printf("pawn");
	else if(c==BlackBishop || c==WhiteBishop) printf("bishop");
	else if(c==BlackKnight|| c==WhiteKnight) printf("knight");
	else if(c==BlackRook || c==WhiteRook) printf("rook");
	else if(c==BlackQueen || c==WhiteQueen) printf("queen");
	else if(c==BlackKing || c==WhiteKing) printf("king");
	printf(" at <%d,%c> to <%d,%c>\n",8-posRow,(char)(posCol+'A'),8-destRow, (char)(destCol+'A'));
}


/**
 *
 * This function responsible to check if a given pawn's move is valid and do the move
 * in case the validation is true.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the pawn's position row on board (0-7)
 * @param colPos - the pawn's position column on board (0-7)
 * @param rowDest  - the pawn's destination row on board (0-7)
 * @param colDest  - the pawn's destination column on board (0-7)
 * @param doPrint  - if to print the relevant messeages or not.
 * @return
 * true if the move is valid, false otherwise.
 *
 */

bool movePawn(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	bool secRow = false;
	if ((rowPos==1 && board->curPlayer==0) || (rowPos==6 && board->curPlayer==1)) secRow=true;
	if (board->curPlayer==0){			//black player case
		if(rowDest==rowPos+1 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
			return valid;
		}
		else if((rowDest==rowPos+2 && board->boardArr[rowDest][colDest]==UNDERSCORE
					&& board->boardArr[rowPos+1][colDest]==UNDERSCORE && colPos==colDest)
				&& secRow){
				valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
				return valid;
			}
		else if (rowDest==rowPos+1 && (colPos==colDest+1 || colPos==colDest-1)&&
				isWhitePlayer(board->boardArr[rowDest][colDest])){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
			return valid;
			}
		}
	else if (board->curPlayer==1){			//white player case
		if(rowDest==rowPos-1 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
			return valid;
		}
		else if((rowDest==rowPos-2 && board->boardArr[rowDest][colDest]==UNDERSCORE
				&& colPos==colDest && board->boardArr[rowPos-1][colDest]==UNDERSCORE)
				 && secRow){
				valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
				return valid;
			}
		else if (rowDest==rowPos-1 && (colPos==colDest+1 || colPos==colDest-1)&&
				isBlackPlayer(board->boardArr[rowDest][colDest])){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackPawn,WhitePawn, doPrint);
			return valid;
			}
		}
	if(doPrint) printf("Illegal move\n");
	return false;
}

/**
 *
 * This function responsible to check if a given Rook's move is valid and do the move
 * in case the validation is true.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the Rook's position row on board (0-7)
 * @param colPos - the Rook's position column on board (0-7)
 * @param rowDest  - the Rook's destination row on board (0-7)
 * @param colDest  - the Rook's destination column on board (0-7)
 * @param doPrint  - if to print the relevant messeages or not.
 * @return
 * true if the move is valid, false otherwise.
 *
 */

bool moveRook(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos!=rowDest && colPos!=colDest){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	if((board->curPlayer==0 && isBlackPlayer(board->boardArr[rowDest][colDest]))
			|| (board->curPlayer==1 && isWhitePlayer(board->boardArr[rowDest][colDest]))){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	valid = isValidHorAndVar(board, rowPos, colPos, rowDest, colDest);
	if (valid==false){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	valid = switchAndCheck(board,rowPos,colPos, rowDest, colDest, BlackRook, WhiteRook, doPrint);
	return valid;
}

/**
 *
 * This function responsible to check if a given Bishop's move is valid and do the move
 * in case the validation is true.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the Bishop's position row on board (0-7)
 * @param colPos - the Bishop's position column on board (0-7)
 * @param rowDest  - the Bishop's destination row on board (0-7)
 * @param colDest  - the Bishop's destination column on board (0-7)
 * @param doPrint  - if to print the relevant messeages or not.
 * @return
 * true if the move is valid, false otherwise.
 *
 */

bool moveBishop(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL); assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos==rowDest || colPos==colDest){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	valid = isValidDiagonal(board, rowPos, colPos,rowDest,colDest);
	if (valid==false){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	valid = switchAndCheck(board,rowPos,colPos, rowDest, colDest, BlackBishop, WhiteBishop, doPrint);
	return valid;
}

/**
 *
 * This function responsible to check if a given Knight's move is valid and do the move
 * in case the validation is true.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the Knight's position row on board (0-7)
 * @param colPos - the Knight's position column on board (0-7)
 * @param rowDest  - the Knight's destination row on board (0-7)
 * @param colDest  - the Knight's destination column on board (0-7)
 * @param doPrint  - if to print the relevant messeages or not.
 * @return
 * true if the move is valid, false otherwise.
 *
 */


bool moveKnight(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if((rowPos==rowDest+2 || rowPos==rowDest-2)&& (colPos==colDest+1||colPos==colDest-1)){
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKnight, WhiteKnight, doPrint);
		return valid;
	}
	else if((rowPos==rowDest+1 || rowPos==rowDest-1)&& (colPos==colDest+2||colPos==colDest-2)){
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKnight, WhiteKnight, doPrint);
		return valid;
	}
	if(doPrint) printf("Illegal move\n");
	return false;
}


/**
 *
 * This function responsible to check if a given King's move is valid and do the move
 * in case the validation is true.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the King's position row on board (0-7)
 * @param colPos - the King's position column on board (0-7)
 * @param rowDest  - the King's destination row on board (0-7)
 * @param colDest  - the King's destination column on board (0-7)
 * @param doPrint  - if to print the relevant messeages or not.
 * @return
 * true if the move is valid, false otherwise.
 *
 */

bool moveKing(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if(abs(rowPos-rowDest)>1 || abs(colPos-colDest)>1){
		if(doPrint) printf("Illegal move\n");
		return false;
	}
	else{
		valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackKing, WhiteKing, doPrint);
		return valid;
	}
}

/**
 *
 * This function responsible to check if a given Queen's move is valid and do the move
 * in case the validation is true.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the Queen's position row on board (0-7)
 * @param colPos - the Queen's position column on board (0-7)
 * @param rowDest  - the Queen's destination row on board (0-7)
 * @param colDest  - the Queen's destination column on board (0-7)
 * @param doPrint  - if to print the relevant messeages or not.
 * @return
 * true if the move is valid, false otherwise.
 *
 */


bool moveQueen(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid;
	if (rowPos==rowDest || colPos==colDest){
		if(isValidHorAndVar(board, rowPos, colPos,rowDest,colDest)){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackQueen, WhiteQueen, doPrint);
			return valid;
		}
	}
	else if (abs(rowPos-rowDest)==abs(colPos-colDest)){
		if(isValidDiagonal(board, rowPos, colPos,rowDest,colDest)){
			valid = switchAndCheck(board,rowPos,colPos,rowDest, colDest,BlackQueen, WhiteQueen, doPrint);
			return valid;
		}
	}
	if(doPrint) printf("Illegal move\n");
	return false;
}

/**
 *
 * This function check if a general move is valid in diagonal direction.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the Queen's position row on board (0-7)
 * @param colPos - the Queen's position column on board (0-7)
 * @param rowDest  - the Queen's destination row on board (0-7)
 * @param colDest  - the Queen's destination column on board (0-7)
 * @return
 * true if the move is valid, false otherwise.
 *
 */


bool isValidDiagonal(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if (abs(rowPos-rowDest)!=abs(colPos-colDest))return valid;
	if(rowPos<rowDest && colPos<colDest){
			for(int i=rowPos+1, j=colPos+1; i<rowDest;i++,j++){
				if(board->boardArr[i][j]!=UNDERSCORE){
					return valid;
				}
			}
		}
	if(rowPos<rowDest && colPos>colDest){
		for(int i=rowPos+1, j=colPos-1; i<rowDest;i++,j--){
			if(board->boardArr[i][j]!=UNDERSCORE){
				return valid;
			}
		}
	}
	if(rowPos>rowDest && colPos<colDest){
		for(int i=rowPos-1, j=colPos+1; i>rowDest;i--,j++){
			if(board->boardArr[i][j]!=UNDERSCORE){
				return valid;
			}
		}
	}
	if(rowPos>rowDest && colPos>colDest){
		for(int i=rowPos-1, j=colPos-1; i>rowDest;i--,j--){
			if(board->boardArr[i][j]!=UNDERSCORE){
				return valid;
			}
		}
	}
	return !valid;
}


/**
 *
 * This function check if a general move is valid in horizontal and vertical direction.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the Queen's position row on board (0-7)
 * @param colPos - the Queen's position column on board (0-7)
 * @param rowDest  - the Queen's destination row on board (0-7)
 * @param colDest  - the Queen's destination column on board (0-7)
 * @return
 * true if the move is valid, false otherwise.
 *
 */


bool isValidHorAndVar(boardGame* board, int rowPos, int colPos, int rowDest, int colDest){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	if(rowPos==rowDest){
		if(colPos<colDest){
			for(int i=colPos+1;i<colDest;i++){
				if(board->boardArr[rowPos][i]!=UNDERSCORE){
					return valid;
				}
			}
		}
		else if(colDest<colPos){
			for(int i=colPos-1;i>colDest;i--){
				if(board->boardArr[rowPos][i]!=UNDERSCORE){
					return valid;
				}
			}
		}
	}
	else if (colPos==colDest){
		if (rowPos<rowDest){
			for(int i=rowPos+1;i<rowDest;i++){
				if (board->boardArr[i][colDest]!=UNDERSCORE){
					return valid;
				}
			}
		}
		else if(rowDest<rowPos){
			for(int i=rowPos-1;i>rowDest;i--){
				if (board->boardArr[i][colDest]!=UNDERSCORE){
					return valid;
				}
			}
		}
	}
	return !valid;
}

/**
 *
 * This function responsible to the actual switching places on boardGame
 * by activating the switchObj function and also to do some checks before such as if
 * the move is causing to the king any damger.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the object's position row on board (0-7)
 * @param colPos - the object's position column on board (0-7)
 * @param rowDest  - the object's destination row on board (0-7)
 * @param colDest  - the object's destination column on board (0-7)
 * @param obj1  - black Player objects
 * @param obj2  - white player objects
 * @param print  - if to do the prints.
 *
 * @return
 * true if the move is valid, false otherwise.
 *
 */


bool switchAndCheck(boardGame* board, int rowPos, int colPos, int rowDest, int colDest,char obj1, char obj2, bool print){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool valid = false;
	boardGame* copy = (boardGame*) copyBoard(board);
	assert(copy!=NULL); assert(copy->boardArr!=NULL);
	if((board->curPlayer==0) && (board->boardArr[rowDest][colDest]==UNDERSCORE ||
		isWhitePlayer(board->boardArr[rowDest][colDest]))){
			switchObj(copy, rowPos, colPos, rowDest, colDest,obj1,false);
			valid = isMyKingSafe(copy);
			if(valid){
				destroyBoard(copy);
				switchObj(board, rowPos, colPos, rowDest, colDest,obj1,true);
				return true;
			}
		}
	else if((board->curPlayer==1) && (board->boardArr[rowDest][colDest]==UNDERSCORE ||
		isBlackPlayer(board->boardArr[rowDest][colDest]))){
		switchObj(copy, rowPos, colPos, rowDest, colDest,obj2,false);
		valid = isMyKingSafe(copy);
		if(valid){
			destroyBoard(copy);
			switchObj(board, rowPos, colPos, rowDest, colDest,obj2,true);
			return true;
		}
	}
	if(print) printf("Illegal move\n");
	destroyBoard(copy);
	return false;
}


/**
 *
 * This function responsible for doing the actual move on boardGAme.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - the object's position row on board (0-7)
 * @param colPos - the object's position column on board (0-7)
 * @param rowDest  - the object's destination row on board (0-7)
 * @param colDest  - the object's destination column on board (0-7)
 * @param obj1  - black Player objects
 * @param obj2  - white player objects
 * @param chaPla  - boolean: if also to change turns in the game.
 *
 * @return
 * void
 *
 */

void switchObj(boardGame* board, int rowPos, int colPos, int rowDest, int colDest, char obj,bool chaPla){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	addMoveToHistory(board,rowPos,colPos,rowDest,colDest);
	board->boardArr[rowPos][colPos] = UNDERSCORE;
	board->boardArr[rowDest][colDest] = obj;
	if(chaPla) changePlayer(board);
}

/**
 *
 * This main function which managing the moving actions on board. The function do some initial
 * checks to determine if the move is legal and then classifying & activating
 * the relevant move functions depends on the object's symbol.
 *
 * @param board - the Board Game Data structure.
 * @param position - the symbol's/object's position on board (0-63)
 * @param destination  - the symbol's/object's destination on board  we want to move to(0-63)
 * @param doPrint - if to print the comments or not.
 * @return
 * true if the move is valid, false otherwise.
 *
 */

bool moveObj(boardGame* board,int position, int destination,bool doPrint){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	fflush(stdout);
	bool validMove = false;
	int rowPos = NumToRow(position);
	int colPos = NumToCol(position);
	int rowDest = NumToRow(destination);
	int colDest = NumToCol(destination);
	if ((rowPos<0|| rowPos>7 || colPos<0|| colPos>7 || rowDest<0|| rowDest>7 || colDest<0|| colDest>7)){
		if(doPrint) printf("Invalid position on the board\n");
		return false;
	}
	else if ((board->curPlayer==0) && (isWhitePlayer(board->boardArr[rowPos][colPos])
			|| board->boardArr[rowPos][colPos]==UNDERSCORE)){	//black and lower
		if(doPrint) printf("The specified position does not contain your piece\n");
		return false;
	}
	else if ((board->curPlayer==1) && (isBlackPlayer(board->boardArr[rowPos][colPos])
			|| board->boardArr[rowPos][colPos]==UNDERSCORE)){	//white and upper
		if(doPrint)printf("The specified position does not contain your piece\n");
		return false;
	}
	else if(rowPos==rowDest && colPos==colDest){
		if(doPrint)printf("Illegal move\n");
		return false;
	}
	char obj = board->boardArr[rowPos][colPos];
		 if (obj==BlackPawn|| obj ==WhitePawn) validMove = movePawn(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj==BlackRook || obj ==WhiteRook) validMove = moveRook(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj==BlackBishop || obj ==WhiteBishop) validMove = moveBishop(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj==BlackKnight || obj ==WhiteKnight) validMove = moveKnight(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj==BlackKing || obj ==WhiteKing) validMove = moveKing(board,rowPos,colPos,rowDest,colDest, doPrint);
	else if (obj==BlackQueen || obj ==WhiteQueen) validMove = moveQueen(board,rowPos,colPos,rowDest,colDest, doPrint);
	return validMove;	//change player and add move to history are in switchObj func.
}


/**
 *
 * This function is managing the king's safety checks by activating other functions which
 * find the king's position and check that there is no danger from any direction by the
 * opponent's objects.
 *
 * @param board - the Board Game Data structure.
 *
 * @return
 * true if it's threatened, false otherwise.
 *
 */


bool isMyKingSafe(boardGame* board){
	assert(board!=NULL);
	bool safe = false;
	int position = -1;
	if(board->curPlayer==1){
		position = trackKingPosition(board, WhiteKing);
		if(position==-1){
			printf("ERROR: whiteKing wasn't found\n"); // never suppose to act
			return true;
		}
		safe = safeArea(board, position,WhiteKing);
	}
	else if (board->curPlayer==0){
		position = trackKingPosition(board, BlackKing);
		if(position==-1){
			printf("ERROR: whiteKing wasn't found\n");  //never suppose to act
			return true;
		}
		safe = safeArea(board, position,BlackKing);
	}
	return safe;
}

/**
 *
 * This function is managing the king's safety checking. The function activating
 * all kinds of safety functions to check if king is not threatened by any of the
 * the opponent's tool.
 *
 * @param board - the Board Game Data structure.
 * @param position - integer between 0-63, the position of the king on board Game.
 * @param symbol - whiteKing or blackKing char symbol
 *
 *
 * @return
 * true if it's threatened, false otherwise.
 *
 */

bool safeArea(boardGame* board,int position,char symbol){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	int row = NumToRow(position);
	int col = NumToCol(position);
	bool safe = true;
	if((safe = isSafeStraight(board,row, col, symbol))==false) return false;	//covers queen&rook
	if((safe = isSafeDiagnoal(board,row, col, symbol))==false) return false;	//covers queen&bishop
	if((safe = isSafeFromKingAndKnight(board,row, col, symbol))==false) return false;	//covers king&knight
	if((safe = isSafeFromPawn(board,row, col, symbol))==false) return false;	//covers pawn
	return true;
}

/**
 *
 * This function is checking if a given whiteKing/blackKing
 * is safe from any opponent's object in straight direction.
 *
 * @param board - the Board Game Data structure.
 * @param row - row position of the object before the move
 * @param col - column position of the object before the move
 * @param symbol - whiteKing or blackKing char symbol
 *
 *
 * @return
 * true if it's threatened, false otherwise.
 *
 */

bool isSafeStraight(boardGame* board,int row, int col,char symbol){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	if(symbol==WhiteKing){
		for(int i=row+1;i<ROW;i++){
			if(board->boardArr[i][col]==UNDERSCORE) continue;
			else if(board->boardArr[i][col]==BlackRook||board->boardArr[i][col]==BlackQueen)
				return false;
			else break;
		}
		for(int i=row-1;i>=0;i--){
			if(board->boardArr[i][col]==UNDERSCORE) continue;
			else if(board->boardArr[i][col]==BlackRook||board->boardArr[i][col]==BlackQueen)
				return false;
			else break;
		}
		for(int i=col+1;i<COL;i++){
			if(board->boardArr[row][i]==UNDERSCORE) continue;
			else if(board->boardArr[row][i]==BlackRook||board->boardArr[row][i]==BlackQueen)
				return false;
			else break;
		}
		for(int i=col-1;i>=0;i--){
			if(board->boardArr[row][i]==UNDERSCORE) continue;
			else if(board->boardArr[row][i]==BlackRook||board->boardArr[row][i]==BlackQueen)
				return false;
			else break;
		}
	}
	else if(symbol==BlackKing){
		for(int i=row+1;i<ROW;i++){
			if(board->boardArr[i][col]==UNDERSCORE) continue;
			else if(board->boardArr[i][col]==WhiteRook||board->boardArr[i][col]==WhiteQueen)
				return false;
			else break;
		}
		for(int i=row-1;i>=0;i--){
			if(board->boardArr[i][col]==UNDERSCORE) continue;
			else if(board->boardArr[i][col]==WhiteRook||board->boardArr[i][col]==WhiteQueen)
				return false;
			else break;
		}
		for(int i=col+1;i<COL;i++){
			if(board->boardArr[row][i]==UNDERSCORE) continue;
			else if(board->boardArr[row][i]==WhiteRook||board->boardArr[row][i]==WhiteQueen)
				return false;
			else break;
		}
		for(int i=col-1;i>=0;i--){
			if(board->boardArr[row][i]==UNDERSCORE) continue;
			else if(board->boardArr[row][i]==WhiteRook||board->boardArr[row][i]==WhiteQueen)
				return false;
			else break;
		}
	}
	return true;
}

/**
 *
 * This function is checking if a given whiteKing/blackKing
 * is safe from any opponent's object in diagonal direction.
 *
 * @param board - the Board Game Data structure.
 * @param row - row position of the object before the move
 * @param col - column position of the object before the move
 * @param symbol - whiteKing or blackKing char symbol
 *
 *
 * @return
 * true if it's threatened, false otherwise.
 *
 */

bool isSafeDiagnoal(boardGame* board,int row, int col,char symbol){
	assert(board!=NULL);assert(board->boardArr!=NULL);
	int i = 1;
	if(symbol==WhiteKing){
		while (row+i<ROW && col+i<COL){
			if(board->boardArr[row+i][col+i]==UNDERSCORE) i++;
			else if(board->boardArr[row+i][col+i]==BlackBishop||board->boardArr[row+i][col+i]==BlackQueen)
				return false;
			else break;}
		i = 1;
		while (row-i>=0 && col+i<COL){
			if(board->boardArr[row-i][col+i]==UNDERSCORE) i++;
			else if(board->boardArr[row-i][col+i]==BlackBishop||board->boardArr[row-i][col+i]==BlackQueen)
				return false;
			else break;}
		i = 1;
		while (row-i>=0 && col-i>=0){
			if(board->boardArr[row-i][col-i]==UNDERSCORE) i++;
			else if(board->boardArr[row-i][col-i]==BlackBishop||board->boardArr[row-i][col-i]==BlackQueen)
				return false;
			else break;}
		i = 1;
		while (row+i<ROW && col-i>=0){
			if(board->boardArr[row+i][col-i]==UNDERSCORE) i++;
			else if(board->boardArr[row+i][col-i]==BlackBishop||board->boardArr[row+i][col-i]==BlackQueen)
				return false;
			else break;}
	}
	else if(symbol==BlackKing){
		while (row+i<ROW && col+i<COL){
			if(board->boardArr[row+i][col+i]==UNDERSCORE) i++;
			else if(board->boardArr[row+i][col+i]==WhiteBishop||board->boardArr[row+i][col+i]==WhiteQueen)
				return false;
			else break;}
		i = 1;
		while (row-i>=0 && col+i<COL){
			if(board->boardArr[row-i][col+i]==UNDERSCORE) i++;
			else if(board->boardArr[row-i][col+i]==WhiteBishop||board->boardArr[row-i][col+i]==WhiteQueen)
				return false;
			else break;}
		i = 1;
		while (row-i>=0 && col-i>=0){
			if(board->boardArr[row-i][col-i]==UNDERSCORE) i++;
			else if(board->boardArr[row-i][col-i]==WhiteBishop||board->boardArr[row-i][col-i]==WhiteQueen)
				return false;
			else break;}
		i = 1;
		while (row+i<ROW && col-i>=0){
			if(board->boardArr[row+i][col-i]==UNDERSCORE) i++;
			else if(board->boardArr[row+i][col-i]==WhiteBishop||board->boardArr[row+i][col-i]==WhiteQueen)
				return false;
			else break;}
	}
	return true;
}

/**
 *
 * This function is checking if a given whiteKing/blackKing
 * is safe from the opponent's king and knights.
 *
 * @param board - the Board Game Data structure.
 * @param row - row position of the object before the move
 * @param col - column position of the object before the move
 * @param symbol - whiteKing or blackKing char symbol
 *
 *
 * @return
 * true if it's threatened, false otherwise.
 *
 */

bool isSafeFromKingAndKnight(boardGame* board,int row, int col,char symbol){
	if(symbol==WhiteKing){
		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(board->boardArr[i][j]==BlackKing){
					if ((abs(i-row)==1 && abs(j-col)==1)|| (abs(i-row)==1 && abs(j-col)==0)
						||(abs(i-row)==0 && abs(j-col)==1))return false;
				}
				if(board->boardArr[i][j]==BlackKnight){
					if ((abs(i-row)==2 && abs(j-col)==1)||(abs(i-row)==1 && abs(j-col)==2))
						return false;
				}
			}
		}
	}
	else if(symbol==BlackKing){
		for(int i=0;i<ROW;i++){
			for(int j=0;j<COL;j++){
				if(board->boardArr[i][j]==WhiteKing){
					if ((abs(i-row)==1 && abs(j-col)==1)|| (abs(i-row)==1 && abs(j-col)==0)
						||(abs(i-row)==0 && abs(j-col)==1))return false;
				}
				if(board->boardArr[i][j]==WhiteKnight){
					if ((abs(i-row)==2 && abs(j-col)==1)||(abs(i-row)==1 && abs(j-col)==2))
						return false;
				}
			}
		}
	}
	return true;
}

/**
 *
 * This function is checking if a given whiteKing/blackKing
 * is safe from the the opponent's pawns - means no pawn threatening it.
 *
 * @param board - the Board Game Data structure.
 * @param row - row position of the object before the move
 * @param col - column position of the object before the move
 * @param symbol - whiteKing or blackKing char symbol
 *
 *
 * @return
 * true if it's threatened, false otherwise.
 *
 */

bool isSafeFromPawn(boardGame* board,int row, int col,char symbol){
	if(symbol==WhiteKing){
		if(row>0){
			if(col>=1 && col<=6){
				if(board->boardArr[row-1][col-1]==BlackPawn ||
					board->boardArr[row-1][col+1]==BlackPawn)return false;
			}
			else if(col==0){
				if(board->boardArr[row-1][col+1]==BlackPawn) return false;
			}
			else if(col==7){
				if(board->boardArr[row-1][col-1]==BlackPawn) return false;
			}
		}
	}
	else if(symbol==BlackKing){
		if(row<7){
			if(col>=1 && col<=6){
				if(board->boardArr[row+1][col-1]==WhitePawn ||
					board->boardArr[row+1][col+1]==WhitePawn)return false;
			}
			else if(col==0){
				if(board->boardArr[row+1][col+1]==WhitePawn) return false;
			}
			else if(col==7){
				if(board->boardArr[row+1][col-1]==WhitePawn) return false;
			}
		}
	}
	return true;
}

/**
 *
 * Tracking an object position on board using it's symbol,
 * actually was used only to find the king's position.
 *
 * @param board - the Board Game Data structure.
 * @param symbol - the whiteKing/BlackKing symbol
 * @return
 * The king's position on board (0-63), -1 if it's not there (never should happen).
 *
 */


int trackKingPosition(boardGame* board, char symbol){
	assert(board!=NULL);
	assert(board->boardArr!=NULL);
	for (int i=0;i<ROW;i++){
		for (int j=0;j<COL;j++){
			if (board->boardArr[i][j]==symbol) return RowColToNum(i,j);
		}
	}
	return -1;				// in case the king wasn't found
}


/**
 *
 * The purpose of this function is to to save the moves in history structure (SPArrayList)
 * in order doing undo. The function adds to the arrayList the position, obj in position,
 * destination, obj in destination (4 details every time).
 * If the history is full, the function clears from the array the oldest event,
 * and inserting new one.
 *
 * @param board - the Board Game Data structure.
 * @param rowPos - row position of the object before the move
 * @param colPos - column position of the object before the move
 * @param rowDest - row destination of the other object before the move
 * @param colDest - column destination of other object beforel the move
 *
 * @return
 * void
 *
 */


void addMoveToHistory(boardGame* board,int rowPos,int colPos,int rowDest,int colDest){
	assert(board!=NULL); assert(board->boardArr!=NULL);	assert(board->history!=NULL);
	assert(board->history->elements!=NULL);
	if(spArrayListIsFull(board->history)){
		for(int i=0;i<4;i++){
			spArrayListRemoveFirst(board->history);
		}
	}
	spArrayListAddLast(board->history, RowColToNum(rowPos,colPos));
	spArrayListAddLast(board->history, (int) board->boardArr[rowPos][colPos]);
	spArrayListAddLast(board->history, RowColToNum(rowDest,colDest));
	spArrayListAddLast(board->history, (int) board->boardArr[rowDest][colDest]);
	return;
}


