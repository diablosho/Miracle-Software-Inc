/**
 * @(#)Date.java
 *
 * Date application
 *
 * @author
 * @version 1.00 2012/2/5
 */

public class Date {

    protected int year;						// instance variable
    protected int month;					// instance variable
    protected int day;						// instance variable
    public static final int MINYEAR = 1581;	// class variable because of static, final -> var can't be modified
    										// MINYEAR is the first full year of the Gregorian calender
    // Constructor
    public Date(int newMonth, int newDay, int newYear)
    {
    	month = newMonth;
    	day = newDay;
    	year = newYear;
    }

    // Observers
    public int getYear()	// OBSERVER
    {
    	return year;
    }

    public int getMonth()	// OBSERVER
    {
    	return month;
    }

    public int getDay()		// OBSERVER
    {
    	return day;
    }

    public int lilian()		// TRANSFORMER
    {
    	// Returns the Lilian Day Number of this date.
    	// Precondition: This date is valid after 10/14/1582.
    	//
    	// 1. Computes the number of days between 1/1/0 and the date of interest.
    	// 2. Subtracts 578100 (represents 10/14/1582)
    	// Note: Oct. 15th, 1582 = day #1

    	final int SUBDAYS = 578100;

    	int numDays = 0;

    	// Add days in years.
    	numDays = year * 365;

    	// Add days in months.
    	if (month <= 2)
    		numDays = numDays + (month - 1) * 31;
    	else
    		numDays = numDays + ((month - 1) * 31)
    						  - ((4 * (month - 1) + 27) / 10);

    	// Add days in the days.
    	numDays = numDays + day;

    	// Handle leap years.
    	numDays = numDays + (year / 4) - (year / 100) + (year / 400);

    	// Handle special case of leap year but not yet leap day.
    	if (month < 3)
    	{
    		if ((year % 4) == 0)	numDays = numDays - 1;
    		if ((year % 100) == 0)	numDays = numDays + 1;
    		if ((year % 400) == 0)	numDays = numDays - 1;
    	}

		// Subtract extra days up to 10/14/1582
		numDays = numDays - SUBDAYS;

		return numDays;

    }

	public int mjd()		// TRANSFORMER
    {
    	// Returns the Modified Julian Day Number of this date.
    	// Precondition: This date is valid after 11/17/1858.
    	//
    	// 1. Computes the number of days between 1/1/0 and the date of interest.
    	// 2. Subtracts 578100 (represents 10/14/1582)
    	// 3. There are 100840 days between 10/14/1582 and 11/17/1858
    	// Note: Oct. 15th, 1582 = day #1

    	final int SUBDAYS = 578100 + 100840;

    	int numDays = 0;

    	// Add days in years.
    	numDays = year * 365;

    	// Add days in months.
    	if (month <= 2)
    		numDays = numDays + (month - 1) * 31;
    	else
    		numDays = numDays + ((month - 1) * 31)
    						  - ((4 * (month - 1) + 27) / 10);

    	// Add days in the days.
    	numDays = numDays + day;

    	// Handle leap years.
    	numDays = numDays + (year / 4) - (year / 100) + (year / 400);

    	// Handle special case of leap year but not yet leap day.
    	if (month < 3)
    	{
    		if ((year % 4) == 0)	numDays = numDays - 1;
    		if ((year % 100) == 0)	numDays = numDays + 1;
    		if ((year % 400) == 0)	numDays = numDays - 1;
    	}

		// Subtract extra days up to 10/14/1582
		numDays = numDays - SUBDAYS;

		return numDays;
    }

	public int djd()		// TRANSFORMER
    {
    	// Returns the Lilian Day Number of this date.
    	// Precondition: This date is valid after 1/1/1900.
    	//
    	// 1. Computes the number of days between 1/1/0 and the date of interest.
    	// 2. Subtracts 578100 (represents 10/14/1582)
    	// 3. There are 115860 days between 1/14/1582 and 1/1/1900
    	// Note: Oct. 15th, 1582 = day #1

    	final int SUBDAYS = 578100 + 115860;

    	int numDays = 0;

    	// Add days in years.
    	numDays = year * 365;

    	// Add days in months.
    	if (month <= 2)
    		numDays = numDays + (month - 1) * 31;
    	else
    		numDays = numDays + ((month - 1) * 31)
    						  - ((4 * (month - 1) + 27) / 10);

    	// Add days in the days.
    	numDays = numDays + day;

    	// Handle leap years.
    	numDays = numDays + (year / 4) - (year / 100) + (year / 400);

    	// Handle special case of leap year but not yet leap day.
    	if (month < 3)
    	{
    		if ((year % 4) == 0)	numDays = numDays - 1;
    		if ((year % 100) == 0)	numDays = numDays + 1;
    		if ((year % 400) == 0)	numDays = numDays - 1;
    	}

		// Subtract extra days up to 10/14/1582
		numDays = numDays - SUBDAYS;

		return numDays;
    }

    public String toString()
    {
    	String sMonth = "";
    	switch (month){
			case 1:
				sMonth = "January";
				break;
			case 2:
				sMonth = "February";
				break;
			case 3:
				sMonth = "March";
				break;
			case 4:
				sMonth = "April";
				break;
			case 5:
				sMonth = "May";
				break;
			case 6:
				sMonth = "June";
				break;
			case 7:
				sMonth = "July";
				break;
			case 8:
				sMonth = "August";
				break;
			case 9:
				sMonth = "September";
				break;
			case 10:
				sMonth = "October";
				break;
			case 11:
				sMonth = "November";
				break;
			case 12:
				sMonth = "December";
				break;
    	}
    	return(sMonth + " " + day + ", " + year);
    }

	public class IncDate extends Date
	{
		public IncDate(int newMonth, int newDay, int newYear)
		{
			super(newMonth, newDay, newYear);
		}

		public void increment()
		// Preconditions:  Value of day, month, year represent a valid date
		//				   year must be > MINYEAR
		//
		// Increments this IncDate to represent the next day
		{
			// code here
		}
	}

}


