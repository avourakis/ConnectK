/*
 *  Team Name: SyntaxErrorAI
 *  Team Member: Andres Vourakis   
 */

#include "AIShell.h"
#include <iostream>
#include <limits>
#include <cmath>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>

#define N_INFINITY std::numeric_limits<int>::min();
#define P_INFINITY std::numeric_limits<int>::max();
//#define MAX_DEPTH 10 // 10 is limit without alpha-beta

int MAX_DEPTH = 0;

AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=5000; // 5000 ms as used during tournament
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
     */

    int counter = 0;

    // R: Diagonals that start from first col
    for (int row = numRows - 1; row >= 0; --row)
    {
        for (int i = row, col = 0; (i < numRows && col < numCols); ++i, ++col)
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

    // R: Diagonals that start from last row
    for (int col = 1; col < numCols; ++col)
    {
        for (int i = col, row = 0; (i < numCols && row < numRows); ++i, ++row)
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

        counter =  0;
    }

    // L: Diagonals that start from last col
    for (int row = numRows - 1; row >= 0; --row)
    {
        for (int i = row, col = numCols - 1; (i < numRows && col >= 0); ++i, --col)
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

    // L: Diagonals that start from last row
    for (int col = (numCols - 1) - 1; col >= 0; --col)
    {
        for (int i = col, row = 0; (i >= 0 && row < numRows); --i, ++row)
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

        counter =  0;
    }

    return 0;
}

int AIShell::checkWin(int **gameState)
{
    /*
     * Improvements needed:
     * 1) Only check main diagonal(s) if k is equal to the number of rows 
     */

    int score = 0;
    
    if (k > numRows) // Only check horizontals if k is greater than number of rows
    {
        if((score = checkHorizontal(gameState)) != 0)
            return score;
    }
    
    else
    {
        if((score = checkHorizontal(gameState)) != 0)
            return score;
        else if((score = checkVertical(gameState)) != 0)
            return score;
        else if((score = checkDiagonal(gameState)) != 0)
            return score;
    }

    return 0;
}

int AIShell::evalVertical(int **gameState, int *aiScore, int* humanScore)
{
    for (int col = 0; col < numCols; ++col)
    {
        int pieces = 0;
        int blanks = 0;    
        for (int row = 0; row < numRows; ++row)
        {
            // It doesn't check for consecutive pieces.
            if (gameState[col][row] == 0)
                blanks++;
            else
                pieces += gameState[col][row];
        }
        // score AI
        if((pieces + blanks) >= k)
            aiScore += (pieces * 10); // 10 could be adjusted to improve score

        // score Human
        else if ((pieces - blanks) <= -k)
            humanScore += (pieces * 10); // 10 could be adjusted to improve score
    }


}

int AIShell::evalHorizontal(int **gameState, int *aiScore, int* humanScore)
{

    for (int row = 0; row < numRows; ++row)
    {
        int pieces = 0;
        int blanks = 0;    
        for (int col = 0; col < numCols; ++col)
        {
            // It doesn't check for consecutive pieces.
            if (gameState[col][row] == 0)
                blanks++;
            else
                pieces += gameState[col][row];
        }
        // score AI
        if((pieces + blanks) >= k)
            aiScore += (pieces * 10); // 10 could be adjusted to improve score

        // score Human
        else if ((pieces - blanks) <= -k)
            humanScore += (pieces * 10); // 10 could be adjusted to improve score
    }

}

int AIShell::evalDiagonal(int **gameState, int *aiScore, int* humanScore)
{
    return 0;
}


int AIShell::evaluate(int **gameState, int player)
{   
    int score = 0;
    if ((score = checkWin(gameState)) != 0) 
        return score;

    int aiScore = 0;
    int humanScore = 0;
    
    // Get evaluation scores
    evalVertical(gameState, &aiScore, &humanScore);
    evalHorizontal(gameState, &aiScore, &humanScore);
    evalDiagonal(gameState, &aiScore, &humanScore);


    // Returned evaluation for current player
    if (player == 1)
        return (aiScore - std::abs(humanScore));
    else if (player == -1)
        return (std::abs(humanScore) - aiScore);    
}

bool AIShell::terminalTest ( int **gameState, std::atomic<int>& done, int depth)
{
    if (checkWin(gameState) != 0 || depth > MAX_DEPTH) // if game is over
    //if (checkWin(gameState) != 0 || done == 1) // if game is over
        return true;

    return 0;
}

int AIShell::max(int **gameState, int depth, int alpha, int beta, std::atomic<int>& done)
{
    if (terminalTest(gameState, done, depth) == true)
    {
        /*
        if (depth < MAX_DEPTH) // If time is up, but search hasn't reached max depth
        {
            std::cout << "Ended without reaching max depth" << std::endl;
            return P_INFINITY;
        }
        */
        return evaluate(gameState, -1); // Review player
    }

    //int score = N_INFINITY; // This score could be less than negative infinity. REVIEW
    
    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                gameState[col][row] = 1; // play piece for min player
                
                int tempScore = min(gameState, ++depth, alpha, beta, done); // looks for min score

                if(tempScore > alpha) // The max value
                    alpha = tempScore;

                gameState[col][row] = 0; // removes piece to bring state back to normal   

                if(alpha >= beta)
                    return P_INFINITY; // Prune
            }

        }
    }
        

    return alpha;
}

