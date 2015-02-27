/**	Armstrong Numbers (n digit number = n digits ^ n 


*/
import java.util.Scanner;

public class NumsEqualSumsFourth
{
	public static void main(String[] args)
	{
		Scanner dataInput = new Scanner(System.in);
		int seedNumber=1000;
		int firstNumber, secondNumber, thirdNumber, fourthNumber;
		int sumNumbers;
		float conversionNumber;
		
		while (seedNumber < 10000)
		{
			conversionNumber=seedNumber;
			firstNumber =(int) (conversionNumber * .001);
				conversionNumber -= (firstNumber * 1000);
			secondNumber = (int)(conversionNumber * .01);
				conversionNumber -= (secondNumber * 100);
			thirdNumber = (int)(conversionNumber * .1);
				conversionNumber -= (thirdNumber * 10);
			fourthNumber = (int)(conversionNumber * 1);
				conversionNumber -= (fourthNumber * 1);
			sumNumbers = (int)(Math.pow(firstNumber, 4) + (int)Math.pow(secondNumber, 4) + (int)Math.pow(thirdNumber, 4) + (int)Math.pow(fourthNumber, 4));
			if (sumNumbers == seedNumber)
				System.out.println(seedNumber);
			seedNumber++;
		}
	}
}