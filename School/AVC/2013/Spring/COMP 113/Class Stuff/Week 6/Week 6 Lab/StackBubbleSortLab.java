package ch03.bubblesort;

//----------------------------------------------------------------------
// StackBubbleSort.java     Pseudocode by Dr. Lee              Chapter 3
//
// Applying bubble sort to stack operations
//----------------------------------------------------------------------

// import the Random class
import java.util.Random;
import ch03.stacks.*;

public class StackBubbleSortLab
{

	// scrambleArray
	// inputs: an integer array, and an integer
	// outputs: returns the scrambled array
	// function: this method iterates through each element of the input array
	//			 and swaps the current element with another random element
	//			 of the array, thus randomizing it.
	public static int [] scrambleArray (int [] arr)
	{
		// scramble the values in the array
		// declare integer values x, y, and rnd
		int x, y, rnd;
		// declare and initialize an integer num with the length of the array: arr.length
		int num = arr.length;
		// declare and instantiate a varible rand of type Random
		Random rand = new Random();
		// iterate through each index in the array and swap it with a random index
		for (int i = 0; i < num; i++)
		{
			// assign a random number from 0 to 51 to rnd
			rnd = rand.nextInt(num);
			// assign the i(th) element of arr to x
			x = arr[i];
			// assign the rnd(th) element of arr to y
			y = arr[rnd];
			// swap the elements, assign x to arr[rnd]
			arr[rnd] = x;
			// assign y to arr[i]
			arr[i] = y;
		}
		// test your code to make sure you have an array of sorted numbers
		// uncomment the following three lines. If everything works well
		// then comment the lines so you don't have the extra output
		for (int i = 0; i < num; i++)
			System.out.println(i + " " + arr[i]);
		System.out.println();

		return arr;
	}

	// The main method: Creates a randomized stack, sorts it, and outputs
	// the time it took to perform the sort operation and the number of
	// elements it sorted
	public static void main(String[] args)
	{
 		int num = 52;
 		
 		// declare an integer num and set it equal to 52
	 	// num is our control variable handling the stack size

	    // declare a BoundedStackInterface of type <Integer> named acsStack

	    // instantiate ascStack of size num

	    // declare a BoundedStackInterface of type <Integer> named descStack

	    // instantiate descStack of size num

		// declare/instantiate an integer array named arr, containing num elements

		// initialize the array with a for loop with values from 1 to num


		// Scramble the array:
		// call function scrambleArray passing arr as an argument

		// loop through arr and push the values of arr onto the ascStack


		// declare min, max, x, and y as integers and initialize them to 0




		// declare startClock, stopClock and timeDiff as long

		// initialize startClock with the System.nanoTime()

		// initialize a boolean variable named stopFlag to false

		// set a while loop to iterate until stopFlag is true

		{
			// set stopFlag to true

			// if ascStack is not empty do the following

			{
				// assign the top of ascStack to x

				// pop the ascStack to throw out the top element

			}
			// loop through ascStack until all elements have been popped and pushed to descStack
			// keep looping as long as ascStack is not empty

			{
				// assign the top of ascStack to y

				// pop the ascStack to throw out the top element

				//  if x is less than y enter the following block

				{
					// assign x to min

					// assign y to max

					// assign max to x

				}
				// else x is greater than y

				{
					// assign y to min

					// assign x to max

					// set stopFlag to false (this indicates a swap occurred)

				}
				// push min to the descStack

			}
			// push max to the descStack (this is the final value that needs to be added to the stack

			// if descStack is not empty do the following
			{
				// assign the top of ascStack to x

				// pop the ascStack to throw out the top element

			}
			// loop through descStack until all elements have been popped  and pushed to ascStack
			// keep looping as long as descStack is not empty

			{
				// assign the top of descStack to y

				// pop the ascStack to throw out the top element

				//  if x is greater than y

				{
					// assign x to max

					// assign y to min

					// assign and min to x

				}
			//  if x is less than y

				{
					// assign y to max (x is already the smallest)

					// assign x to min (x is already the minimum of x and y)

					// set stopFlag to false

				}
				// push max to the ascStack

			}
			// push min (the last value) to the ascStack

		}
		// ascStack should now contain a sorted sorted stack of elements
		// with the topmost element being the minimum number and the
		// bottommost element the maximim number

		// initialize stopClock with the System.nanoTime()

		// calculate timeDiff which equals stopClock minus startClock

		// The following prints the elements of ascStack without maintaining them
//		while (!ascStack.isEmpty())
//		{
//			System.out.println(ascStack.top());
//			ascStack.pop();
//		}

		// Print out the time it took to sort
//		System.out.print("\nIt took " + timeDiff + " nano seconds to sort the list of " + num + " integers");
	 }
}