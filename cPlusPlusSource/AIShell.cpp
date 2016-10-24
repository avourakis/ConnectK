/*
 *  Team Name: SyntaxErrorAI
 *  Team Member: Andres Vourakis   
 */

#include "AIShell.h"
#include <iostream>
#include <limits>


#define N_INFINITY std::numeric_limits<int>::min();
#define P_INFINITY std::numeric_limits<int>::max();
#define MAX_DEPTH 10 // 10 might be pushing it

AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
}

int AIShell::checkHorizontal(int **gameState)
{
    
    int counter = 0;
        
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            if (gameState[col][row] == 0)
                counter = 0;
            else
                counter += gameState[col][row]; 
            
            if (counter == k)
            {
                return P_INFINITY;
            }
            else if (counter == -k)
                return N_INFINITY;
        }

        counter = 0;
    
    } 
    
    return 0;
}

int AIShell::checkVertical(int **gameState)
{
    int counter = 0;
        
    for (int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
                counter = 0;
            else
                counter += gameState[col][row]; 
            
            if (counter == k)
            {
                return P_INFINITY;
            }
            else if (counter == -k)
                return N_INFINITY;
        }

        counter = 0;
    
    } 
    return 0;

}

int AIShell::checkDiagonal(int **gameState)
{
    /*
     * Improvements need:
     * 1) Avoid looking into diagonals smaller than k
     * 2) use const
     * 3) i++ to ++i
     */

    int counter = 0;

    // R: Diagonals that start from first col
    for (int row = numRows - 1; row >= 0; row--)
    {
        for (int i = row, col = 0; (i < numRows && col < numCols); i++, col++)
        {
            //std::cout << "(" << col << ", " << i << ")" << std::endl;
            if (gameState[col][row] == 0)
                counter = 0;
            else
                counter += gameState[col][row]; 
            
            if (counter == k)
            {
                return P_INFINITY;
            }
            else if (counter == -k)
                return N_INFINITY;
        }
        counter = 0;
    }

    // R: Diagonals that start from last row
    for (int col = 1; col < numCols; col++)
    {
        for (int i = col, row = 0; (i < numCols && row < numRows); i++, row++)
        {
            //std::cout << "(" << i << ", " << row << ")" << std::endl;
            if (gameState[col][row] == 0)
                counter = 0;
            else
                counter += gameState[col][row]; 
            
            if (counter == k)
            {
                return P_INFINITY;
            }
            else if (counter == -k)
                return N_INFINITY;
        }

        counter =  0;
    }

    // L: Diagonals that start from last col
    for (int row = numRows - 1; row >= 0; row--)
    {
        for (int i = row, col = numCols - 1; (i < numRows && col >= 0); i++, col--)
        {
            //std::cout << "(" << col << ", " << i << ")" << std::endl;
            if (gameState[col][row] == 0)
                counter = 0;
            else
                counter += gameState[col][row]; 
            
            if (counter == k)
            {
                return P_INFINITY;
            }
            else if (counter == -k)
                return N_INFINITY;
        }
        counter = 0;
    }

    // L: Diagonals that start from last row
    for (int col = (numCols - 1) - 1; col >= 0; col--)
    {
        for (int i = col, row = 0; (i >= 0 && row < numRows); i--, row++)
        {
            //std::cout << "(" << i << ", " << row << ")" << std::endl;
            if (gameState[col][row] == 0)
                counter = 0;
            else
                counter += gameState[col][row]; 
            
            if (counter == k)
            {
                return P_INFINITY;
            }
            else if (counter == -k)
                return N_INFINITY;
        }

        counter =  0;
    }

    return 0;
}

int AIShell::checkWin(int **gameState)
{
    int score = 0;

    if((score = checkHorizontal(gameState)) != 0)
        return score;
    else if((score = checkVertical(gameState)) != 0)
        return score;
    else if((score = checkDiagonal(gameState)) != 0)
        return score;

    return 0;
}

int AIShell::player(const int **gameState)
{

    return 0;
}

int AIShell::evaluate(int **gameState, int player)
{   
    int score = 0;
    if ((score = checkWin(gameState)) != 0) 
        return score;

    if (player > 0)
    {
        
    }

    else if (player < 0)    
    {

    }

    return 0; // Its a tie
}

bool AIShell::terminalTest ( int **gameState, int depth)
{
    if (checkWin(gameState) != 0 || depth >= MAX_DEPTH) // if game is over
        return true;

    return 0;
}

int AIShell::max(int **gameState, int depth)
{
    if (terminalTest(gameState, depth) == true)
        return evaluate(gameState, -1); // Review player

    int score = N_INFINITY; // This score could be less than negative infinity. REVIEW
    
    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                gameState[col][row] = 1; // play piece for min player
                
                int tempScore = min(gameState, ++depth); // looks for min score

                if(tempScore > score) // < or > will depend on default score
                {
                    score = tempScore;

                }
                gameState[col][row] = 0; // removes piece to bring bag state back to normal   
            }

        }
    }
        

    return score;
}

int AIShell::min(int **gameState, int depth)
{
    if (terminalTest(gameState, depth) == true)
        return evaluate(gameState, 1); // Review Player

    int score = P_INFINITY; // This score could be less than positive infinity. REVIEW
    
    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                gameState[col][row] = -1; // play piece for human player
                
                int tempScore = max(gameState, ++depth); // looks for max score

                if(tempScore < score) // < or > will depend on default score
                {
                    score = tempScore;
                }    

                gameState[col][row] = 0; // removes piece to bring bag state back to normal   
            }

        }
    }
    return score;
}

Move AIShell::minimax(int **gameState)
{
    int score = N_INFINITY;
    Move bestMove;

    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                gameState[col][row] = 1; // play piece for max player
                
                int tempScore = min(gameState, 1); // looks for max score. Passes a depth of 1

                if(tempScore >= score) // < or > will depend on default score
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
	for (int i = 0; i<numCols; i++){
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
