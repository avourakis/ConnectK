/*
 *  Team Name: SyntaxErrorAI
 *  Team Member: Andres Vourakis   
 */

#ifndef AISHELL_H
#define AISHELL_H

#pragma once
#include "Move.h"
#include <atomic>


// A new AIShell will be created for every move request.
class AIShell{

public:
	//these represent the values for each piece type.
	static const int AI_PIECE=1;
	static const int HUMAN_PIECE = -1;
	static const int NO_PIECE=0;


private:
	//Do not alter the values of numRows or numcols.
	//they are used for deallocating the gameState variable.
	int numRows; //the total number of rows in the game state.
	int numCols; //the total number of columns in the game state.
	int **gameState; //a pointer to a two-dimensional array representing the game state.
	bool gravityOn; //this will be true if gravity is turned on. It will be false if gravity is turned off.
	Move lastMove; //this is the move made last by your opponent. If your opponent has not made a move yet (you move first) then this move will hold the value (-1, -1) instead.
    Move randomMove(); //this will move to the left-most column possible

    /* minimax search implementation: Begin
     */

    // Evaluate game state and return a score
    int evaluate (int **gameState, int score, int player, Move lastMove); // Add const
    
    int evalHorizontal(int **gameState, int *aiScore, int *humanScore, Move lastMove);
    int evalVertical(int **gameState, int *aiScore, int *humanScore, Move lastMove);
    int evalDiagonal(int **gameState, int *aiScore, int *humanScore, Move lastMove);
    
    // check game state for terminal state. Return True if is a terminal state.
    bool terminalTest (int **gameState, int& score, int depth); // Add const 
    
    // Takes current game state, searches for best possible move and returns it.
    Move minimax (int **gameState, std::atomic<int>& done); 

    int max (int **gameState, int depth, int alpha, int beta, std::atomic<int>& done, Move lastMove); // Includes depth limit and Alpha beta pruning 
    int min (int **gameState, int depth, int alpha, int beta, std::atomic<int>& done, Move lastMove); // Includes depth limit and Alpha beta pruning
    
    // Given the current game state it determines who's turn is it. It returns 1 for AI play, -1 for human playerand 0 otherwise.
    int player (const int **gameState); 
    
    // Given the current game state it searches for k connected pieces. It returns +infinity if AI wins and -infinity otherwise. 0 if no winners.
    int checkWin (int **gameState); 

    // Helper functions for "checkWin()"
    int checkHorizontal(int **gameState);    
    int checkVertical(int **gameState);    
    int checkDiagonal(int **gameState);    

    /* minimax search implementation: End
     */

public:
	int deadline; //this is how many milliseconds the AI has to make move.
	int k;        // k is the number of pieces a player must get in a row/column/diagonal to win the game. IE in connect 4, this variable would be 4

	AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove);
	~AIShell();
	Move makeMove();
};

#endif //AISHELL_H
