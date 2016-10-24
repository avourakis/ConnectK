#include <iostream>

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

int main()
{
    // declare
    int numRows = 4;
    int numCols = 5;

    int **array;
    array = new int*[numCols];
    for (int col = 0; col < numCols; ++col)
        array[col] = new int[numRows]; 
    
    // fill
    for ( int col = 0; col < numCols; ++col)
    {
        for ( int row = numRows - 1; row >= 0; --row)
            array[col][row] = row;
    }

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

    return 0;
}
