/*	Week 6 Lab 1: identify errors
 *	Your Name:
 *	1. Identify and comment 4 errors
 *	2. E-mail me your corrected file
 *	3. Your e-mail's subject line must contain the following:
 *		CIS113: Week8 Lab exercises.
 **/

import java.util.Scanner;
public class Lab 1
{
	private String currString = " = ";
	private int factorial(int n)
	{
		if (n == 0)
		{
			currString = currString + "0!" ;
			System.out.println(currString);
			return 1;
		}
		else
		{
			currString = currString + n;
			System.out.println(currString + "!");
			currString = currString + " * ";
			return (n * factorial (n - 1));
		}
	}

	public void main(String[] args)
	{
		Scanner conIn = new Scanner(System.in);
		int num, result;
		System.out.print("Enter integer> ");
		num = conIn.nextInt();
		System.out.print(num + "!");
		result = factorial(num);
	}
}