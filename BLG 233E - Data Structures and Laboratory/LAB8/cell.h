#ifndef CELL_H
#define CELL_H

#define MAZESIZE 5

typedef struct cell{
	bool left, right, up, down; // right = false when a wall does not exist otherwise, right = true means there is a wall
	char val; // initially this is empty (' '), when the cell is used to reach the exit, this becomes 'o'
	bool visited; // this variable will be used while generating maze randomly
	cell *next;
}StackDataType;

#endif
