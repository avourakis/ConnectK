/*
 *
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
    for (int row = 0; row < numRows; ++row)
    {
        int aiCon = 0;
        int humanCon = 0;

        for (int col = 0; col < numCols; ++col)
        {

            if (aiCon == k) return P_INFINITY;
            if (humanCon == k) return N_INFINITY;

            if(gameState[col][row] == 1)
            {
                aiCon ++;
                humanCon = 0;
            }
            else if(gameState[col][row] == -1)
            {
                humanCon++;
                aiCon = 0;
            }
            else
            {
                aiCon = 0;
                humanCon = 0;
            } 
        }
    }

    return 0;
}

int AIShell::checkVertical(int **gameState)
{
    for (int col = 0; col < numCols; ++col)
    {
        int aiCon = 0;
        int humanCon = 0;

        for (int row = 0; row < numRows; ++row)
        {

            if (aiCon == k) return P_INFINITY;
            if (humanCon == k) return N_INFINITY;

            if(gameState[col][row] == 1)
            {
                aiCon ++;
                humanCon = 0;
            }
            else if(gameState[col][row] == -1)
            {
                humanCon++;
                aiCon = 0;
            }
            else
            {
                aiCon = 0;
                humanCon = 0;
            } 
        }
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
        int aiCon = 0;
        int humanCon = 0;

        for (int i = row, col = 0; (i < numRows && col < numCols); ++i, ++col)
        {
            if (aiCon == k) return P_INFINITY;
            if (humanCon == k) return N_INFINITY;

            if(gameState[col][row] == 1)
            {
                aiCon++;
                humanCon = 0;
            }
            else if(gameState[col][row] == -1)
            {
                humanCon++;
                aiCon = 0;
            }
            else
            {
                aiCon = 0;
                humanCon = 0;
            } 
        }
    }

    // R: Diagonals that start from last row
    for (int col = 1; col < numCols; ++col)
    {
        int aiCon = 0;
        int humanCon = 0;

        for (int i = col, row = 0; (i < numCols && row < numRows); ++i, ++row)
        {
            if (aiCon == k) return P_INFINITY;
            if (humanCon == k) return N_INFINITY;

            if(gameState[col][row] == 1)
            {
                aiCon++;
                humanCon = 0;
            }
            else if(gameState[col][row] == -1)
            {
                humanCon++;
                aiCon = 0;
            }
            else
            {
                aiCon = 0;
                humanCon = 0;
            } 
        }

    }

    // L: Diagonals that start from last col
    for (int row = numRows - 1; row >= 0; --row)
    {
        int aiCon = 0;
        int humanCon = 0;

        for (int i = row, col = numCols - 1; (i < numRows && col >= 0); ++i, --col)
        {
            if (aiCon == k) return P_INFINITY;
            if (humanCon == k) return N_INFINITY;

            if(gameState[col][row] == 1)
            {
                aiCon++;
                humanCon = 0;
            }
            else if(gameState[col][row] == -1)
            {
                humanCon++;
                aiCon = 0;
            }
            else
            {
                aiCon = 0;
                humanCon = 0;
            } 
        }
    }

    // L: Diagonals that start from last row
    for (int col = (numCols - 1) - 1; col >= 0; --col)
    {
        int aiCon = 0;
        int humanCon = 0;

        for (int i = col, row = 0; (i >= 0 && row < numRows); --i, ++row)
        {
            if (aiCon == k) return P_INFINITY;
            if (humanCon == k) return N_INFINITY;

            if(gameState[col][row] == 1)
            {
                aiCon++;
                humanCon = 0;
            }
            else if(gameState[col][row] == -1)
            {
                humanCon++;
                aiCon = 0;
            }
            else
            {
                aiCon = 0;
                humanCon = 0;
            } 
        }
    }

    return 0; 
}

int AIShell::checkWin(int **gameState)
{
    /*
     * Improvements needed:
     * 1) Only check main diagonal(s) if k is equal to the number of rows 
     * 2) Logic for when to check or not could be fixed.
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

int AIShell::evalVertical(int **gameState, int *aiScore, int* humanScore, Move lastMove)
{
    // NEW SCORING SYSTEM
    // Only evalutes column where last move was made
    int col = lastMove.col;

    // Evaluate AI
    int ai = 0, aiBlanks = 0, humanIndicator = 0, aiConnect = 0;

    for (int row = 0; row < numRows; ++row)
    {
        if(gameState[col][row] == 0 && humanIndicator == 0)
            aiBlanks++;
        else if(gameState[col][row] == -1)
        {
            if(ai == (k - 1)) // Check if ai had almost all k connected
                aiConnect = 1;

            humanIndicator = 1;
            if(ai == 0) aiBlanks = 0;
            else if((ai + aiBlanks) < k)
            {    
                ai = 0;
                aiBlanks = 0;
            }
            else 
                break;
        }
        else if(gameState[col][row] == 1)
        {
            humanIndicator = 0;
            ai++;
        }
    }


    if ((ai + aiBlanks) >= k) 
        aiScore += ai + 1; // 1 for potential places to play a piece

    // Evaluate other player
    int human = 0, humanBlanks = 0, aiIndicator = 0, humanConnect = 0;

    for (int row = 0; row < numRows; ++row)
    {
        if(gameState[col][row] == 0 && aiIndicator == 0)
            humanBlanks++;
        else if(gameState[col][row] == 1)
        {
            if(human == (k - 1)) // Check is human had almost all k connected
                humanConnect = 1;

            aiIndicator = 1;
            if(ai == 0) aiBlanks = 0;
            else if((human + humanBlanks) < k)
            {    
                human = 0;
                humanBlanks = 0;
            }
            else 
                break;
        }
        else if(gameState[col][row] == -1)
        {
            aiIndicator = 0;
            human++;
        }
    }

    if ((human + humanBlanks) >= k) 
        humanScore += human + 1; // 1 for potential places to play a piece

    
    //Bonus for blocking
    
    if (gameState[lastMove.col][lastMove.row] == -1 && aiConnect == 1)
    {
        // replace
        gameState[lastMove.col][lastMove.row] = 1;
        
        //check for human ai win
        int connected = 0;
        for (int row = 0; row < numRows; ++row)
        {
            if(gameState[lastMove.col][row] == 1)
                connected += 1;
            else
            {
                // give bonus for blocking
                if (connected == k)
                {
                   humanScore += 100;
                   break;
                }
                connected = 0;
            }
        }
        // put back
        gameState[lastMove.col][lastMove.row] = -1;    

    }

    else if (gameState[lastMove.col][lastMove.row] == 1 && humanConnect == 1)
    {
        // replace
        gameState[lastMove.col][lastMove.row] = -1;
        
        //check for human ai win
        int connected = 0;
        for (int row = 0; row < numRows; ++row)
        {
            if(gameState[lastMove.col][row] == -1)
                connected += 1;
            else
            {
                // give bonus for blocking
                if (connected == k)
                {
                   aiScore += 100;
                   break;
                }
                connected = 0;
            }
        }
        // put back
        gameState[lastMove.col][lastMove.row] = 1;    

    }
         

    /*
    for (int col = 0; col < numCols; ++col)
    {
        int pieces = 0;
        int blanks = 0;    
        int aiCon = 0; // Pieces placed consecutively.
        int humanCon = 0; // Pieces placed consecutively.

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
    */
}

