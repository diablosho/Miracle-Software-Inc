import java.util.Scanner;
import java.text.DecimalFormat;
class DistanceTraveled
{
	public static void main(String[] args)
	{
		Scanner dataInput = new Scanner (System.in);
		DecimalFormat floatToInt = new DecimalFormat("##############0.##");
		float speed=0;;
		int time=0;
		do
		{
			System.out.println("Enter the speed of the vehicle (mph):  ");
			speed = dataInput.nextFloat();
		} while (speed < 0);
		do
		{
			System.out.println("How long has the vehicle been traveling (hours):  ");
			time = dataInput.nextInt();
		} while (time < 0);
		System.out.println("Hour				Distance Traveled");
		System.out.println("-------------------------------------------");
		for (int i=1; i <= time; i++)
		{
			System.out.println("" + i + "						" + floatToInt.format(speed*i));
		}
	}
}
		
