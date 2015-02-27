/**
Name:  			Brian Jones
Assignment:    Extra Credit 1:  Integer Series
Date: 			2011-10-03
Course:         CIS 111
Instructor:     Prof. Mummaw

-  This program will prompt the user for a target sum, and pass that sum to the IntegersAdding method
-  The IntegersAdding method will then run a loop through every possible integer from 0 to the target sum, 
	adding the current integer to the running total
-  When the target sum is reached, if the running total is equal to the target sum, then the first and last number 
	of that series is output to the screen
*/

import java.util.Scanner;		// Data Input Package
public class IntegersAdding
{
	public static void getSeries(int targetSum)	// Method that processes all possible combinations of summed integers that equal targetSum
	{
		int firstInt=0;		// First number of potential series
		int mainLoopCounter=0;	// Determine the first number of each loop iteration
		int experimentalSum=0;	// Running total of the sums of each integer in the series of each loop iteration
		int numberToAdd=0;	// Number to add to the experimental sum
		
		while (mainLoopCounter <= targetSum)	// While the first number is less than the target sum, 
																   //  there are further potential series possibilities
		{
			mainLoopCounter++;		// Increment main loop counter
			firstInt++;					  // Increment first number of potential series
			experimentalSum=firstInt;	// Add the first number to the running total of the loop iteration
			numberToAdd = firstInt+1;	// Set the second number
			while (experimentalSum < targetSum)		// Go through all integers added together until >= targetSum;  then start over
			{
				experimentalSum += numberToAdd;		// Add the next integer to the running total
				if (experimentalSum == targetSum)			//  If the running total is equal to the target sum
				{
					System.out.println(firstInt + "..." + numberToAdd);		// Output the current series' first and last integers
				}
				numberToAdd ++;		// increment combination Counter
			}
		}
	}
	public static void main(String[] args)
	{
		int targetSum=0;		// Initialize the target sum variable to zero
		Scanner dataInput = new Scanner(System.in);		// Data Input object
		
		System.out.print("Enter target sum:  ");		// Prompt user for target sum
		targetSum = dataInput.nextInt();					//  Input target sum from user
			
		getSeries(targetSum);	//  Determine all possible combinations of integer series' that, when summed,  equal the target sum
	}
}