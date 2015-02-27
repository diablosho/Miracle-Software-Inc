import java.util.Scanner;
class LetterCounter
{
	public static void main(String[] args)
	{
		Scanner dataInput = new Scanner (System.in);
		char letterToCountFor;
		String stringToCompareTo;
		int i=0;
		int Occurences=0;
		
		System.out.println("Enter a string:  ");
		stringToCompareTo = dataInput.nextLine();
		System.out.println("Enter a letter to count for in the string:  ");
		letterToCountFor = dataInput.next().charAt(0);
		
		while (i<stringToCompareTo.length())
		{
			if (letterToCountFor == stringToCompareTo.charAt(i))
				Occurences++;
			i++;
		}
		
		System.out.println("There are " + Occurences + " occurences of '" + letterToCountFor +"' in the string " + stringToCompareTo + ".");
	}
}