/*
Name:			Brian Jones
Assignment:		Extra Credit 01
Date:			2012-02-25

	This program will prompt the user for a targetSum integer, and then determine all 
	possible sequential-integer combinations whose sums equal the target sum.  It will 
	then output those combinations to the screen.
*/


#include <stdio.h>
void getSeries();					// dedicated procedure to process integer combinations
int targetSum;						// global variable targetSum

void main()
{
	printf("Enter target sum:  ");	// ask for target sum
	scanf("%d", &targetSum);		// store target sum
	getSeries();					// Find all the combinations of sequential 
									// integers whose sum = targetSum
}


void getSeries()
{
	// Determines the first and last integers in EVERY series of positive, 
	// consecutive INTEGERS whose sum is the target sum.
	int firstNum, lastNum, runningTotal;
	
	for (firstNum=1; firstNum < targetSum; firstNum++)	// First Number
	{
		lastNum=firstNum+1;					// Last Number = (First Number + 1)
		runningTotal=firstNum+lastNum;		// runningTotal = (First Number + Last Number)
		
		while (runningTotal<targetSum)		// while more last numbers...
		{
			lastNum++;						// ...Increment Last Number
			runningTotal+=lastNum;			// ...Add Last Number to RunningTotal
		}

///////////////////////////////////////////////////////////////////////////////////////////
//////////////// RunningTotal is now EQUAL-TO or GREATER-THAN targetSum ///////////////////
///////////////////////////////////////////////////////////////////////////////////////////

		if (runningTotal == targetSum)			// If runningTotal is EQUAL-TO targetSum...
			printf("%d...%d\n", firstNum, lastNum);	// ...output numbers to the screen
	}
}