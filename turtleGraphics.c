// Project: Turtle Graphics
// Author: Parampal Singh Gill
// Date: October 14, 2023

/*  This program processes an array of commands which causes turtle to draw
	a pattern on a 2D floor. This pattern is diplayed after commands have been executed */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define NROWS 22 // number of rows in floor
#define NCOLS 70 // number of colums in floor
#define TRUE 1
#define FALSE 0


// function prototypes
void turtleDraw(const int[]); // main function responsible for executing cmds
void displayFloor(const short[][NCOLS]);
void moveTurtle(short[][NCOLS], const int, const enum Dirs, const short, int*, int*);


const unsigned int STARTING_ROW = 0;    // row that turtle will start in
const unsigned int STARTING_COL = 0;    // column that turtle will start in

enum TCmnds { PEN_UP = 1, PEN_DWN = 2, TURN_RIGHT = 3, TURN_LEFT = 4, MOVE = 5, DISPLAY = 6, END_OF_DATA = 9 };
enum Dirs { BEGIN_VALUE, NORTH, EAST, SOUTH, WEST, END_VALUE };

// direction that turtle will be facing at the start
const enum Dirs STARTING_DIRECTION = SOUTH; 

// Pen will be up when program starts; 0 (false) means pen up; 1 (true) means pen down
const short STARTING_PEN_POSITION = FALSE; 

int main()
{
	//int commands[] = { 5, 5, 4, 5, 9, 2,   // go to start of first letter and put pen down

	//	// B
	//	5, 12, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 2, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 11, 3, 5, 5,
	//	1, 3, 5, 12, 3, 5, 5, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 2, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 11, 3, 5, 5,

	//	1, 5, 5, 3, 5, 22, 2, // go to start of next letter and put pen down

	//	// O
	//	5, 10, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 7, 1, 3, 5, 1, 4, 2, 5, 1,
	//	1, 3, 5, 1, 2, 5, 10, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 7, 1, 3, 5, 1, 4, 2, 5, 1,

	//	1, 3, 5, 19, 2,     // go to start of next letter and put pen down

	//	// B
	//	5, 12, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 2, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 11, 3, 5, 5,
	//	1, 3, 5, 12, 3, 5, 5, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 2, 1, 3, 5, 1, 4, 2, 5, 1, 1, 3, 5, 1, 2, 5, 11, 3, 5, 5,

	//	// Test program bound checking and add border in the process

	//	//   Uncomment next line when ready to test out of bounds checking
	//	1, 5, 100, 2, 4, 5, 100, 4, 5, 100, 4, 5, 100, 4, 5, 100, 4, 5, 100,

	//	1, 6, 9 }; // finish off

	int commands[] = { 5, 5, 4, 5, 15,    // go to start of first letter and put pen down

		// G
		2, 5, 9, 3, 5, 1, 3, 5, 10, 4, 5, 9, 4, 5, 9, 4, 5, 4, 4, 5, 5, 3, 5, 1, 3, 5, 6,
		3, 5, 6, 3, 5, 11, 3, 1, 5, 1, 2, 5, 9, 1,

		// move pen to beginning of next letter
		5, 1, 3, 5, 16, 3,

		// I
		2, 5, 11, 4, 5, 1, 4, 5, 12, 1,

		// move to beginning of next letter
		3, 5, 5, 3, 5, 1,

		// L
		2, 5, 11, 4, 5, 8, 4, 5, 1, 4, 5, 7, 3, 5, 11, 1,

		// to beginning of next letter
		3, 5, 12, 3, 5, 1,

		// L
		2, 5, 11, 4, 5, 8, 4, 5, 1, 4, 5, 7, 3, 5, 11, 1,

		// Test program bound checking and add border in the process

		//   Uncomment next line when ready to test out of bounds checking
		1, 5, 100, 2, 4, 5, 100, 4, 5, 100, 4, 5, 100, 4, 5, 100, 4, 5, 100,

		1, 6, 9 }; // finish off


	// Invoke function which will execute commands
	turtleDraw(commands);

	// Time to go home
}

