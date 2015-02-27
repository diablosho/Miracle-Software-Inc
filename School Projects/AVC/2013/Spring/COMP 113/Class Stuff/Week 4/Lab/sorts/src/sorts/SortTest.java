package sorts;

public class SortTest {
	public static void main(String[] args) {
		//declares 2 arrays and a random number
		int[] randArray;
		int[] ascArray;
		int[] descArray;
		final int SIZE = 10;
		final int RAND_RANGE = 100;
		long start1, start2, finish;
		
		Sorts sort = new Sorts(SIZE, RAND_RANGE);
		sort.InitArray();
		randArray = sort.getRandArray();
		start1 = new Date().getTime();
		ascArray = sort.ascBruteForce(randArray);
		start2 = new Date().getTime();
		descArray = sort.descBruteForce(randArray);
		finish = new Date().getTime();
		sort.displayArrays(SIZE, ascArray, descArray);

		System.out.println ("Time to sort " + SIZE + " elements in ascending order: " + (start2 - start1) + "ns\n" +
							"Time to sort " + SIZE + " elements in descending order: " + (finish - start2) + "ns");	
	}
}