int AIShell::evalHorizontal(int **gameState, int *aiScore, int* humanScore, Move lastMove)
{
    // NEW SCORING SYSTEM
    // Only evalutes row where last move was made, instead of entire board
    int row = lastMove.row;

    // Evaluate AI
    int ai = 0, aiBlanks = 0, humanIndicator = 0, aiConnect = 0;

    for (int col = 0; col < numCols; ++col)
    {
        if(gameState[col][row] == 0 && humanIndicator == 0)
            aiBlanks++;
        else if(gameState[col][row] == -1)
        {
            if(ai == (k - 1)) // Check if ai had almost all k connected
                aiConnect = 1;

            humanIndicator = 1;
            if(ai == 0) aiBlanks = 0;
            else if((ai + aiBlanks) < k)
            {    
                ai = 0;
                aiBlanks = 0;
            }
            else 
                break;
        }
        else if(gameState[col][row] == 1)
        {
            humanIndicator = 0;
            ai++;
        }
    }

    if ((ai + aiBlanks) >= k) 
        aiScore += ai + 1; // 1 for potential places to play a piece

    // Evaluate other player
    int human = 0, humanBlanks = 0, aiIndicator = 0, humanConnect = 0;

    for (int col = 0; col < numCols; ++col)
    {
        if(gameState[col][row] == 0 && aiIndicator == 0)
            humanBlanks++;
        else if(gameState[col][row] == 1)
        {
            if(human == (k - 1)) // Check is human had almost all k connected
                humanConnect = 1;

            aiIndicator = 1;
            if(ai == 0) aiBlanks = 0;
            else if((human + humanBlanks) < k)
            {    
                human = 0;
                humanBlanks = 0;
            }
            else 
                break;
        }
        else if(gameState[col][row] == -1)
        {
            aiIndicator = 0;
            human++;
        }
    }

    if ((human + humanBlanks) >= k) 
        humanScore += human + 1; // 1 for potential places to play a piece

    //Bonus for blocking
    
    if (gameState[lastMove.col][lastMove.row] == -1 && aiConnect == 1)
    {
        // replace
        gameState[lastMove.col][lastMove.row] = 1;
        
        //check for human ai win
        int connected = 0;
        for (int row = 0; row < numRows; ++row)
        {
            if(gameState[lastMove.col][row] == 1)
                connected += 1;
            else
            {
                // give bonus for blocking
                if (connected == k)
                {    
                   humanScore += 100;
                   break;
                }   

                connected = 0;
            }
        }
        // put back
        gameState[lastMove.col][lastMove.row] = -1;    

    }

    else if (gameState[lastMove.col][lastMove.row] == 1 && humanConnect == 1)
    {
        // replace
        gameState[lastMove.col][lastMove.row] = -1;
        
        //check for human ai win
        int connected = 0;
        for (int row = 0; row < numRows; ++row)
        {
            if(gameState[lastMove.col][row] == -1)
                connected += 1;
            else
            {    
                // give bonus for blocking
                if (connected == k)
                {    
                   aiScore += 100;
                   break;
                }   

                connected = 0;
            }
        }
        // put back
        gameState[lastMove.col][lastMove.row] = 1;    


    }

    // END OF NEW SCORING SYSTEM
    
    /*
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
    */
}

