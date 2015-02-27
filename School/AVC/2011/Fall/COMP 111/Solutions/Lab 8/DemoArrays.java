/*
Name:  			Brian Jones
Assignment:    Chapter 8:  Assignment 12: 2D Array Operations
Date: 			2011-11-21
Course:         CIS 111
Instructor:     Prof. Mummaw
	- This program will create a two-dimensional array, and pass it as an argument to multiple methods in the Arrays class.
	- The returns of those methods are then output to the screen
 */
 
import java.util.Scanner;
import java.text.DecimalFormat;
public class DemoArrays
{
	public static void main (String[] args)
	{
		Scanner dataInput = new Scanner(System.in);
		DecimalFormat output = new DecimalFormat("#0.0#");
		int rowIndex=0;
		int columnIndex=0;

		int[][] userArray = { 																											// Define Array values
										{2, 4, 6, 8},
										{10, 12, 14, 16},
										{18, 20, 22, 24}};
		System.out.println("The total of all values in the array is:  " + 
									output.format(Arrays.getTotal(userArray)) + ".");										// Get total
		System.out.println("The average of all values in the array is:  " + 
									output.format(Arrays.getAverage(userArray)) + ".");								// Get Average
		System.out.println("");

		for (rowIndex=0; rowIndex<userArray.length; rowIndex++)													// Cycle through all rows
		{
			System.out.println("The total of all values in row " + rowIndex + " of the array is:  " + 
										output.format(Arrays.getRowTotal(userArray, rowIndex)) + ".");				// Get RowTotal
			System.out.println("The highest value in row " + rowIndex + " of the array is " + 
										output.format(Arrays.getHighestInRow(userArray, rowIndex)) + ".");		// Get Highest in Row
			System.out.println("The lowest value in row " + rowIndex + " of the array is:  " + 
										output.format(Arrays.getLowestInRow(userArray, rowIndex)) + ".");		// Get Lowest in Row
			System.out.println("");
		}

		for (columnIndex=0; columnIndex<userArray[0].length; columnIndex++)									// Cycle through all columns
			System.out.println("The total of all values in column " + columnIndex + " of the array is:  " + 
										output.format(Arrays.getColumnTotal(userArray, columnIndex)) + ".");		// Get Column Total
		System.exit(0);																													// Release memory
	}
}