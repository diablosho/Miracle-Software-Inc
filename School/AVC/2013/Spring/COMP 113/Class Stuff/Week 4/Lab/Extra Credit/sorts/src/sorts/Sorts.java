package sorts;

import java.util.Random;

public class Sorts {
	int [] randArray;
	int randRange;
	final int OB_MAX;
	final int OB_MIN = -1;
	
	public Sorts(){
		randArray = new int[10];
		randRange = 100;
		OB_MAX = randRange + 1;
	}
	
	public Sorts(int arrSize, int randRange){
		randArray = new int[arrSize];
		this.randRange = randRange;
		OB_MAX = randRange + 1;
	}
	
	public void InitArray(){
		Random rand = new Random();
		for(int i = 0; i < 10; i++)
			randArray[i] = rand.nextInt(randRange) + 1;
	}
	
	public int[] getRandArray(){
		return randArray;
	}
	
	public int[] ascBruteForce(int[]rand){
		int[] sort = new int[rand.length];
		int[] temp = new int[rand.length];
		System.arraycopy(rand, 0, temp, 0, rand.length);
		int smallest = OB_MAX;
		int index = 0;
		for(int i = 0; i < rand.length; i++){
			smallest = temp[i];
			for(int j = 1; j < rand.length; j++)
				if(temp[j] < smallest){
					smallest = temp[j];
					index = j;
				}
			sort[i] = smallest;
			temp[index] = OB_MAX;
		}
		return sort;
	}
	
	public int[] descBruteForce(int[]rand){
		int[] sort = new int[rand.length];
		int[] temp = new int[rand.length];
		System.arraycopy(rand, 0, temp, 0, rand.length);
		int largest = OB_MIN;
		int index = 0;
		for(int i = 0; i < rand.length; i++){
			largest = temp[i];
			for(int j = 0; j < rand.length; j++)
				if(temp[j] > largest){
					largest = temp[j];
					index = j;
				}
			sort[i] = largest;
			temp[index] = OB_MIN;
		}
		return sort;
	}
	
	public void displayArrays(int size, int[] ascArray, int[] descArray){
		System.out.println("Element\t\tunsorted\tforward\t\treverse");
		for(int i = 0; i < size; i++)
			System.out.println(i + "\t\t" + randArray[i] +
								   "\t\t" + ascArray[i] +
								   "\t\t" + descArray[i]);
	}
}
