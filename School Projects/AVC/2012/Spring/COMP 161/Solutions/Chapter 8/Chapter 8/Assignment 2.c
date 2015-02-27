/*	NAME:		BRIAN JONES
	DATE:		04/30/2012
	PROJECT:	CHAPTER 8, ASSIGNMENT 2
	COURSE:		CIS-161


	This program will create a "magic square" of user-defined size.  The program will prompt the user for the
	size of the magic square.  It will then populate the two-dimensional array representing the magic-square
	(starting at row 0, column 3) with consecutive integers from 1 to the (user-defined size^2).  After 
	placing each number, the position in the array will move higher and to the right on the square.  If the 
	number placed is evenly divisible by the size of the square, the position will go down one row, and 
	proceed again.  It will continue this process until all positions are filled.

	EXAMPLE:	17	24	01	08	15
				23	05	07	14	16
				04	06	13	20	22
				10	12	19	21	03
				11	18	25	02	09
*/

#include <stdio.h>

void populateSquare(int squareArray[99][99], int squareSize);
void printSquare(int squareArray[99][99], int squareSize);
void initializeArray(int squareArray[99][99], int squareSize);

void main()
{
	int magicSquareArray[99][99];							// array storing the magic-square
	int magicSquareSize=0;									// initialize the size of the magic-square to 0
	int currentRow = 0, currentCol = 0;						// initialize the current Row and Column to 0
	int rowIndex = 0, colIndex = 0;							// initialize the Row index and Column index to 0
	int counter;											// declare the loop-counter variable

	printf(	"This program creates a magic square of a specified size."
			"The size must be an odd number between 1 and 99.\n"
			"Enter size of magic square:  ");				// prompt the user for the magic-square size
	scanf("%d", &magicSquareSize);							// input the magic-square size from the user
	
	initializeArray(magicSquareArray, magicSquareSize);		// initialize the magic-square array
	populateSquare(magicSquareArray, magicSquareSize);		// fill in the magic-square
	printSquare(magicSquareArray, magicSquareSize);			// display the magic-square
	scanf("%d", &magicSquareSize);							// delay console termination for printing
}

void initializeArray(int squareArray[99][99], int squareSize)		// fill all positions with zeros
{
	int currentRow, currentCol;
	for (currentRow = 0; currentRow < 99; currentRow++)				// Cycle through all rows sequentially
		for (currentCol = 0; currentCol < 99; currentCol++)			// Cycle through all columns sequentially
			squareArray[currentRow][currentCol] = 0;				// Initialize current position to 0
}

void populateSquare(int squareArray[99][99], int squareSize)		// Fill in all positions of the square
{
	int counter, currentRow, currentCol;
	
	for		(counter = 1, currentRow = 0, currentCol = squareSize/2;// Start at row 0, 1/2 across
			counter <= (squareSize * squareSize); counter++)		// Repeat until all positions are full
	{
		squareArray[currentRow][currentCol]=counter;				// Fill in current square-position
	
		if (counter % squareSize == 0)								// if current number is evenly divisible by
		{															// square size...
			currentRow++;											// ...move down one row
			if (currentRow > squareSize - 1)						// if current row is out-of-bounds...
				currentRow = 0;										// ...move to row 0
		}
		else														// if current number is not divisible by
		{															// square size...
			currentRow--;											// ...move up one row
			currentCol++;											// ...move right one column
			if (currentRow < 0)										// if current row is out-of-bounds...
				currentRow = squareSize - 1;						// ...move to bottom of square
			if (currentCol > squareSize - 1)						// if current column is out-of-bounds...
				currentCol = 0;										// ...move to left side of square
		}
	}
}

void printSquare(int squareArray[99][99], int squareSize)		// Displays the magic-square
{
	int rowIndex, colIndex;
	for (rowIndex = 0; rowIndex <= squareSize-1; rowIndex++)	// Cycle through all rows sequentially
	{
		for (colIndex = 0; colIndex <= squareSize-1; colIndex++)// Cycle through all columns sequentially
			printf("%d	", squareArray[rowIndex][colIndex]);	// Output the number at the current position
		printf("\n");											// Once finished with columns, move to new line
	}
}