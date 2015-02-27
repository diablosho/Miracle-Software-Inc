package com.school.lab5;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.widget.TextView;

public class Message_Display extends Activity
{
	
	@Override protected void onCreate(	Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		
		Intent getMessageIntent	=	getIntent();
		String message = getMessageIntent.getStringExtra("com.school.lab5.MESSAGE");
		setContentView(R.layout.activity_message__display);
		TextView viewText = (TextView) findViewById(R.id.strMessageToDisplay);
		//viewText.setTextSize(40);
		viewText.setText(message);		
	}
	
	@Override public boolean onCreateOptionsMenu(	Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.message__display, menu);
		return true;
	}
	
}
