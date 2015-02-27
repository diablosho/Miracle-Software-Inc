/**
 * @(#)SimplePalindrome.java
 *
 *
 * @author
 * @version 1.00 2012/3/25
 */

import java.util.Scanner;

public class SimplePalindrome {

    public static void main(String[] args) {

        boolean isPal = true;
        String sentence;
        Scanner scan = new Scanner(System.in);

        System.out.print("Enter your sentence >");
        sentence = scan.nextLine();

		int end = sentence.length() - 1;

		// Compare letters at balanced indices of the string
       	for (int i = 0; i < end/2; i++)
       	{
			// Ignore non letters from the front by incrementing i
       		while (!Character.isLetter(sentence.charAt(i)) && (i < end))
       				i++;
			// Ignore non letters from the rear by decrementing end
       		while (!Character.isLetter(sentence.charAt(end)) && (i < end))
       			end--;
			// If the characters at indices i and end do not match, no palindrome
    		if (sentence.charAt(i) != sentence.charAt(end))
    			isPal = false;
			// Decrement end
    		end--;
       	}

        if (isPal)
        	System.out.println("Your word IS a palindrome!");
        else
        	System.out.println("Your word is NOT a palindrome!");
    }
}
