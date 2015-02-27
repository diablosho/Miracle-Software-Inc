public class Rainfall
{
	private final int size = 12;
	private double[] Rainfall = new double[size];
	private double totalRainfall;
	private double averageRainfall;
	public Rainfall ()
	{
	}
	public void setMonthRainfall(int month, double rainfall)
	{
		Rainfall[month]=rainfall;
	}
	public double getMonthRainfall(int month)
	{
		return Rainfall[month];
	}
	public double getTotalRainfall()
	{
		for (int i=0; i<Rainfall.length; i++)
			totalRainfall+=Rainfall[i];
		return totalRainfall;
	}
	public double getAverageMonthlyRainfall()
	{
		for (int i=0; i<Rainfall.length; i++)
			averageRainfall+=(1.0/12.0)*Rainfall[i];
		return averageRainfall;
	}
	public String getMonthWithMostRainfall()
	{
		int monthWithMostRainfall=0;
		for (int i=0; i<Rainfall.length; i++)
		{
			if (Rainfall[monthWithMostRainfall] < Rainfall[i])
				monthWithMostRainfall=i;
		}
		switch (monthWithMostRainfall)
		{
			case 0:  return "January";
			case 1:  return "February";
			case 2:  return "March";
			case 3:  return "April";
			case 4:  return "May";
			case 5:  return "June";
			case 6:  return "July";
			case 7:  return "August";
			case 8:  return "September";
			case 9:  return "October";
			case 10:  return "November";
			case 11:  return "December";
			default:  break;
		}
		return "Error";
	}
	public String getMonthWithLeastRainfall()
	{
		int monthWithLeastRainfall=0;
		for (int i=0; i<Rainfall.length; i++)
		{
			if (Rainfall[monthWithLeastRainfall] > Rainfall[i])
				monthWithLeastRainfall=i;
		}
		switch (monthWithLeastRainfall)
		{
			case 0:  return "January";
			case 1:  return "February";
			case 2:  return "March";
			case 3:  return "April";
			case 4:  return "May";
			case 5:  return "June";
			case 6:  return "July";
			case 7:  return "August";
			case 8:  return "September";
			case 9:  return "October";
			case 10:  return "November";
			case 11:  return "December";
			default:  break;
		}
		return "Error";
	}
}