/**
This program determines fuel economy based on given data from the user
Name:  			Brian Jones
Assignment:     Chapter 2
Date: 			2011-09-19
Course:         CIS 111
Instructor:     Prof. Mummaw

Miles Driven	Gallons Used	MPG (Hand Calculated)				MPG (Resulting Output)
2000					100						20 mpg                              			  20.0 mpg
500						 25.5					 19.6 mpg                           			  19.607843 mpg
241.5					10					     24.15 mpg                           			 24.15 mpg
100					     0					       Error: Division by Zero            	  0.0 mpg (error-controlled)

Output #1:                                                                   												Output #2:
This program will calculate your gas mileage based on calculated metrics     This program will calculate your gas mileage based on calculated metrics
Enter the miles driven on your last tank of gas:                             						Enter the miles driven on your last tank of gas: 
2000                                                                        													  500
Enter the total gallons of gasoline used from your last tank:                			  Enter the total gallons of gasoline used from your last tank:  
100                                                                          													   25.5
You averaged 20.0 miles/gallon on your last tank of gasoline!                		   You averaged19.607843 miles/gallon on your last tank of gasoline!

Output #3:                                                                   												 Output #4:
This program will calculate your gas mileage based on calculated metrics     This program will calculate your gas mileage based on calculated metrics
Enter the miles driven on your last tank of gas:                             						Enter the miles driven on your last tank of gas: 
241.5                                                                        													  100
Enter the total gallons of gasoline used from your last tank:                			  Enter the total gallons of gasoline used from your last tank:  
10                                                                          														 0
You averaged 24.15 miles/gallon on your last tank of gasoline!              		  You averaged 0.0 miles/gallon on your last tank of gasoline!
 */
import java.util.Scanner;                       // To provide functionality allowing input/output
public class Mileage                            // Class header
{
     public static void main(String[] args)     // Main Function
     {
          Scanner dataInput = new Scanner(System.in);             // Create new Scanner variable dataInput for input communication with the user
          System.out.println("This program will calculate your gas mileage based on calculated metrics");   // Display program goals
          System.out.println("Enter the miles driven on your last tank of gas: ");                          // prompt for miles driven on tank and...
          float milesDrivenOnTank = dataInput.nextFloat();                 // populate  milesDrivenOnTank
          System.out.println("Enter the total gallons of gasoline used from your last tank:  ");            // prompt for gallons used and...
          float gallonsUsedFromTank = dataInput.nextFloat();            // populate gallonsUsedFromTank
          float milesPerGallon = 0;                        // declare and initialize  milesPerGallon for later definition
          if (gallonsUsedFromTank > 0)             // error control:  Can't divide by zero, nor can you use less than zero gallons
          {
// If gallonsUsedFromTank is greater than zero:  Divide the number of gallons used by the number of miles driven, and store in milesPerGallon
               milesPerGallon = milesDrivenOnTank / gallonsUsedFromTank;
          }
          // Display the user's average fuel economy in miles/gallon
           System.out.println("You averaged " + milesPerGallon + " miles/gallon on your last tank of gasoline!");
     }
}