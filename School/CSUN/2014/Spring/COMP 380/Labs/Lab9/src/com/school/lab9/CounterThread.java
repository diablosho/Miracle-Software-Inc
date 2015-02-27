package com.school.lab9;

public class CounterThread extends Thread implements Runnable
{	
	MainActivity	parent		=	null;
	boolean			Finished	=	false;
	int				counter		=	0;
	
	public CounterThread(MainActivity parent)
	{
		super();
		this.parent	=	parent;
	}
	
	public void run()
	{
		while (!Finished)
		{
			try									{	sleep(1000);			counter++;	}
			catch (InterruptedException e)		{	e.printStackTrace();				}
			
			parent.runOnUiThread(new 	Runnable()
										{
											public void run()
											{
												parent.ctrlThread.setText(Integer.toString(counter));
											}
										});
		}
	}
	
	public void restorestate()
	{
		
	}
	
	public void savestate()
	{
		
	}
}