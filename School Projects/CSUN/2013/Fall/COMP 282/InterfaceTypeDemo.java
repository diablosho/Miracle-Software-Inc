<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<!DOCTYPE html PUBLIC "" ""><HTML><HEAD>
<META http-equiv="Content-Type" 
content="text/html; charset=windows-1252"></HEAD>
<BODY>
<PRE>/*
InterfaceTypeDemo.java

Illustrates that interfaces are ADTs -- you can create a 
collection of them.

In the example aList is a ArrayList of InterfaceB types.
However its members are either ClassB, ClassC, or ClassD objects
as well as being ClassA objects.

Mike Barnes
8/26/2010
*/

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

interface InterfaceB {
   public void foo();
   }

abstract class ClassA {
   protected int id;
   }

class ClassB extends ClassA implements InterfaceB {
   public ClassB(int i) { id = i; }
   public void foo() { System.out.println(getClass().getName() + " id = " + id); }
   }

class ClassC  implements InterfaceB {
   String name;
   public ClassC(String str) { name = str; }
   public void foo() { System.out.println("ClassC name = " + name); }
   }

class ClassD extends ClassB {
   public ClassD(int i) { super(i); }
   }
    
public class InterfaceTypeDemo {

   ArrayList &lt;InterfaceB&gt; aList;
   ClassB aClassB;
   ClassC aClassC;
   ClassD aClassD;
   Random aRandom;

   public InterfaceTypeDemo() {
      aList = new ArrayList&lt;InterfaceB&gt;();
      aRandom = new Random();
      System.out.println("Initial aList");
      System.out.println("aList has " + aList.size() + " elements");
      System.out.println("add 11 elements to aList");
      for(int i = 0; i &lt; 11; i++) 
         switch(aRandom.nextInt(3)) {
         case 0 : aClassB = new ClassB(10 + i);
                  System.out.print("create "); 
                  aClassB.foo();
                  aList.add(aClassB); 
                  break;
         case 1 : aClassC = new ClassC("2" + i);
                  System.out.print("create ");
                  aClassC.foo();
                  aList.add(aClassC); 
                  break;
         case 2 : aClassD = new ClassD(30 + i);
                  System.out.print("create ");
                  aClassD.foo();
                  aList.add(aClassD); 
         }
      System.out.println("aList has " + aList.size() + " elements");
      }

   public void show() {
      // need to specify which type &lt;InterfaceB&gt; because
      // aList members are either ClassB or ClassC objects but they
      // are also ClassA and InterfaceB types.  
      Iterator &lt;InterfaceB&gt; iterator =  aList.iterator();
      System.out.println("show the values of aList");
      while (iterator.hasNext()) iterator.next().foo();
      }

   public static void main(String [] arg) {
      InterfaceTypeDemo itd = new InterfaceTypeDemo();
      itd.show();
      }

   }</PRE></BODY></HTML>
