/**
Name:  			Brian Jones
Assignment:    Chapter 5:  Assignment 8:  Conversion Program
Date: 			2011-10-03
Course:         CIS 111
Instructor:     Prof. Mummaw
	This program will input a user-defined distance (meters), and prompt for a metric unit to convert it to (kilometers, inches, or feet)
*/
import java.util.Scanner;							// Data Input Package
import java.text.DecimalFormat;					// Decimal Formatting Package

public class ConversionProgram
{
	public static void main (String[] args)			// Main procedure
	{
		Scanner dataInput = new Scanner(System.in);						// Data Input object variable
		DecimalFormat floatToInt = new DecimalFormat("#0.##");		// Decimal Formatting variable
		float distance=0.00F;														// Variable to hold distance input
		int selection=0;																// Variable to hold selection

		do			// Ask user for distance in meters until...
		{
			System.out.print("Enter a distance in meters:  ");
			distance = dataInput.nextFloat();									// Store distance (meters) in variable "distance"
		} while (distance < 0);		// until response is non-negative

		while (selection != 4)		// While menu selection is not "Exit"
		{
			do		// Show menu until selection chosen is within an acceptable range
			{
				menu();											// Display the menu
				selection = dataInput.nextInt();		// Get Menu selection
				if (selection < 1 || selection > 4)			// If invalid selection, display error message
					System.out.println("Invalid selection.  Try again.");		// Error message
			} while (selection < 1 || selection > 4); // Keep asking for menu selection until valid response is given
		
			switch (selection)
			{
				case 1:  showKilometers(distance);		break;		// If selection=1, convert to Kilometers
				case 2:  showInches(distance);			break;	// If selection=2, convert to Inches
				case 3:  showFeet(distance);				break;		// If selection=3, convert to Feet
				case 4:  break;												// If selection=4, exit program
			}
		}
	}
	
	public static void menu()																	// Procedure to display menu options
	{
		System.out.println("Enter your selection:  ");
		System.out.println("1.  Convert to Kilometers");
		System.out.println("2.  Convert to Inches");
		System.out.println("3.  Convert to Feet");
		System.out.println("4.  Quit the program");
	}
	
	public static void showKilometers(float distanceMeters)		// Procedure to convert distance to kilometers
	{
		DecimalFormat floatToInt = new DecimalFormat("#0.##");
		System.out.println("Distance (kilometers):  " + floatToInt.format(distanceMeters*.001F));		//meters*.001
	}
	
	public static void showInches(float distanceMeters)			// Procedure to convert distance to Inches
	{
		DecimalFormat floatToInt = new DecimalFormat("#0.##");
		System.out.println("Distance (inches):  " + floatToInt.format(distanceMeters*39.37F));		//meters*39.37
	}
	
	public static void showFeet(float distanceMeters)				// Procedure to convert distance to Feet
	{
		DecimalFormat floatToInt = new DecimalFormat("#0.##");
		System.out.println("Distance (feet):  " + floatToInt.format(distanceMeters*3.281F));			//meters*3.281
	}
}