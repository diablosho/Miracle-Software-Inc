//----------------------------------------------------------------------
// ForwardSort.java
// Creates an array of 10 random numbers, then sorts them into a second
// array. Both arrays are then printed out in a table to show it worked.
// Array is sorted smallest to largest.
//----------------------------------------------------------------------

import java.util.Random;

public class ForwardSort {	
	public static void main(String[] args){
		//declares 2 arrays and a random number
		int[] randArray = new int[10];
		int[] sortArray = new int[10];
		Random rand = new Random();
		int smallest = 101;
		int index = 0;
		
		//initializes first array with random numbers between
		//1 and 100
		for(int i = 0; i < 10; i++)
			randArray[i] = rand.nextInt(100) + 1;
	
		//outputs results into table
		System.out.println("Element\t\tunsorted Array");
		for(int i = 0; i < 10; i++)
			System.out.println(i + "\t\t" + randArray[i]);		
		
		//sorts array by checking for the smallest element in rand
		//and placing it into sortArray, then doing it again until
		//it makes it through all elements
		for(int i = 0; i < 10; i++){
			smallest = randArray[i];
			for(int j = 0; j < 10; j++)
				if(randArray[j] < smallest){
					smallest = randArray[j];
					index = j;
				}
			sortArray[i] = smallest;
			randArray[index] = 101;
		}

		//outputs results into table
		System.out.println("Element\t\tsortedArray");
		for(int i = 0; i < 10; i++)
			System.out.println(i + "\t\t" + sortArray[i]);
	}
}