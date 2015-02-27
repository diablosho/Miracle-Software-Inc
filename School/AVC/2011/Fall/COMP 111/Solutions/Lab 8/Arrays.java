/*
Name:  			Brian Jones
Assignment:    Chapter 8:  Assignment 12: 2D Array Operations
Date: 			2011-11-21
Course:         CIS 111
Instructor:     Prof. Mummaw
	- This program will create a two-dimensional array, and pass it as an argument to multiple methods in the Arrays class.
	- The returns of those methods are then output to the screen
 */
 
public class Arrays
{
	private static int i=0;													// Index counter
	private static int sum=0;											// Running tally
	private static int numRows=0;										// Number of Rows in Array
	private static int numColumns=0;								// Number of Columns in Array

	public static int getTotal(int[][] ArgArray)			// Returns the sum of all values in ArgArray
	{													
		sum=0;
		numRows=ArgArray.length;
		numColumns=ArgArray[0].length;
		for (i=0; i < numRows; i++)									// Cycle through all rows
			for (int val : ArgArray[i])									// Average each column
				sum+=val;														// Add current array value to sum
		return sum;															// Return array total
	}
	public static double getAverage(int[][] ArgArray)		// Return average of all values inside array
	{
		return (double)getTotal(ArgArray)/(numRows*numColumns);	// Return average of all values
	}
	
	public static int getRowTotal(int[][] ArgArray, int rowIndex)		// Return the total of a specific row in the Array
	{
		int rowTotal=0;
		for (int val : ArgArray[rowIndex])											// Cycle through all of the columns
			rowTotal += val;															// Increment the running tally
		return rowTotal;																// Return the row total
	}
	
	public static int getColumnTotal(int[][] ArgArray, int columnIndex)	// Return the total of a specific column in the Array
	{
		int columnTotal=0;
		for (int rowIndex=0; rowIndex<ArgArray.length; rowIndex++)		// Cycle through all of the rows
			columnTotal += ArgArray[rowIndex][columnIndex];				// Increment the running tally
		return columnTotal;																	// Return the column total
	}
	public static int getHighestInRow(int[][] ArgArray, int rowIndex)	// Returns the highest value in the row
	{
		int highestInRow=0;
		for (int val : ArgArray[rowIndex])											
			if (val > highestInRow)														// If current value > previous maximum
				highestInRow=val;														// store value as new maximum
		return highestInRow;															// Return maximum
	}
	public static int getLowestInRow(int[][] ArgArray, int rowIndex)		// Returns the lowest value in the row
	{
		int lowestInRow=ArgArray[rowIndex][0];								
		for (int val : ArgArray[rowIndex])											
			if (val < lowestInRow)														// If current value < previous minimum
				lowestInRow=val;														// store value as new minimum
		return lowestInRow;																// Return minimum
	}
}