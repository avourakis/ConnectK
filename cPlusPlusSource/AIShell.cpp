/*
 *  Team Name: SyntaxErrorAI
 *  Team Member: Andres Vourakis   
 */

#include "AIShell.h"
#include <iostream>
#include <limits>

#define N_INFINITY = std::numeric_limits<int>::min();
#define P_INFINITY = std::numeric_limits<int>::max();

AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
}

int AIShell::checkWin(const int **gameState)
{
    return 0;
}

int AIShell::player(const int **gameState)
{

    return 0;
}

int AIShell::evaluate(const int **gameState)
{

    return 0;
}

int AIShell::terminalTest (const int **gameState)
{

    return 0;
}

int AIShell::max(int **gameState)
{
    if terminalTest(gameState)
        return evaluate(gameState)
    
    int score = N_INFINITE; // This score could be less than negative infinity. REVIEW
        

    return 0;
}

int AIShell::min(int **gameState)
{
    return 0;
}

Move AIShell::minimax(int **gameState)
{
    int score = 0;
    Move bestMove;

    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                gameState[col][row] = 1; // play piece for max player
                
                int tempScore = max(gameState); // looks for max score

                if(tempScore > score) // < or > will depend on default score
                {
                    score = tempScore;
                    bestMove.col = col;
                    bestMove.row = row;
                }    

                gameState[col][row] = 0; // removes piece to bring bag state back to normal   
            }

        }
    }

    return bestMove;
}

AIShell::~AIShell()
{
	
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;

}

Move AIShell::randomMove()
{
    //this will move to the left-most column possible.
    for (int col = 0; col<numCols; col++){
        for (int row = 0; row<numRows; row++){
            if (gameState[col][row] == NO_PIECE){
                Move m(col, row);
                return m;
            }
        }
    }
}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2
    	
    return minimax(gameState);
}
