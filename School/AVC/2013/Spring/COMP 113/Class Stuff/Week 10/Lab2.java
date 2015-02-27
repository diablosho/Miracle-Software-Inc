/* Lab 2: Make a new class
 * 	Your Name:
 *	1. Identify and comment 4 errors
 *	2. Create a new Java class file named recur
 *	3. Move the sum method to recur
 *	4. Invoke the sum method from the recur class
 *	   Hint: you need to make a change in the main method
 *	5. You will have one error to correct which has to do
 *	   with Java Access Control Modifiers
 *	   Hint: it's an object oriented permissions issue
 *  6. E-mail me your corrected file
 *	7. Your e-mail's subject line must contain the following:
 *		CIS113: Week10 Lab exercises.
 */
import java.util.Scanner;
public class Lab2
{
  // Precondition: n >= 0
  // Returns the sum of 1 + 2 + ... + n
  private static int sum(int n)
  {
    if (n == 0)
       return 0;
    else
      return (n + sum(n - 1));
  }

  public static void main(String[] args)
  {
    Scanner conIn = new Scanner(System.in);
    int num;

    System.out.print("Enter an integer: ");
    num = conIn.nextInt();

    System.out.println(recur.sum(num));
  }
}
