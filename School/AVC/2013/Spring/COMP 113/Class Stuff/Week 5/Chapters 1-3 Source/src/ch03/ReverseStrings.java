package ch03;
//----------------------------------------------------------------------
// ReverseStrings.java         by Dale/Joyce/Weems                Chapter 3
//
// Sample use of stack. Outputs strings in reverse order of entry.
//----------------------------------------------------------------------

import ch03.stacks.*;

import java.util.Scanner;

public class ReverseStrings 
{
  public static void main(String[] args)
  {
    Scanner conIn = new Scanner(System.in);

//	ArrayStack - Bounded
//  This is how we must create generic collections using arrays in Java!
//  Note: the compiler warning during compilation
//  Compile ArrayStack.java to visualize warning
    BoundedStackInterface<String> stack;
    stack = new ArrayStack<String>(3);

//	ArrayListStack - Unbounded
//  The Java library's generic ArrayList gets around this compiler warning
//  Compile ArrayListStack.java to verify there is no warning
//	UnboundedStackInterface<String> stack;
//	stack = new ArrayListStack<String>();

//  LinkedStack - Unbounded
//	UnboundedStackInterface<String> stack;
//	stack = new LinkedStack<String>();
    
    String line;
    
    for (int i = 1; i <= 3; i++)
    {
      System.out.print("Enter a line of text > ");
      line = conIn.nextLine();
      stack.push(line);
    }
    	 
    System.out.println("\nReverse is:\n");
    while (!stack.isEmpty())
    {
      line = stack.top();
      stack.pop();
      System.out.println(line);
    }
  }
}