// turtleDraw() - function responsible for executing commands
void turtleDraw(const int cmds[])
{
	// turtle starts at position 0,0
	int currentTurtlePosition[] = { STARTING_ROW, STARTING_COL };
	// turtle starts with pen face down
	short penPosition = STARTING_PEN_POSITION;
	// turtle starts with direction facing south
	enum Dirs turtleDirection = STARTING_DIRECTION;

	// initialize array of floors NROWS by NCOLS with zeros
	short floor[NROWS][NCOLS] = { {0}, {0} };

	int i = 0;
	int numOfMoves = 0;

	enum TCmnds endOfData = END_OF_DATA;

	while (cmds[i] != endOfData)
	{
		switch (cmds[i])
		{
			case 1:	// pen up
				penPosition = FALSE;
				break;
			case 2: // pen down
				penPosition = TRUE;
				break;
			case 3:	// turn right
			case 4: // turn left
				turtleDirection = getTurtleDirection(turtleDirection, cmds[i]);
				break;
			case 5: // move forward by some number

				numOfMoves = cmds[i + 1];	// number of moves are given in next value.
				++i;						// becuase we have read 2 values

				moveTurtle(floor, numOfMoves, turtleDirection, penPosition, currentTurtlePosition, &currentTurtlePosition[1]);
				break;
			case 6: // display floor
				displayFloor(floor);
				break;
			default:
				puts("Error. Unexpected case in switch statement. ");
				break;
		}

		// increment i to pick next command
		++i;
	}
}

// moveTurtle() - responsible for moving the turtle on the floor and modifying floor if pen is down.
// This function is passed pointers to row and col because they need to be passed by reference
//      because this function must update the row and col when moving turtle. Note that 
//      floor is also passed by reference, but because anarry name is a pointer, the array
//      is automatically passed by reference.
void moveTurtle(short floor[][NCOLS], const int numOfMoves, const enum Dirs currDir, const short penPos, int* rowPtr, int* colPtr)
{
	for (int i = 0; i < numOfMoves; ++i)
	{
		if (penPos)
		{
			++floor[*rowPtr][*colPtr];		// increment the value at position pointed by rowPtr and colPtr
		}

		if (currDir == EAST)
		{
			// if there is room to increment without going out the bounds
			if (*colPtr < NCOLS - 1)
			{
				++(*colPtr);				// increment the position represented by column pointer
			}
		}
		else if (currDir == WEST)
		{
			if (*colPtr > STARTING_COL)
			{
				--(*colPtr);
			}
		}
		else if (currDir == SOUTH)
		{
			if (*rowPtr < NROWS - 1)
			{
				++(*rowPtr);
			}
		}
		else if (currDir == NORTH)
		{
			if (*rowPtr > STARTING_ROW)
			{
				--(*rowPtr);
			}
		}	
	}
}// end of moveTurtle()

// Responsible for displaying the floor
void displayFloor(const short floorSurface[][NCOLS])
{
	//puts("Inside displayFloor\n\n");

	for (int i = 0; i < NROWS; ++i)
	{
		for (int j = 0; j < NCOLS; ++j)
		{
			//printf("i = % d; j = %d\n", i, j);
			if (floorSurface[i][j])
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		puts("");	// new line after every row
	}
} // end of displayFloor()

// Responsible for figuring out and returning the turtleDirection
enum Dirs getTurtleDirection(enum Dirs currentTurtleDirection, int cmd)
{
	enum Dirs newDirection = currentTurtleDirection;

	if (cmd == TURN_RIGHT)
	{
		newDirection = ++currentTurtleDirection;
	}
	else
	{
		newDirection = --currentTurtleDirection;
	}

	if (newDirection == END_VALUE)
	{
		newDirection = NORTH;
	}
	else if (newDirection == BEGIN_VALUE)
	{
		newDirection = WEST;
	}

	return newDirection;
}