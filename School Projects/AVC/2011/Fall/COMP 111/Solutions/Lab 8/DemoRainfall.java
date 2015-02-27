import java.util.Scanner;
public class DemoRainfall
{
	public static void main (String[] args)
	{
		Scanner dataInput = new Scanner(System.in);
		Rainfall rainfall = new Rainfall();
		boolean InvalidInput=false;
		for (int i=0; i<12; i++)
		{
			do
			{
				InvalidInput=false;
				System.out.print("Enter month " + (i+1) + "'s rainfall:  ");
				try
				{
					rainfall.setMonthRainfall(i, dataInput.nextDouble());
				}
				catch (Exception e)
				{
					InvalidInput=true;
					dataInput.next();
				}
			} while (InvalidInput || rainfall.getMonthRainfall(i) < 0);
		}
		
		System.out.println("Total Rainfall for the year:  " + rainfall.getTotalRainfall() + " inches ");
		System.out.println("Average Monthly Rainfall:  " + rainfall.getAverageMonthlyRainfall() + " inches ");
		System.out.println("Month with the Most Rainfall:  " + rainfall.getMonthWithMostRainfall());
		System.out.println("Month with the Least Rainfall:  " + rainfall.getMonthWithLeastRainfall());
	}
}