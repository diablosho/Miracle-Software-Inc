/**
Name:  			Brian Jones
Assignment:     Chapter 4
Date: 			2011-10-03
Course:         CIS 111
Instructor:     Prof. Mummaw

This program will calculate daily income, as well as keep a running total for a user-defined number of days to accumulate
The formula for the loop is (Total Pennies + 2^(Current Day))/100

Output 1: Enter how many days to calculate:  4
Day 1:  You have earned $0.01 today, netting you $0.01!
Day 2:  You have earned $0.02 today, netting you $0.03!
Day 3:  You have earned $0.04 today, netting you $0.07!
Day 4:  You have earned $0.08 today, netting you $0.15!

Output 2:  Enter how many days to calculate: 5
Day 1:  You have earned $0.01 today, netting you $0.01!
Day 2:  You have earned $0.02 today, netting you $0.03!
Day 3:  You have earned $0.04 today, netting you $0.07!
Day 4:  You have earned $0.08 today, netting you $0.15!
Day 5:  You have earned $0.16 today, netting you $0.31!

Output 3: Enter how many days to calculate: 6
Day 1:  You have earned $0.01 today, netting you $0.01!
Day 2:  You have earned $0.02 today, netting you $0.03!
Day 3:  You have earned $0.04 today, netting you $0.07!
Day 4:  You have earned $0.08 today, netting you $0.15!
Day 5:  You have earned $0.16 today, netting you $0.31!
Day 6:  You have earned $0.32 today, netting you $0.63!
*/

import java.util.Scanner;		// package for Data Input
import java.text.DecimalFormat;	// package for formatting decimals
class PenniesForPay
{
	public static void main(String[] args)
	{
		Scanner dataInput = new Scanner (System.in);			// Data input object
		DecimalFormat floatToDollars = new DecimalFormat("$#0.00");	// Format Decimal to Dollars.

		int lastDay=0;			// Variable for how many days to calculate
		float totalPennies=0.0F;		// Variable for the running total of accumulated daily income
		System.out.println ("This program will calculate how much money you will have after a user-defined number of days, if you start"+
			 																						"with one penny a day"+", and your income doubles each day");
		System.out.println("Enter how many days to calculate:  ");
		lastDay = dataInput.nextInt();		// Input total number of days to calculate income for
		
		for (int day=0; day < lastDay;  day++)		// loop day from "0", inc. once per iteration, until equal to total # of days to calculate
		{
			totalPennies+=(Math.pow(2, day)*.01);		// add the daily income to the running total
			System.out.println("Day " + (day +1) + ":  You have earned " +  floatToDollars.format((Math.pow(2, day)*.01)) +  " today, "+
																									"netting you " + floatToDollars.format(totalPennies) + "!");
		}
	}
}
		
