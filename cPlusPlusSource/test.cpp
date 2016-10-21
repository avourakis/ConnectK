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
    
    int **array;
    array = new int*[4];
    for (int row = 0; row < 4; ++row)
        array[row] = new int[4]; 
    
    // fill
    for ( int row = 0; row < 4; ++row)
    {
        for ( int col = 0; col < 4; ++col)
            array[row][col] = row;
    }


    // print
    std::cout << "Printing original 2d array" << std::endl;
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            std::cout << array[row][col] << std::endl;
        }
    }
    
    pass(array);


    std::cout << "Printing original 2d array after passing to function" << std::endl;
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            std::cout << array[row][col] << std::endl;
        }
    }

    // delete
    for (int row = 0; row < 4; ++row )
        delete[] array[row];

    delete[] array;

    return 0;
}
