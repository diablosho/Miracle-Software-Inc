/**
Name:  		Brian Jones
Assignment:	Chapter 2 / NumericTypes
Date:  		2011-09-19
Course: 		CIS 111
Instructor:		Prof. Mummaw
    This program:
       - Calculates the average of 95 and 100
       - Converts 212 degrees F to Celsius
       - Inputs your first and last name separately, then concatenates them into another variable and displays it.
       - Determines and displays your first name's initials
       - Capitalizes your full name
       - Displays your full name and how many letters compose it
       - Calculates the volume of a sphere based on user input
 
Diameter	   Volume (Hand Calculated)	Volume (Resulting Output)
2				      4.1888                                    4.1887902047863905
25.4				8580.2466                			   8580.24625946384
875,000			 350770273496516627.862	   3.5077027349651661E17

 Output #1:                                                                                                                                                  Output #2:
    100 and 95 have an average of 97.5                                                                                                    100 and 95 have an average of 97.5
    212 in Fahrenheit is 100.0 in Celsius.                                                                                                  212 in Fahrenheit is 100.0 in Celsius.
    Enter your first name:                                                                                                                           Enter your first name: 
    Brian                                                                                                                                                        Brian
    Enter your last name:                                                                                                                            Enter your last name: 
    Jones                                                                                                                                                       Jones
    Your full name is:  Brian Jones                                                                                                            Your full name is:  Brian Jones
    B                                                                                                                                                               B 
    BRIAN JONES, there are 11 characters in your full name                             									 BRIAN JONES, there are 11 characters
    																																							      in your full name
    Enter the diameter of a sphere:                                                                                                            Enter the diameter of a sphere: 
    2                                                                                                                                                                25.4
   The volume of a sphere of 2.0 units in diameter is  4.1887902047863905 cubic units                  The volume of a sphere of 25.4 units in 
   																																							       diameter is 8580.24625946384 cubic units
   
Output #3:
    100 and 95 have an average of 97.5
    212 in Fahrenheit is 100.0 in Celsius.
    Enter your first name: 
    Brian
    Enter your last name: 
    Jones
    Your full name is:  Brian Jones
    B 
    BRIAN JONES, there are 11 characters in your full name
    Enter the diameter of a sphere: 
    875000
    The volume of a sphere of 875000.0 units in diameter equals 3.5077027349651661E17 cubic units
 */
import java.util.Scanner;
// import javax.swing.JOptionPane;          
// TASK #2  (Alternate) Add import statment to use JOptionPane class methods, allowing for Message Boxes to interact with the user

public class NumericTypes                                                      // Class Header
{
    public static void main(String[] args)                                 // Main Function
    {
        // Create a variable pointing to a new Scanner object, allowing for dataInput methods to be used
        Scanner dataInput = new Scanner(System.in); 

        final int NUMBER = 2;          			 // number of test scores to average
        final int SCORE1 = 100;						// first test score
        final int SCORE2 = 95;        			   // last test score
        final int BOILING_IN_F = 212;   	  // boiling temperature
        double fToC;         								 // temperature in celsius
        double average;           						 // arithmetic average
        String output;             							 // line of output to print to screen

        // Find an arithmetic average by dividing the float overloaded total of two scores, and dividing by 2
        average = (float) (SCORE1 + SCORE2) / NUMBER;
        // Create output message, including test scores and their average
       output = SCORE1 + " and " + SCORE2 + " have an average of " + average; 
        System.out.println(output);                                                             // Display the output message, showing test scores and their average

        fToC = (BOILING_IN_F - 32.0) * (5.0 / 9.0);                                  // Convert Fahrenheit to Celsius
        // Create output message with Fahrenheit and Celsius boiling point
        output = BOILING_IN_F + " in Fahrenheit is " + fToC + " in Celsius.";
        System.out.println(output);       // Display output message, showing the Boiling Point in Fahrenheit and it's calculated Celsius value
        System.out.println();                   // Display a blank line to separate output from different program objectives

        // Create String variables for the user's first name (firstName), last name (lastName), and the Concatenated fullName
        String firstName, lastName, fullName;
        System.out.println("Enter your first name: ");          			    // ask for user's first name
        firstName = dataInput.nextLine();                                			   // input user's first name and store in firstName
        System.out.println("Enter your last name: ");         			     // ask for user's last name
        lastName = dataInput.nextLine();                              				     // input user's last name and store in lastName
        fullName = firstName.concat(" " + lastName);            			  // Concatenate user's first and last names and store in fullName
        System.out.println("Your full name is:  " + fullName);            // Print the user's full name (fullName)
        System.out.println();                                                              		  // Display a blank line to separate output from different program objectives

/* *  Alternative Method:  Display Dialogue Boxes instead of text prompts to communicate with the user
      // Prompt user for their first name, and store in the variable firstName
      String firstName = JOptionPane.showInputDialog("Enter your first name: ");
      // Prompt user for their last name, and store in the variable lastName
      String lastName = JOptionPane.showInputDialog("Enter your last name: "); 
      // Concatenate user's first name and last name (firstName, lastName) and store in fullName
      String fullName = firstName.concat(" " + lastName);
      // Show Dialogue Message Box displaying the user's full name (fullName)
      JOptionPane.showMessageDialog(null, "Your full name is:  " + fullName);
*/

        char firstInitial = firstName.charAt(0);         // get the first character from the user's first name
        System.out.println(firstInitial + " ");            // print out the user's first initial
        fullName = fullName.toUpperCase();           // convert the user's full name to all capital letters
        // print out the user's full name in all capital letters
        System.out.println(fullName + ", there are " + fullName.length() + " characters in your full name");
        System.out.println();                                       // to separate the output with a blank line
       
        float diameter, radius;                                     // Create the variables for the sphere's diameter and calculated radius
        double volumeSphere;                                   // Create the variable for the sphere's calculate volume
      
        System.out.println("Enter the diameter of a sphere: ");      // Prompt the user for the diameter of a sphere
        diameter = dataInput.nextFloat();      // Input the diameter of a sphere from the user, and store in diameter
        radius = diameter / 2;       // Calculate the radius of the sphere by dividing the diameter by 2
        // Calculate the volume of the sphere by multiplying 4ᴫ * r^3, then dividing by 3.0
        volumeSphere =(4 * Math.PI * Math.pow(radius, 3)) / 3.0;
// JOptionPane.showMessageDialog(null, "The volume of a sphere of "+diameter+" units in diameter is "+volumeSphere+" cubic units");     
// Alt.: display the calculated volume
        System.out.println("The volume of a sphere of " + diameter + " units in diameter is " + volumeSphere + " cubic units");           
        // output the volume to the screen

        // System.exit(0);                    // Used to release memory allocations when utilizing Dialog Boxes and JOptionPane methods
    }
}