int AIShell::min(int **gameState, int depth, int alpha, int beta, std::atomic<int>& done)
{
    if (terminalTest(gameState, done, depth) == true)
    {
        /*
        if (depth < MAX_DEPTH) // If time is up, but search hasn't reached max depth
        {
            std::cout << "Ended without reaching max depth" << std::endl;
            return N_INFINITY; // Ignore
        }
        */
        return evaluate(gameState, 1); // Review Player
    }
    //int score = P_INFINITY; // This score could be less than positive infinity. REVIEW
    
    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                gameState[col][row] = -1; // play piece for human player
                
                int tempScore = max(gameState, ++depth, alpha, beta, done); // looks for max score

                if(tempScore < beta) // The min value
                    beta = tempScore;

                gameState[col][row] = 0; // removes piece to bring state back to normal   

                if(alpha >= beta)
                    return N_INFINITY; // Prune
            }

        }
    }
    return beta;
}

Move AIShell::minimax(int **gameState, std::atomic<int>& done)
{
    int score = N_INFINITY;
    int alpha = N_INFINITY; // Alpha
    int beta = P_INFINITY; // Beta

    Move bestMove;
    bestMove.row = -1;
    bestMove.row = -1; 

    for(int d = 0; d < 20; d++) // Find out how many nodes possible at lowest level.
    {
        MAX_DEPTH = d;

        if (done == 1)
        {
            return bestMove;
        }

        if (d > 0) // Starting from bestMove
        {
            gameState[bestMove.col][bestMove.row] = 1; // play piece for max player
            
            int tempScore = min(gameState, 1, alpha, beta, done); // looks for max score. Passes a depth of 1
            alpha = tempScore; // Updating alpha
            
            if(tempScore >= score) // < or > will depend on default score
                score = tempScore;

            gameState[bestMove.col][bestMove.row] = 0; // removes piece to bring bag state back to normal   
        }

        for(int col = 0; col < numCols; ++col)
        {
            for (int row = 0; row < numRows; ++row)
            {
                if (gameState[col][row] == 0 && col != bestMove.col && row != bestMove.row)
                {
                    gameState[col][row] = 1; // play piece for max player
                    
                    int tempScore = min(gameState, 1, alpha, beta, done); // looks for max score. Passes a depth of 1
                    alpha = tempScore; // Updating alpha

                    if(tempScore >= score) // < or > will depend on default score
                    {
                        score = tempScore;
                        bestMove.col = col;
                        bestMove.row = row;
                        //std::cout << "COL: " << col << ", ROW: " << row << std::endl;
                    }    

                    gameState[col][row] = 0; // removes piece to bring bag state back to normal   
                }

            }
        }
        }

        /*
        for(int col = 0; col < numCols; ++col)
        {
            for (int row = 0; row < numRows; ++row)
            {
                if (gameState[col][row] == 0)
                {
                    gameState[col][row] = 1; // play piece for max player
                    
                    int tempScore = min(gameState, 1, alpha, beta); // looks for max score. Passes a depth of 1
                    alpha = tempScore; // Updating alpha

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
        */
    MAX_DEPTH = 0;

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
    for (int col = 0; col<numCols; ++col){
        for (int row = 0; row<numRows; ++row){
            if (gameState[col][row] == NO_PIECE){
                Move m(col, row);
                return m;
            }
        }
    }
}

Move AIShell::makeMove(){
    std::atomic<int> done{0};
    
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now(); // Start timer
    //std::thread thread1(minimax, std::ref(done), std::ref(timeElapsed));
    auto future = std::async(&AIShell::minimax, this, std::ref(gameState), std::ref(done)); // Creates a new thread and saves the return value in future

    while(!done)
    {
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now(); // End timer
        std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1); // Time elapsed in milliseconds

        if( mill.count() >= deadline && !done)
            done = 1; // Used to let thread know when to quit
    }

    //return minimax(gameState);
    return future.get(); // return the value from thread
}
