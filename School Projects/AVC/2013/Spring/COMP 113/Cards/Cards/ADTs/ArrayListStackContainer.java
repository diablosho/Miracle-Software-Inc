package ADTs;

import Stacks.ArrayListStack;

public class ArrayListStackContainer // Container for ArrayListStacks
{
	public int						elementCount;	// Number of stacks in the
													// array
	public ArrayListStack<Card>[]	stack;			// Array of
													// ArrayListStack<Card>'s

	public ArrayListStackContainer(int size) // Constructor for the Container
	{
		elementCount = size; // Initialize the elementCount, and size of array,
								// to 'size'
		stack = new ArrayListStack[size]; // Create the stack array

		for (int i = 0; i < size; i++)
		{
			stack[i] = new ArrayListStack<Card>(); // Initialize all of the
													// stacks in the Container
		}
	}

	public void SwapElements(int element1, int element2) // Method to swap two
															// stacks in the
															// array
	{
		ArrayListStack<Card> object1 = new ArrayListStack<Card>();
		ArrayListStack<Card> object2 = new ArrayListStack<Card>();

		object1.addStack(stack[element1]); // Object 1 = stack 1
		object2.addStack(stack[element2]); // Object 2 = stack 2

		stack[element1].EmptyStack(); // Stacks 1 = empty
		stack[element2].EmptyStack(); // Stacks 2 = empty

		stack[element1].addStack(object2); // Stack1 = Object 2
		stack[element2].addStack(object1); // Stack2 = Object 1
	}
}