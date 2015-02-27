/*
Name:	Brian Jones
Date:	2012-03-10
Assignment:	Chapter 4 Part 2, #2

	This program will input an unknown number of integers from the user (less than 100), 
	and after a sentinel value of 101 or 0 are input, it will find the smallest integer 
	entered, and output each integer between the smallest and the largest integer entered.
*/

#include <stdio.h>							// Used for scanf()/printf() functions
#include <stdlib.h>							// Used for system("CLS") function to clear screen

void main()
{
	int pausechar;								// Used to pause console before exit
	int inputNums[100], indexCounter=0;			// Input array and its input quantity
	int inputNumIndex;							// Counter for inputNums[] array
	int smallestInt, largestInt;				// For the smallest/largest input integers

//////////////////////// Prompt User for Integers and store in Variables /////////////////////////

	do
	{
		system("CLS");
		printf("Please enter a series of integers between 1 and 100 inclusive.\n"
		   "Entering a number outside that range will end the input process:  ");

		scanf("%d", &inputNums[indexCounter]);
		
		if (indexCounter==0)						// If this is the first input number...
		{
			smallestInt=inputNums[indexCounter];	// Initialize smallestInt to first input number
			largestInt=inputNums[indexCounter];		// Initialize largestInt to first input number
		}
			
		indexCounter++;								// Increment total number of inputs
		
		if (inputNums[indexCounter-1] <= 100 && inputNums[indexCounter-1] >= 1)	// If Valid Number...
		{
			if (inputNums[indexCounter-1] > largestInt)		// if number is larger than largestInt...
				largestInt=inputNums[indexCounter-1];		// ...set largestInt to new number
			if (inputNums[indexCounter-1] < smallestInt)	// if number is smaller than smallestInt...
				smallestInt=inputNums[indexCounter-1];		// ...set smallestInt to new number
		}
		
	} while (((inputNums[indexCounter-1] >= 1)		&&			// repeat while input is not 0...
			  (inputNums[indexCounter-1] <= 100))	&&			// ...and input is not 101...
			   indexCounter < 100);								// ...and not more than 100 inputs

/////////////// Output all integers between the smallest and largest input integers //////////////

	while (smallestInt <= largestInt)
	{
		printf("%d...", smallestInt);
		smallestInt++;											// Increment counter
	}

	scanf("%d", &pausechar);									// Pause console
}