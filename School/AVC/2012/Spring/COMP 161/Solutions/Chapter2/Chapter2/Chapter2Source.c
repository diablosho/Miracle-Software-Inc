/*
Name:        Brian Jones
Assignment:  Chapter 2-Exercise 1
		  	 This assignment will input a Fahrenheit temperature 3 different times, and convert each one to Celsius
*/
#include <stdio.h>	// Library for c++ standard input/output functions
int main()
{
	int counter;									// Counter-variable for repetition loop
	float FahrenheitTemp=32.0;						// Variable definition for input temperature

	for (counter=0; counter<3; counter++)			// Repetition loop (3 reps)
	{
		printf("Enter a Fahrenheit temperature to convert to Celsius:  ");
		scanf("%f", &FahrenheitTemp);				// Input temperature to convert
		printf("The converted temperature is:  %f degrees in Celsius \n", 5*(FahrenheitTemp-32)/9);
	}
	scanf("%f", &FahrenheitTemp);
	return 0;
}