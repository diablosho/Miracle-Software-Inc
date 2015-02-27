//----------------------------------------------------------------------------
// Sorts.java               by Dale/Joyce/Weems modified by Lee     Chapter 10
//
// Test harness used to run sorting algorithms.
// This is preparation for a final project if you choose not to take the final exam.
//----------------------------------------------------------------------------

import java.util.*;
import java.text.DecimalFormat;

public class Sorts
{
  //***************************************************************//
  // declare two static integers cntSwaps and cntComparisons
  // 	you will need to increment cntSwaps and cntComparisons
  //	in several of the following methods, it is your job to
  //	figure out where and how to do it correctly!

  //***************************************************************//
  static final int SIZE = 10;            // size of array to be sorted
  static int[] values = new int[SIZE];   	// values to be sorted

  // Initializes the values array with random integers from 1 to SIZE.
  static void initRndValues()
  {
  	//************************************************************//
	// initialize cntSwaps and cntComparisons to 0 (zero).


  	//************************************************************//

    Random rand = new Random();
    for (int index = 0; index < SIZE; index++)
      values[index] = rand.nextInt(SIZE) + 1;
  }

  //************************************************************//
  // create a static void method named initAscValues
  //   initialize cntSwaps and cntComparisons to 0.
  //   initialize the array values with ascending #s
  //		from 1 to SIZE






  //************************************************************//


  // Initializes the values array with random integers from 0 to 99.
  //************************************************************//
  // create a static void method named initDescValues
  //   initialize cntSwaps and cntComparisons to 0.
  //   initialize the array values with descending #s
  //		from Size to 1







  //************************************************************//


  // Returns true if the array values are sorted and false otherwise.
  static public boolean isSorted()
  {
    boolean sorted = true;
    for (int index = 0; index < (SIZE - 1); index++)
    {
      if (values[index] > values[index + 1])
        sorted = false;
    }
    return sorted;
  }

  // Precondition: index1 and index2 are >= 0 and < SIZE.
  // Swaps the integers at locations index1 and index2 of the values array.
  //
  static public void swap(int index1, int index2)
  {
    int temp = values[index1];
    values[index1] = values[index2];
    values[index2] = temp;
  }

  // Prints all the values integers.
  static public void printValues()
  {
    int value;
    DecimalFormat fmt = new DecimalFormat("00");
    System.out.println("The values array is:");
    for (int index = 0; index < SIZE; index++)
    {
      value = values[index];
      if (((index + 1) % 10) == 0)
        System.out.println(fmt.format(value));
      else
        System.out.print(fmt.format(value) + " ");
    }
    System.out.println();
  }

  /////////////////////////////////////////////////////////////////
  //  Selection Sort
  // 	Returns the index of the smallest value in
  // 	values[startIndex]..values[endIndex].
  //
  static int minIndex(int startIndex, int endIndex)
  {
    int indexOfMin = startIndex;
    for (int index = startIndex + 1; index <= endIndex; index++)
    {
      if (values[index] < values[indexOfMin])
        indexOfMin = index;
    }
    return indexOfMin;
  }

  // Sorts the values array using the selection sort algorithm.
  static void selectionSort()
  {
    int endIndex = SIZE - 1;
    for (int current = 0; current < endIndex; current++)
    {
      swap(current, minIndex(current, endIndex));
    }
  }

  /////////////////////////////////////////////////////////////////
  //  Bubble Sort
  // 	Switches adjacent pairs that are out of order
  // 	between values[startIndex]..values[endIndex]
  // 	beginning at values[endIndex].
  //
  static void bubbleUp(int startIndex, int endIndex)
  {
    for (int index = endIndex; index > startIndex; index--)
    {
      if (values[index] < values[index - 1])
        swap(index, index - 1);
    }
  }

  // Sorts the values array using the bubble sort algorithm.
  static void bubbleSort()
  {
    int current = 0;

    while (current < (SIZE - 1))
    {
      bubbleUp(current, SIZE - 1);
      current++;
    }
  }


  /////////////////////////////////////////////////////////////////
  //  Short Bubble Sort
  // 	Switches adjacent pairs that are out of order
  // 	between values[startIndex]..values[endIndex]
  // 	beginning at values[endIndex].
  //
  // 	Returns false if a swap was made; otherwise, returns true.
  //
  static boolean bubbleUp2(int startIndex, int endIndex)
  {
    boolean sorted = true;
    for (int index = endIndex; index > startIndex; index--)
    {
      if (values[index] < values[index - 1])
      {
        swap(index, index - 1);
        sorted = false;
      }
    }
    return sorted;
  }

  // Sorts the values array using the bubble sort algorithm.
  // The process stops as soon as values is sorted.
  static void shortBubble()
  {
    int current = 0;
    boolean sorted = false;
    while ((current < (SIZE - 1)) && !sorted)
    {
      sorted = bubbleUp2(current, SIZE - 1);
      current++;
    }
  }


  /////////////////////////////////////////////////////////////////
  //  Insertion Sort
  static void insertItem(int startIndex, int endIndex)
  // Upon completion, values[0]..values[endIndex] are sorted.
  {
    boolean finished = false;
    int current = endIndex;
    boolean moreToSearch = true;
    while (moreToSearch && !finished)
    {
      if (values[current] < values[current - 1])
      {
        swap(current, current - 1);
        current--;
        moreToSearch = (current != startIndex);
      }
      else
        finished = true;
    }
  }

  static void insertionSort()
  // Sorts the values array using the insertion sort algorithm.
  {
   for (int count = 1; count < SIZE; count++)
      insertItem(0, count);
  }

  /////////////////////////////////////////////////////////////////
  //  Main
  //	Declare startClock and StopClock
  //	Use System.nanoTime to determine the runtime of the sort
  //	Output cntComparisons
  //	Output cntSwaps
  //	Output Efficiency = cntComparisons/SIZE
  //	Output ImprovedEfficiency = (cntComparisons + cntSwaps)/SIZE
  //	Output CPU time in seconds to two significant digits, i.e. 5.23s
  //		(hint: use DecimalFormat)
  public static void main(String[] args)
  {
    initRndValues();
//    initAscValues();
    initDescValues();
//    printValues();
    System.out.println("values is sorted: " + isSorted());
    System.out.println();

    // make call to sorting method here (just remove //)
    // selectionSort();
    // bubbleSort();
    // shortBubble();
     insertionSort();

    printValues();
    System.out.println("values is sorted: " + isSorted());
    System.out.println();
  }
}
