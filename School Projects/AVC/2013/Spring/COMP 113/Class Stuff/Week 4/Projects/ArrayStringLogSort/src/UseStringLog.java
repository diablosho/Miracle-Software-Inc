//----------------------------------------------------------------------------
// UseStringLog.java           by Dale/Joyce/Weems                   Chapter 2
//								updated by Lee
//
// Example of applying a brute force sorting routine to the ArrayStringLog
//----------------------------------------------------------------------------

import java.util.Date;
import java.util.Random;
// add imports as directed by comments below

public class UseStringLog
{
  public static void main(String[] args)
  {
    final int LOG_SIZE = 10;
    final int NUM_SIZE = 10;
 
    System.out.println("Array: ");
    
    // increments the log size and random number size used in the driven method
    // by multiples of 10
   	System.out.println("Log Size: " + LOG_SIZE);
	System.out.println("Random Number Size: " + NUM_SIZE);
	System.out.println("Average Time: " + ((driven(LOG_SIZE, NUM_SIZE) + 
											driven(LOG_SIZE, NUM_SIZE) + 
											driven(LOG_SIZE, NUM_SIZE)) / 3));
  }
  
  public static long driven(int numElements, int maxValue)
  {
    // declare and instantiate a sampleCopy and sampleSorted string logs
	StringLogInterface sampleCopy = new ArrayStringLog("Work Array");
	StringLogInterface sampleSorted = new ArrayStringLog("Sort Array");

	
    // declare some timing variables startClock and stopClock
    // don't forget to import java.util.Date prior to UseStringLog
    long startClock;
    long stopClock;


	// declare a variable named elapsedTime of type long
	// elapsedTime will hold the time differential in milliseconds
	long elapsedTime;


    // declare other variables
    // two String variables named min and rand
    //		since a string log contains methods passing strings,
    //		the int's will need to be converted
    String min;
    String rand;
    int temp;


	// declare three integer variables named numElements, minValue, and maxValue
	// set numElements and maxValue to 10000
	// set minValue to 1
	int minValue = 1;
	
	
    // declare a variable named random of type Random and instantiate it.
	Random random = new Random();

	
    // Load the string log sample with 10000 random numbers ranging from 1-10000
    // don't forget to import java.util.Random prior to UseStringLog
	for(int i = 0; i < numElements; i++)
	{
		rand = Integer.toString(random.nextInt(maxValue - minValue) - minValue + 1);
		sampleCopy.insert(rand);
	}


    // start the clock
	// instantiate the timer Date().getTime() for startClock
	startClock = new Date().getTime();

    
	// insert a sorting method here to sort the array of numbers represented
    // Hint: 	1. identify the smallest element in sampleCopy and assign it to min
    //			2. insert min into sampleSort
    //			3. delete min from sampleCopy
    //			4. repeat steps 1-3 until sampleCopy is empty
	for(int i = 0; i < numElements; i++)
	{
		min = sampleCopy.smallest();
		sampleSorted.insert(min);
		sampleCopy.delete(min);
	}


    // stop the clock
	stopClock = new Date().getTime();

    
	// print out the time it took to do the sort in milliseconds
	elapsedTime = stopClock - startClock;

    
	// print out the sample string log with the .toString method
		System.out.println(sampleCopy.toString());

    // print out the sampleSort string log with the .toString method
		System.out.println(sampleSorted.toString());

	return elapsedTime;
  }
}