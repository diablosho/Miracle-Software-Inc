package com.example.lifecycle;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.Menu;
import android.widget.Toast;

public class MainActivity extends Activity
{
	Context			context;
	Toast			toast;
	enum			AppProcess
					{
						onCreate,
						onStart,
						onCreateOptionsMenu,
						onRestoreInstanceState,
						onResume,
						onSaveInstanceState,
						onPause,
						onStop,
						onDestroy,
						onRestart
					}
	AppProcess		previousProcess	=	AppProcess.onCreate;
	
	@Override protected void onCreate(	Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		context =	getApplicationContext();
		
		if 		(previousProcess != AppProcess.onDestroy)	displayToast("We are now creating the Activity...");
		else 												displayToast("We are now re-creating the Activity...");
		
		previousProcess	=	AppProcess.onCreate;
	}
	
	public void onStart()
	{
		super.onStart();
		
		if (previousProcess	!= AppProcess.onRestart)	displayToast("We are now starting the Activity...");
		else											displayToast("We are now re-starting the Activity...");
		
		previousProcess	=	AppProcess.onStart;
	}
	
	@Override public boolean onCreateOptionsMenu(	Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		
		displayToast("The Activity has been created, so now we are creating the Options Menu via onCreateOptionsMenu()");
		previousProcess	=	AppProcess.onCreateOptionsMenu;
		
		return true;
	}
	
	public void onRestoreInstanceState(Bundle savedInstanceState)
	{
		super.onRestoreInstanceState(savedInstanceState);
		
		displayToast("We are now restoring the Activity's information to resume the Application...");
		previousProcess	=	AppProcess.onRestoreInstanceState;
	}
	
	public void onResume()
	{
		super.onResume();
		
		if (previousProcess != AppProcess.onPause)	displayToast("The Activity is resuming because it is regaining focus");
		else										displayToast("The Activity is resuming after changing screen orientation");
				
		previousProcess	=	AppProcess.onResume;
	}
	
	public void onSaveInstanceState(Bundle savedInstanceState)
	{
		super.onSaveInstanceState(savedInstanceState);
		
		displayToast("We are now saving the Activity's information to pause the Application...");
		previousProcess	=	AppProcess.onSaveInstanceState;
	}
	
	public void onPause()
	{
		super.onPause();
		
		displayToast("The Activity has been paused...");
		previousProcess	=	AppProcess.onPause;
	}
	
	public void onStop()
	{
		super.onStop();
		
		displayToast("The Activity is stopping...");
		previousProcess	=	AppProcess.onStop;
	}
	
	public void onRestart()
	{
		super.onRestart();
		
		displayToast("The Activity is restarting...");
		previousProcess	=	AppProcess.onRestart;
	}
	
	public void onDestroy()
	{
		super.onDestroy();
		
		displayToast("The Activity is being destroyed...");
		previousProcess	=	AppProcess.onDestroy;
	}
	
	public void displayToast(CharSequence stringToDisplay)
	{
		toast	=	Toast.makeText(context, stringToDisplay, Toast.LENGTH_SHORT);
		toast.show();
	}
}