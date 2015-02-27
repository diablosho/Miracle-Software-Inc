package com.school.snake;

import com.school.snake.R;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

public class UI_Mainframe extends Activity
{
	Thread				threadFramework;
	FrameworkHandler	handlerFramework;
	ViewHandler			handlerView;
	
	TextView			ctrlStrX,
						ctrlStrY,
						ctrlStrZ,
						ctrlStrCos,
						ctrlStrHeading;
	
	boolean				gameOver	=	false;
	boolean				gameRunning	=	false;
	boolean				exitApp		=	false;
	
	@Override protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		//setContentView(R.layout.activity_ui_mainframe);
		handlerView		=	new	ViewHandler(this);
		setContentView(handlerView);
		
		/*ctrlStrX		=	(TextView) findViewById(R.id.strX);
		ctrlStrY		=	(TextView) findViewById(R.id.strY);
		ctrlStrZ		=	(TextView) findViewById(R.id.strZ);
		ctrlStrCos		=	(TextView) findViewById(R.id.strCos);
		ctrlStrHeading	=	(TextView) findViewById(R.id.strHeading);*/
		
		handlerFramework	=	new FrameworkHandler(this, this);
		threadFramework		=	new	Thread(handlerFramework);
		threadFramework.start();
	}
	
	@Override public synchronized boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.ui_mainframe, menu);
		return true;
	}

	@Override public synchronized boolean onOptionsItemSelected(	MenuItem item)
	{
		switch (item.getItemId())
		{
			case R.id.new_game:
			{
				handlerFramework.newGame();
				return true;
			}
			case R.id.exit_game:
			{
				handlerFramework.exitApp();
				handlerView.destroyView();
				finish();
				return true;
			}
			default:
				return super.onOptionsItemSelected(item);
		}
	}
	
	public void onPause()
	{
		super.onPause();
		handlerView.onPauseViewHandler();
	}
	
	public void onResume()
	{
		super.onResume();
		handlerView.onResumeViewHandler();
	}
}