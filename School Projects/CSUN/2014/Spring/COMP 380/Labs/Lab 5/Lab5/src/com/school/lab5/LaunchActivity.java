package com.school.lab5;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;

public class LaunchActivity extends Activity
{
	
	@Override protected void onCreate(	Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_launch);
	}
	
	@Override public boolean onCreateOptionsMenu(	Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.launch, menu);
		return true;
	}
	
	public void messageSend(View view)
	{
		Intent displayMessageIntent = new Intent(this, Message_Display.class);
		EditText inputMessage = (EditText) findViewById(R.id.ctrlInput);
		String	strMessage = inputMessage.getText().toString();
		
		displayMessageIntent.putExtra("com.school.lab5.MESSAGE", strMessage);
		startActivity(displayMessageIntent);
	}	
}
