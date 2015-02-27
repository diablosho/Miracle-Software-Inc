

import java.util.Random;
public class Arrays
{
	final static int SIZE = 20;
	public static void main(String[] args)
	{
		Random gen = new Random();
		int lcv;
		float average;
		int[] nums = new int[SIZE];
		int[] nums2 = {2, 4, 6, 8};
		
		//fill array
		for(lcv = 0; lcv < SIZE; lcv ++)
			nums[lcv] = gen.nextInt(101);
		//print array
		printArray(nums);
		
		average = findAverage(nums);
		System.out.println(average);
		average = findAverage(nums2);
		System.out.println(average);
		sortArray(nums);
		System.out.println("Sorted array");
		printArray(nums);
	}
	public static float findAverage(int[] values)
	{
		float average;
		int indx;
		
		average = findSum(values) / (float) values.length;
		return average;
	}
	public static int findSum(int[] values)
	{
		int lcv, sum = 0;
		
		for(lcv = 0; lcv < values.length; lcv++)
			sum += values[lcv];
		System.out.println("sum -> " + sum);
		return sum;
	}	
	public static void printArray(int[] values)
	{
		int lcv;
		for(lcv = 0; lcv < values.length; lcv++)
			System.out.println(values[lcv]);
	}
	public static void sortArray(int[] nums)
	{
		int pass, comp, temp;
		
		for(pass = 1; pass < nums.length; pass++)
			for(comp = 0; comp < nums.length - 1; comp++)
				if(nums[comp] > nums[comp+1])
				{
					temp = nums[comp];
					nums[comp] = nums[comp+1];
					nums[comp+1] = temp;
				}
	}
	
}