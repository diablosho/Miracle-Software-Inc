/*
Name:  Brian Jones
Date:  2012-03-10
Assignment:  Chapter 5, Assignment #1

	This program will repeatedly prompt the user for integer input, and then determine if that input is
	a prime number or not.  It will then output the result of the isPrime() function, informing the user
	if the number they entered is a prime number or not.  This will continue until the user enters "-1",
	which is the sentinel value reserved for program termination.  Once the sentinel value is entered, 
	the program will terminate.
*/
#include <stdio.h>							// Included for printf()/scanf() functions

int isPrime(int number);					// Declare function prototype globally across entire program

void main()									// Main function
{
	int input=0;							// Initialize user input to zero
	while (input != -1)						// While input integer is not -1, which is the sentinel value
	{
		printf("Please enter an integer (-1 to exit):  ");
		scanf("%d", &input);								// Store input integer in variable "input"
		if (isPrime(input) == 0)							// if function returns 0, then # not prime
			printf(" ...Not a Prime Number\n");
		else												// ...else # is prime
			printf(" ...Prime Number\n");
	}
	scanf("%d", &input);
}

int isPrime(int number)			// Function for determining primal-nature of integer inputs passed as arg.
{
	int isPrimeNum=1;											// Assume it is Prime, until proven otherwise
	int loopCounter;											// Loop Counter to try every number
	for (loopCounter=2; loopCounter < number; loopCounter++)	// Test all numbers (2 to input-num)...
		if (number % loopCounter == 0)							// If (number % loopCounter) is evenly divisible
			isPrimeNum = 0;										// ...set isPrimeNum to 0 (Not Prime)
	return isPrimeNum;											// Return 1 if PRIME, 0 if NOT PRIME.
}