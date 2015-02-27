/**
Name:  			Brian Jones
Assignment:    Chapter 6:  Assignment 2: Car-Class Demo Program
Date: 			2011-11-14
Course:         CIS 111
Instructor:     Prof. Mummaw
	- This program will create an object of a custom Car object
	- That Car object will accelerate 5 times, each time displaying the current speed
	- Then that Car object will decellerate 5 times, each time displaying the current speed	
*/
import java.util.Scanner;
public class DemoCar
{
	public static void main(String[] args)
	{
		Scanner dataInput = new Scanner(System.in);													// object for keyboard input
		Car vehicle = new Car(2005, "Chrysler");														// Create Car object
		int i=0;																										// Initialize the loop counter-index
		
		for (i=0; i<5; i++)																							// "For" loop for acceleration
		{
			vehicle.Accelerate();																				// Accelerate the vehicle by 5
			System.out.println("Current Speed:  " + vehicle.GetSpeed() + " mph");			// Output speed
		}
		for (i=0; i<5; i++)																							// "For" loop for decelleration
		{
			vehicle.Brake();																						// Slow the vehicle by 5
			System.out.println("Current Speed:  " + vehicle.GetSpeed() + " mph");			// Output speed
		}		
	}
}