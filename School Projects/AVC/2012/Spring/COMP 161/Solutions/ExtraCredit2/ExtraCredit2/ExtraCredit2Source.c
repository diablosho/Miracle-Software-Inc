/*
Name:		Brian Jones
Date:		2012-02-25
Assignment:	Extra Credit 02

	This program will find all narcissist numbers (between 1000 and 10000),
	and then output them to the screen.

	Narcissist numbers are numbers in which each individual digit, when raised to
	the nth power (n = number of digits in number), and added to each other, equal
	the overall	number.
*/
#include <stdio.h>									// Header file for std input/output
#include <stdlib.h>									// Header file for _itoa function
#include <math.h>									// Header file for pow function

void main()											// main procedure
{
	char charBuffer[5];								// Buffer for ASCII representation of number
	int digitCounter, currentNum, sumIndividualDigits;	// Variables for data
	
	for (currentNum=1000; currentNum<10000; currentNum++)	// loop through all possible numbers
	{
		sumIndividualDigits=0;				// Reset the sum of individual digits
		_itoa(currentNum, charBuffer, 10);	// Convert number to ASCII and store in char array
		
///////////////////////////////////////////////////////////////////////////////////////////
///////////////// Run through each digit in number, and raise to nth power ////////////////

		for (digitCounter=0; digitCounter < 4; digitCounter++)
			sumIndividualDigits+=pow((double)(charBuffer[digitCounter]-0x30), 4);

//////////////////////// Calculations on current number finished //////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
		
		if (currentNum == sumIndividualDigits)	// If currentNum is EQUAL-TO sumIndividualDigits
			printf("%d\n", currentNum);			// ...Output current number to the screen
	}
}