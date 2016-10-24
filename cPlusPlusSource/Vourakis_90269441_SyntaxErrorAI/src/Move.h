#ifndef MOVE_H
#define MOVE_H

#pragma once
class Move
{
public:
	int row; //the row to move to. 
	int col; //the col to move to.
    //int score; //the score of the move
	Move();
    //Move(int score);
	Move(int col, int row);
};

#endif //MOVE_H
