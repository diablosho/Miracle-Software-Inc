/**
Name:  			Brian Jones
Assignment:    Extra Credit 2:  Armstrong/Narcissist Numbers
Date: 			2011-10-03
Course:         CIS 111
Instructor:     Prof. Mummaw

This program will find all four digit numbers whose sum of (individual digits)^4 is equal to the number
*/
import java.util.Scanner;			// Data Input Package

public class NumsEqualSumsFourth
{
	public static void main(String[] args)
	{
		Scanner dataInput = new Scanner(System.in);		// Data Input Object variable
		int seedNumber=1000;		// Initialize the sum number to the smallest four digit number
		int firstNumber, secondNumber, thirdNumber, fourthNumber;	// Variables to hold each individual (digit)^4
		int sumNumbers;	// Variable to hold the sum of each (digit)^4
		float conversionNumber;	// Temporary variable to calculate each individual digit from a single number
		
		while (seedNumber < 10000)		// Loop sum number from 1000 to 9999
		{
			conversionNumber=seedNumber;								// Set the temporary number to the sum number, to perform calculations on
			firstNumber =(int) (conversionNumber * .001);			// First number equals the ConversionNumber*.001, discarding decimals
				conversionNumber -= (firstNumber * 1000);			// Set the temporary number to:  Temporary number - the first number * 1000
			secondNumber = (int)(conversionNumber * .01);		// Second number equals the ConversionNumber * .01, discarding decimals
				conversionNumber -= (secondNumber * 100);		// Set the temporary number to:  Temporary number - the second number * 100
			thirdNumber = (int)(conversionNumber * .1);				// Third number equals the ConversionNumber * .1, discarding decimals
				conversionNumber -= (thirdNumber * 10);				// Set the temporary number to:  Temporary number - the third number * 10
			fourthNumber = (int)(conversionNumber * 1);			// Fourth number equals the ConversionNumber * 1, discarding decimals
				conversionNumber -= (fourthNumber * 1);				// Set the temporary number to:  Temporary number - the fourth number * 1
			sumNumbers =   (int)(Math.pow(firstNumber, 4) + 		// Add first number^4 to...
									(int)Math.pow(secondNumber, 4) + 			//second number^4 to...
									(int)Math.pow(thirdNumber, 4) +			   //third number^4 to...
									 (int)Math.pow(fourthNumber, 4));				//fourth number^4
			if (sumNumbers == seedNumber)				// If the sum of the digits^4 is equal to the sum number, then it is a narcissist number
				System.out.println(seedNumber);		// Output the sum number
			seedNumber++;										// Increment the sum number
		}
	}
}