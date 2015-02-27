/**
Name:  			Brian Jones
Assignment:    Chapter 6:  Assignment 2: Car Class
Date: 			2011-11-14
Course:         CIS 111
Instructor:     Prof. Mummaw
	- This class will create an object for the DemoCar program
	- 3 private fields  are used for: 							 
						Model Year (int yearModel)
						Make (String make)
						Speed (int speed)
	- The constructor Car() has 2 arguments (int argYearModel, String argMake) which are passed by the DemoCar program
	- There are methods defined to allow: 				 
						retrieval of model year (GetModelYear())
						retrieval of make (GetMake())
						retrieval of current speed (GetSpeed())
						acceleration of vehicle (Accelerate())
						decelleration of vehicle (Brake())
*/
import java.lang.Math;
public class Car
{
	private int yearModel;
	private String make;
	private int speed;
	
	public Car (int argYearModel, String argMake)	// Constructor / Transfer constructor fields to class fields
	{
		yearModel=argYearModel;							
		make=argMake;
		speed=0;
	}
	public int GetModelYear()								// Return model year
	{
		return yearModel;
	}
	public String GetMake()									// Return make
	{
		return make;
	}
	public int GetSpeed()										// Return speed
	{
		if (speed<0)
			speed=0;
		return speed;
	}
	public void Accelerate()										// Accellerate the vehicle
	{
		speed+=5;
	}
	public void Brake()											// Decellerate the vehicle
	{
		speed-=5;
	}
}