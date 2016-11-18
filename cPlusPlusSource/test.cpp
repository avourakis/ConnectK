#include <iostream>
#include <limits>
#include <cmath>

#define N_INFINITY std::numeric_limits<int>::min();
#define P_INFINITY std::numeric_limits<int>::max();

int numCols = 5;
int numRows = 4;
int count = 0;

int min(int **gameState, int depth, int alpha, int beta);
int max(int **gameState, int depth, int alpha, int beta);

int MAX_DEPTH = 0;

struct Move
{
public:
	int row; //the row to move to. 
	int col; //the col to move to.
};

int pass(int** x)
{
    x[0][1] = 8;
    std::cout << "Printing 2d array after modifying" << std::endl;
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            std::cout << x[row][col] << std::endl;
        }
    }
    return 0;
}    



int max(int **gameState, int depth, int alpha, int beta)
{
    if(depth > MAX_DEPTH)
        return 10;
    


    /*
    if (terminalTest(gameState, depth) == true)
        return evaluate(gameState, -1); // Review player
    */

    //int score = N_INFINITY; // This score could be less than negative infinity. REVIEW
    
    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                std::cout << "max: (" << col << ", " << row << ")" << std::endl; 
                gameState[col][row] = 1; // play piece for min player
                count += 1;
                
                int tempScore = min(gameState, ++depth, alpha, beta); // looks for min score

                if(tempScore > alpha) // The max value
                    alpha = tempScore;

                gameState[col][row] = 0; // removes piece to bring state back to normal   

                if(alpha >= beta)
                {
                    std::cout << "PRUNE" << std::endl;
                    return P_INFINITY; // Prune
                }
            }

        }
    }
        

    return alpha;
}

int min(int **gameState, int depth, int alpha, int beta)
{
    if(depth > MAX_DEPTH)
        return -10;
    /*
    if (terminalTest(gameState, depth) == true)
        return evaluate(gameState, 1); // Review Player
    */

    //int score = P_INFINITY; // This score could be less than positive infinity. REVIEW

    
    for(int col = 0; col < numCols; ++col)
    {
        for (int row = 0; row < numRows; ++row)
        {
            if (gameState[col][row] == 0)
            {
                std::cout << "min: (" << col << ", " << row << ")" << std::endl; 
                gameState[col][row] = -1; // play piece for human player
                
                count += 1;
                                
                int tempScore = max(gameState, ++depth, alpha, beta); // looks for max score

                if(tempScore < beta) // The min value
                    beta = tempScore;

                gameState[col][row] = 0; // removes piece to bring state back to normal   
                
                if(alpha >= beta){
                    std::cout << "PRUNE" << std::endl;
                    return N_INFINITY; // Prune
                }
            }

        }
    }
    return beta;
}

Move minimax(int **gameState)
{
    int score = N_INFINITY;
    int alpha = N_INFINITY; // Alpha
    int beta = P_INFINITY; // Beta

    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for(int d = 0; d < numCols; d++)
    {
        MAX_DEPTH = d;

        std::cout << "Current bound: " << d << std::endl;
        
        if(d > 0)
        {
            std::cout << "minimax: (" << bestMove.col << ", " << bestMove.row << ")" << std::endl; 
            gameState[bestMove.col][bestMove.row] = 1; // play piece for max player
            count += 1;
            
            int tempScore = min(gameState, 1, alpha, beta); // looks for max score. Passes a depth of 1
            alpha = tempScore; // Updating alpha

            if(tempScore >= score) // < or > will depend on default score
            {
                score = tempScore;
            } 

            gameState[bestMove.col][bestMove.row] = 0; // removes piece to bring bag state back to normal   
        }
            for(int col = 0; col < numCols; ++col)
            {
                for (int row = 0; row < numRows; ++row)
                {
                    std::cout << bestMove.col << std::endl;
                    std::cout << bestMove.row << std::endl;
                    if (gameState[col][row] == 0 && col != bestMove.col && row != bestMove.row)
                    //if (gameState[col][row] == 0)
                    {
                        std::cout << "minimax: (" << col << ", " << row << ")" << std::endl; 
                        gameState[col][row] = 1; // play piece for max player
                        count += 1;
                        
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
            
       /* 
        else
        {

            for(int col = 0; col < numCols; ++col)
            {
                for (int row = 0; row < numRows; ++row)
                {
                    if (gameState[col][row] == 0)
                    {
                        std::cout << "minimax: (" << col << ", " << row << ")" << std::endl; 
                        gameState[col][row] = 1; // play piece for max player
                        count += 1;
                        
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
        }
        */
    }
    MAX_DEPTH = 0;
    return bestMove;
}


int main()
{
    // declare
    int **array;
    array = new int*[numCols];
    for (int col = 0; col < numCols; ++col)
        array[col] = new int[numRows]; 
    
    // fill
    for ( int col = 0; col < numCols; ++col)
    {
        for ( int row = numRows - 1; row >= 0; --row)
            //array[col][row] = row;
            array[col][row] = 0;
    }

    
    /* New state
     */

    
    minimax(array);
    std::cout << count << std::endl;

    /* End
     */

    /*

    // print
    std::cout << "Printing original 2d array" << std::endl;
    for (int col = 0; col < numCols; ++col)
    {
        for (int row = numRows-1; row >= 0; --row)
        {
            std::cout << array[col][row] << std::endl;
        }
    }

    // Diagonals that start from first col
    for (int row = numRows - 1; row >= 0; row--)
    {
        //int i, col;
        std::cout << "call" << std::endl;
        for (int i = row, col = 0; (i < numRows && col < numCols); i++, col++)
        {
            //std::cout << "(" << col << ", " << i << ")" << std::endl;
            std::cout << array[col][i] << std::endl;
        }
    }
    std::cout << "" << std::endl;
    // Diagonals that start from last row
    for (int col = 1; col < numCols; col++)
    {
        //int i, col;
        std::cout << "call" << std::endl;
        for (int i = col, row = 0; (i < numCols && row < numRows); i++, row++)
        {
            //std::cout << "(" << i << ", " << row << ")" << std::endl;
            std::cout << array[i][row] << std::endl;
        }
    }

    
    
    // delete
    for (int row = 0; row < 4; ++row )
        delete[] array[row];

    delete[] array;
    */
    return 0;
}
