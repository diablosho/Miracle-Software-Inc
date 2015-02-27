package com.school.lab9;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity
{
	CounterThread	cntThread;
	CounterService	cntService;
	TextView		ctrlThread,
					ctrlService;
	
	@Override protected void onCreate(	Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		ctrlThread	=	(TextView) findViewById(R.id.strThreadCounter);
		ctrlService	=	(TextView) findViewById(R.id.strServicesCounter);
	}
	
	@Override public boolean onCreateOptionsMenu(	Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	public void onStart()
	{
		super.onStart();
		
		cntThread	=	new	CounterThread(this);
		cntService	=	new	CounterService(this);
		
		cntThread.start();
	}
	
	public void onResume()
	{
		super.onResume();
		cntThread.restorestate();
	}
	
	public void onPause()
	{
		super.onPause();
		cntThread.savestate();
		cntThread.interrupt();
	}
	
	public void onStop()
	{
		super.onStop();
		cntThread.Finished	=	true;
		cntThread.interrupt();
	}
}