int AIShell::evalDiagonal(int **gameState, int *aiScore, int* humanScore, Move lastMove)
{
    return 0;
}


int AIShell::evaluate(int **gameState, int score, int player, Move lastMove)
{   
    if (score != 0) // Check for win
        return score;

    int aiScore = 0;
    int humanScore = 0;
    
    // Get evaluation scores

    if (numRows >= k) // Only check vert and diag if number of rows is greater or equal to k
    {
        evalVertical(gameState, &aiScore, &humanScore, lastMove);
        evalDiagonal(gameState, &aiScore, &humanScore, lastMove);
    }    

    if (numCols >= k) // Only check Hor if number of cols is greater or equal to k
        evalHorizontal(gameState, &aiScore, &humanScore, lastMove);


    // Returned evaluation for current player

    if (player == 1)
        return (aiScore - std::abs(humanScore));
    else if (player == -1)
        return (std::abs(humanScore) - aiScore);    
}

bool AIShell::terminalTest (int **gameState, int& score, int depth)
{
    if ((score = checkWin(gameState)) != 0 || depth > MAX_DEPTH) // if game is over
        return true;

    return false;
}

int AIShell::max(int **gameState, int depth, int alpha, int beta, std::atomic<int>& done, Move lastMove)
{
    int score = 0;
    if (terminalTest(gameState, score, depth) == true)
        return evaluate(gameState, score, -1, lastMove); // Review player

    //int score = N_INFINITY; // This score could be less than negative infinity. REVIEW
    
    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                gameState[col][row] = 1; // play piece for min player
                
                int tempScore = min(gameState, ++depth, alpha, beta, done, Move(col, row)); // looks for min score

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

int AIShell::min(int **gameState, int depth, int alpha, int beta, std::atomic<int>& done, Move lastMove)
{
    int score = 0;
    if (terminalTest(gameState, score, depth) == true)
        return evaluate(gameState, score,  1, lastMove); // Review Player

    //int score = P_INFINITY; // This score could be less than positive infinity. REVIEW
    
    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                gameState[col][row] = -1; // play piece for human player
                
                int tempScore = max(gameState, ++depth, alpha, beta, done, Move(col, row)); // looks for max score

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

    for(int d = 0; d < 30; d++) // Find out how many nodes possible at lowest level.
    {
        MAX_DEPTH = d;

        if (done == 1)
        {
            std::cout << "Time is up" << std::endl;
            std::cout << "Depth: " << d << std::endl;
            return bestMove;

        }    

        if (d > 0) // Starting from bestMove
        {
            gameState[bestMove.col][bestMove.row] = 1; // play piece for max player
            
            int tempScore = min(gameState, 1, alpha, beta, done, Move(bestMove.col, bestMove.row)); // looks for max score. Passes a depth of 1
            alpha = tempScore; // Updating alpha
            
            if(tempScore >= score) // < or > will depend on default score
                score = tempScore;

            gameState[bestMove.col][bestMove.row] = 0; // removes piece to bring bag state back to normal   
        }

        for(int col = 0; col < numCols; ++col)
        {
            for (int row = 0; row < numRows; ++row)
            {
                if (gameState[col][row] == 0 && col != bestMove.col && row != bestMove.row) // REVIEW THIS, REPEATING MOVE!!!!
                {
                    gameState[col][row] = 1; // play piece for max player
                    
                    int tempScore = min(gameState, 1, alpha, beta, done, Move(col, row)); // looks for max score. Passes a depth of 1
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
    }

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

    if(gameState[numCols-1][0] == 0)
        return Move(numCols - 1, 0);

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
