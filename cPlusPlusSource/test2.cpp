for (int col = 0; col < numCols; ++col)
{
    int aiCon = 0; // Pieces placed consecutively.
    int humanCon = 0; // Pieces placed consecutively.

    for (int row = 0; row < numRows; ++row)
    {
        if(gameState[col][row] == 1)
        {
            aiCon += gameState[col][row];
            humanCon = 0;
        }
        else if(gameState[col][row] == -1)
        {
            humanCon += gameState[col][row];
            aiCon = 0;
        }
        else
        {
            aiCon++;
            humanCon++;
        } 
        //if(aiCon == k || humanCon == k) // Break if any of the players have enough pieces and/or space to connect k
            //break   
    }

    // score AI
    aiScore += (aiCon * 10);

    // score Human
    humanScore += (humanCon * 10);
}
