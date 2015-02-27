/**
Name:  			Brian Jones
Assignment:    Chapter 4:  Part II:  #11:  Celsius to Fahrenheit
Date: 			2011-10-03
Course:         CIS 111
Instructor:     Prof. Mummaw

This program will create a table, converting all integer degrees Celsius, from 0 to 20, to degrees Fahrenheit.
*/
import java.util.Scanner;				// Data Input Package
class CelsiusToFahrenheitTable
{
	public static void main(String[] args)			// Main Procedure
	{
		Scanner dataInput = new Scanner (System.in);		// Data Input object variable
		float FahrenheitTempConversion=0.0F;		// Variable to hold the converted Fahrenheit temperature
		for (int celsius=0; celsius <= 20; celsius++)		// Convert all integer Celsius temperatures, from 0 to 20, to Fahrenheit
		{
			FahrenheitTempConversion=(float)((9.0/5.0)*celsius) + 32F;		// Convert celsius degrees to Fahrenheit
			System.out.println(celsius + " degrees Celsius = " + FahrenheitTempConversion + " degrees Fahrenheit.");	//output
		}
	}
}
		
