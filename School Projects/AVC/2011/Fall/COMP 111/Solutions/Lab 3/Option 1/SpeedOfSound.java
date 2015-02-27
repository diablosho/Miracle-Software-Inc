/**
Name:  			 Brian Jones
Assignment:	Chapter 3 / The Speed of Sound
Date:  			   2011-09-26
Course: 			 CIS 111
Instructor:		Prof. Mummaw
    This program:
       - Calculates the time (float timeForSoundToTravelAcrossDistance) it takes for a sound wave to travel a user-defined distance (float distance) 
       - 		through a user-defined medium: air, water, or steel (String medium).  After calculating the time required, the time will be displayed to the
       -		 screen.
       - Step One:     Ask the user for the type of medium through which the sound wave will be traveling, and store in (String medium)
       - Step Two:    Ask the user for the distance that the sound wave must travel, and store in (float distance)
       - Step Three:  float timeForSoundToTravelAcrossDistance:  If (String medium) is "Air":  Divide (float distance) by its' 
       -					 speed constant (1100 fps-->final int mediumAirFPS))
       - Step Four:    float timeForSoundToTravelAcrossDistance:  If (String medium) is "Water":  Divide (float distance) by its' 
       - 					 speed constant (4900 fps-->final int mediumAirFPS))
       - Step Five:     float timeForSoundToTravelAcrossDistance:  If (String medium) is "Steel":  Divide (float distance) by its' 
       -					 speed constant (16400 fps-->final int mediumAirFPS))
       - Step Six:        Output "Sound waves will travel " + (float distance) + " feet through " + (String medium) + " in " + 
       - 					 float (timeForSoundToTravelAcrossDistance) + " seconds!"
       
Output 1:  
This program will determine how long it will take for a sound wave to travel a user-defined distance through a user-defined medium
Enter the medium for the sound waves to travel through (air, water, or steel):  
air
Enter the distance the sound waves must travel (in feet):  
25
Sound waves will travel 25 feet through air in 0.022727273 seconds!

Output 2:
This program will determine how long it will take for a sound wave to travel a user-defined distance through a user-defined medium
Enter the medium for the sound waves to travel through (air, water, or steel):  
Water
Enter the distance the sound waves must travel (in feet):  
80
Sound waves will travel 80 feet through Water in 0.01632653 seconds!

Output 3:
This program will determine how long it will take for a sound wave to travel a user-defined distance through a user-defined medium
Enter the medium for the sound waves to travel through (air, water, or steel):  
STEEL
Enter the distance the sound waves must travel (in feet):  
1500
Sound waves will travel 1500 feet through STEEL in 0.09146342 seconds!
*/

import java.util.Scanner;											// Provides for the usage of user-input methods
import java.text.DecimalFormat;								   // Provides for the formatting of distance to a zero decimal number when necessary
public class SpeedOfSound										// Class Header
{
	public static void main (String[] args)						// Main Function
	{
		Scanner dataInput = new Scanner(System.in);		// Points to a new Scanner object, allowing for dataInput methods to be used
		DecimalFormat floatToTime = new DecimalFormat("#0.##");	// Points to a new DecimalFormat object, formatting distance to 0 decimals if necessary
		String medium = "";							// Create/Initialize a variable holding the user-defined medium through which the sound wave will travel
		float distance=0F;									// Create a variable holding the user-defined distance for the sound wave to travel
		final int mediumAirFPS = 1100;					// Assign a variable to hold the speed constant of sound waves travelling through an Air medium
		final int mediumWaterFPS = 4900;				// Assign a variable to hold the speed constant of sound waves travelling through a Water medium
		final int mediumSteelFPS = 16400;					// Assign a variable to hold the speed constant of sound waves travelling through a Steel medium
		float timeForSoundToTravelAcrossDistance=0F;		// Assign a variable for the time for a sound wave to travel a distance through the medium
		
		// Output main purpose of program
		System.out.println("This program will determine how long it will take for a sound wave to travel a user-defined distance through a user-defined" +
									medium + "");

		// Error Control loop (must be air, water, or steel to continue)
		while (!(medium.equalsIgnoreCase("air") || medium.equalsIgnoreCase("water") || medium.equalsIgnoreCase("steel")))	
		{
					System.out.println("Enter the medium for the sound waves to travel through (air, water, or steel):  ");	// Prompt user to enter the medium
					medium = dataInput.nextLine();																										// Input medium from user
		}
		
		System.out.println("Enter the distance the sound waves must travel (in feet):  ");			// Prompt user for distance
		distance = dataInput.nextFloat(); 																				// Input distance from user
		
		if (medium.equalsIgnoreCase("air"))	// if medium = "air", timeForSoundToTravelAcrossDistance = distance / its speed constant (1100)
			timeForSoundToTravelAcrossDistance = distance / mediumAirFPS;		
		if (medium.equalsIgnoreCase("water"))	// if medium = "water", timeForSoundToTravelAcrossDistance = distance / its speed constant (4900)
			timeForSoundToTravelAcrossDistance = distance / mediumWaterFPS;
		if (medium.equalsIgnoreCase("steel"))	// if medium = "steel", timeForSoundToTravelAcrossDistance = distance / its speed constant (16400)
			timeForSoundToTravelAcrossDistance = distance / mediumSteelFPS;
		
		// Output (distance) travelled through (medium) in (timeForSoundToTravelAcrossDistance) seconds
		System.out.println("Sound waves will travel " + floatToTime.format(distance) + " feet through " + medium 
									+ " in " + floatToTime.format(timeForSoundToTravelAcrossDistance) + " seconds!");
	}
}