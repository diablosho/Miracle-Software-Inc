/**
Name:  			 Brian Jones
Assignment:	Chapter 3 / Internet Service Provider Part 1 (assignment 13) / Part 2 (assignment 14)
Date:  			   2011-09-26
Course: 			 CIS 111
Instructor:		Prof. Mummaw
    This program:
       - Step One:  Ask the user for the letter of their ISP Subscription package, convert it to Uppercase, and store it in (char packageLetter)
       - Step Two: Ask the user for the total number of hours used for the month, and store in totalHours
       - Step Three: Calculate additional hours for packages A and B, and store in extraHoursA/B
       - Step Four: Calculate the cost of any additional hours in packages A and B, and store in extraHoursCostA/B
       - Step Five:  Calculate the totalPackageCostA/B by adding extraHoursCostA/B to the packagePriceA/B
       - Step Six:  Define monthlyBill with totalPackageCostA/B/C to simplify output methods
       - Step Seven:  Output monthlyBill, formatted with floatToDollars to show two decimal places.
       - Step Seven (Assignment 14):  Determine if there are savings to be found by switching to a different package letter.
       					- If yes, output the cost savings with the other packages, formatted to show two decimal places
       					- If not, do not output anything
 */

import java.util.Scanner;							// Provides for the usage of user-input methods
import java.text.DecimalFormat;				   // Provides for the formatting of decimals into Dollars;
public class InternetServiceProvider			// Class Header
{
	public static void main (String[] args)		// Main Function
	{
		Scanner dataInput = new Scanner(System.in);						   // Points to a new Scanner object, allowing for dataInput methods to be used
		DecimalFormat floatToDollars = new DecimalFormat("#0.00");	// Points to a new DecimalFormat object, formatting (floats) to Dollars
		final float packagePriceA = 9.95F;											// Define package A price
		final float packagePriceB = 13.95F;										// Define package B price
		final float packagePriceC = 19.95F;										// Define package C price
		final float packageAdditionalA = 2.00F;									// Define the price for additional hours in package A
		final float packageAdditionalB = 1.00F;									// Define the price for additional hours in package B
		final int packageHoursIncludedA = 10;								   // Define the hours included in package A
		final int packageHoursIncludedB = 20;									  // Define the hours included in package B
		char packageLetter = ' ';														  // User-defined variable for the package letter
		int totalHours = -1;																  // User-defined variable to hold the hours used
		int packageHoursA = 0;													     // Calculated hours included in package A
		int packageHoursB = 0;													      // Calculated hours included in package B
		float extraHoursA = 0.00F;												     // Calculated additional hours with package A
		float extraHoursB = 0.00F;												      // Calculated additional hours with package B
		float extraHoursCostA = 0.00F;										      // Calculated cost of package A's additional hours
		float extraHoursCostB = 0.00F;										      // Calculated cost of package B's additional hours
		float totalPackageCostA = 0.00F;										    // Calculated total cost of package A
		float totalPackageCostB = 0.00F;										     // Calculated total cost of package B
		float totalPackageCostC = 0.00F;										    // Calculated total cost of package C
		float monthlyBill = 0.00F;												       // General variable to hold the total package cost.
		
		System.out.println("This program will calculate the user's Internet Services Bill");				// Output main purpose of program
		while (packageLetter != 'A' && packageLetter != 'B' && packageLetter != 'C')		 // Make sure the letter input is either 'A', 'B', or 'C'
		{
			System.out.print("Enter Subscription Package Letter:  ");											// Ask user for subscription package letter
			packageLetter = dataInput.next().charAt(0);																// Input package letter from user
			packageLetter = Character.toUpperCase(packageLetter);											   // Convert package letter to upper case
		}
		while (totalHours < 0)																		// Error Control:  Keep asking until totalHours are >= 0
		{
			System.out.print("Enter total hours used:  ");															// Prompt the user for the total hours used
			totalHours = dataInput.nextInt();																				// Input total hours used
		}
		
		// Populate extra hours variables
		extraHoursA = totalHours - packageHoursIncludedA;								// Calculate how many extra hours in package A were used
		extraHoursB = totalHours - packageHoursIncludedB;								// Calculate how many extra hours in package B were used
		if (extraHoursA > 0)																 // If there were extra hours present in package A, calculate their cost
			extraHoursCostA = extraHoursA * packageAdditionalA;										
		if (extraHoursB > 0)																// If there were extra hours present in package B, calculate their cost
			extraHoursCostB = extraHoursB * packageAdditionalB;								 			  
			
		// Populate total package cost variables
		totalPackageCostA = packagePriceA + extraHoursCostA;	// totalPackageCostA = (monthly price+total cost of the extra hours)
		totalPackageCostB = packagePriceB + extraHoursCostB;	  // totalPackageCostB = (monthly price+total cost of the extra hours)
		totalPackageCostC = packagePriceC;									  	// Determine the total cost of package C
		
		// Populate monthly bill variable
		if (packageLetter == 'A')
			monthlyBill = totalPackageCostA;										// Define monthlyBill as totalPackageCostA if packageLetter was 'A'
		else if (packageLetter == 'B')
			monthlyBill = totalPackageCostB;										// Define monthlyBill as totalPackageCostB if packageLetter was 'B'
		else if (packageLetter == 'C')
			monthlyBill = totalPackageCostC;										// Define monthlyBill as totalPackageCostC if packageLetter was 'C'
		System.out.println("Your monthly bill is:  $" + floatToDollars.format(monthlyBill) + "");						// Output packageCost
		
		// Determine savings with other package costs
		if (monthlyBill - totalPackageCostA > 0)			// Could have saved x amount of money by switching to package A
			System.out.println("You could have saved $" + (floatToDollars.format(monthlyBill - totalPackageCostA)) 
																													+ " by switching to package A");
		else if (monthlyBill - totalPackageCostB > 0)			// Could have saved x amount of money by switching to package B
			System.out.println("You could have saved $" + (floatToDollars.format(monthlyBill - totalPackageCostB)) 
																													+ " by switching to package B");
		else if (monthlyBill - totalPackageCostC > 0)			// Could have saved x amount of money by switching to package C
			System.out.println("You could have saved $" + (floatToDollars.format(monthlyBill - totalPackageCostC)) 
																													+ " by switching to package C");
	}
}