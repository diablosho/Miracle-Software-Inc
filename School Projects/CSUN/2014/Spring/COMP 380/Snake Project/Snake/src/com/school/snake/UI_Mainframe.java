package com.school.snake;

import com.school.snake.R;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;

public class UI_Mainframe extends Activity
{
	Thread				threadFramework;
	Thread				threadView;
	FrameworkHandler	handlerFramework;
	ViewHandler			handlerView;
	
	boolean				gameOver	=	false;
	boolean				gameRunning	=	false;
	boolean				exitApp		=	false;
	
	@Override protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		handlerView		=	new	ViewHandler(this);
		threadView		=	new	Thread(handlerView);
		threadView.start();
		setContentView(handlerView);
		
		handlerFramework	=	new FrameworkHandler(this, this);
		handlerFramework.start();
		//threadFramework		=	new	Thread(handlerFramework);
		//threadFramework.start();
	}
	
	@Override public boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.ui_mainframe, menu);
		return true;
	}

	@Override public boolean onOptionsItemSelected(	MenuItem item)
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