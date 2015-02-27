//----------------------------------------------------------------------------
// UseStringLog.java           by Dale/Joyce/Weems                   Chapter 2
//
// Simple example of the use of a StringLog.
//----------------------------------------------------------------------------

import ch02.stringLogs.*;
// add imports as directed by comments below

public class UseStringLog
{
  public static void main(String[] args)
  {
    StringLogInterface sample;
    sample 		= new ArrayStringLog("Random Array");

	// Begin commenting out the following code
    sample.insert("Elvis");
    sample.insert("King Louis XII");
    sample.insert("Captain Kirk");
    System.out.println(sample);
    System.out.println("The size of the log is " + sample.size());
    System.out.println("Elvis is in the log: " + sample.contains("Elvis"));
    System.out.println("Santa is in the log: " + sample.contains("Santa"));
	// End commenting

    // declare and instantiate a sampleCopy and sampleSorted string logs


    // declare some timing variables startClock and stopClock
    // don't forget to import java.util.Date prior to UseStringLog


	// declare a variable named elapsedTime of type long
	// elapsedTime will hold the time differential in milliseconds


    // declare other variables
    // two String variables named min and rand
    //		since a string log contains methods passing strings,
    //		the int's will need to be converted


	// declare three integer variables named numElements, minValue, and maxValue
	// set numElements and maxValue to 10000
	// set minValue to 1


    // declare a variable named random of type Random and instantiate it.


    // Load the string log sample with 10000 random numbers ranging from 1-10000
    // don't forget to import java.util.Random prior to UseStringLog


    // start the clock
	// instantiate the timer Date().getTime() for startClock


    // insert a sorting method here to sort the array of numbers represented
    // Hint: 	1. identify the smallest element in sampleCopy and assign it to min
    //			2. insert min into sampleSort
    //			3. delete min from sampleCopy
    //			4. repeat steps 1-3 until sampleCopy is empty


    // stop the clock


    // print out the time it took to do the sort in milliseconds


    // print out the sample string log with the .toString method


    // print out the sampleSort string log with the .toString method


    // print out the time in milliseconds used by the sort algorithm


  }
}