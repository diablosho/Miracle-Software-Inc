/**
 * @(#)DaysBetween.java
 *
 * DaysBetween application
 *
 * @author
 * @version 1.00 2012/2/5
 */

import java.util.Scanner;

public class DaysBetween
{
	public static void main(String[] args)
	{
		Scanner conIn = new Scanner(System.in);
		int day, month, year;
		String more;

		do
		{
			more = null;
			System.out.println("Enter two 'modern' dates: month day year");
			System.out.println("For example, January 12, 1954 would be: 1 12 1954");
			System.out.println();
			System.out.println("Modern dates occur after " + Date.MINYEAR + ".");
			System.out.println();
			System.out.println("Enter the first date: ");

			if (conIn.hasNextInt()) month = conIn.nextInt();
			else
			{
				System.out.println("Illegal input was entered");
				return;
			}
			if (conIn.hasNextInt()) day = conIn.nextInt();
			else
			{
				System.out.println("Illegal input was entered");
				return;
			}
			if (conIn.hasNextInt()) year = conIn.nextInt();
			else
			{
				System.out.println("Illegal input was entered");
				return;
			}

			Date date1 = new Date(month, day, year);
			System.out.println("Enter the second date: ");
			if (conIn.hasNextInt()) month = conIn.nextInt();
			else
			{
				System.out.println("Illegal input was entered");
				return;
			}
			if (conIn.hasNextInt()) day = conIn.nextInt();
			else
			{
				System.out.println("Illegal input was entered");
				return;
			}
			if (conIn.hasNextInt()) year = conIn.nextInt();
			else
			{
				System.out.println("Illegal input was entered");
				return;
			}
			Date date2 = new Date(month, day, year);
			if ((date1.getYear() <= Date.MINYEAR)
				||
				(date2.getYear() <= Date.MINYEAR))
				System.out.println("You entered a 'pre-modern' date.");
			else
			{
				System.out.println("The number of days between ");
				System.out.println(date1);
				System.out.println(" and ");
				System.out.println(date2);
				System.out.println(" is ");
				System.out.println(Math.abs(date1.lilian()-date2.lilian()));
			}

			// Determine if the user wants to continue.
		   	System.out.println();
	   		System.out.print("Continue? (Y=Yes): ");
	   		conIn.nextLine();
	   		more = conIn.nextLine();
   		}
   		while (more.equalsIgnoreCase("y"));
   }

}
