/**
Name:  			Brian Jones
Assignment:     Chapter 4 Part 1:  #10:  Largest and Smallest
Date: 			2011-10-03
Course:         CIS 111
Instructor:     Prof. Mummaw

This program will prompt the user for an infinite series of numbers, and after receiving "-99" as an input, it will
	determine the lowest number, as well as the highest number, that was inputted from the user
*/
import java.util.Scanner;
class LargestAndSmallest
{
	public static void main (String[] args)
	{
		int lowestNumber=0;
		int highestNumber=0;
		int inputNumber = 0;
		Scanner dataInput = new Scanner(System.in);
		
		while (inputNumber != -99)	// While input number is not the sentinel value -99
		{
			System.out.print("Enter a number to compare (-99 to finish):  ");
			inputNumber = dataInput.nextInt();
			
			if ((lowestNumber==0 && inputNumber != -99) || (inputNumber < lowestNumber && inputNumber != -99))
				lowestNumber=inputNumber;
			if ((highestNumber==0 && inputNumber != -99) || (inputNumber > highestNumber && inputNumber != -99))
				highestNumber=inputNumber;
		}
		System.out.println ("The lowest number was:  " + lowestNumber + ", and the highest number was:  " + highestNumber);
	}
}