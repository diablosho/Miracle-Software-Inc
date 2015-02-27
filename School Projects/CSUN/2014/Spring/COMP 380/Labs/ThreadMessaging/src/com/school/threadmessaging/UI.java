package com.school.threadmessaging;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.Parcelable;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;

public class UI extends ActionBarActivity
{	
	
	private GameView	view;
			Game		game;
			Input		input;
			Thread		threadView,
						threadGame,
						threadInput;
			Handler		handlerView,
						handlerGame,
						handlerInput,
						handlerUI	=	new	Handler()
						{
							public void handleMessage(Message msg)
							{
					            Bundle	msgData	=	msg.getData();
					            Note	note	=	(Note) msg.getData().get("UI");
					            
					            switch (note.message)
					            {
					            	case "Game Over":								break;
					            	default:			super.handleMessage(msg);	break;
					            }
								super.handleMessage(msg);
					        }
						};
	
	@Override protected void onCreate(	Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
				
		view				=	new	GameView(this.getBaseContext(), this);
		game				=	new Game(view.surface, view);
		input				=	new	Input(this);
		
		threadView			=	new Thread(view);
		threadGame			=	new	Thread(game);
		threadInput			=	new	Thread(input);
		
		threadView.start();
		threadGame.start();
		threadInput.start();
		
		handlerView			=	view.getHandler();
		handlerGame			=	game.getHandler();
		handlerInput		=	input.getHandler();
		
		setHandlers(handlerUI, handlerView, handlerGame, handlerInput);
		
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(view);
				
		//	The Game, View, Input, and UI threads now have each other's handlers, so they can directly communicate
	}
	@Override public boolean onCreateOptionsMenu(	Menu menu)
	{		
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.ui, menu);
		return true;
	}
	@Override public boolean onOptionsItemSelected(	MenuItem item)
	{
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		//int id = item.getItemId();
		
		switch (item.getItemId())
		{
		case R.id.newgame:	sendNote("Game", "New Game");	break;
		}
		
		//if (id == R.id.action_settings) { return true; }
		return super.onOptionsItemSelected(item);
	}
	public void onStart()
	{
		super.onStart();
	}
	
	public Handler getHandler()
	{
		return handlerUI;
	}	
	
	public void setHandlers(Handler ui, Handler handlerview, Handler handlergame, Handler handlerinput)
	{
		view.setHandlers(ui, handlerview, handlergame, handlerinput);
		game.setHandlers(ui, handlerview, handlergame, handlerinput);
		input.setHandlers(ui, handlerview, handlergame, handlerinput);
	}

	public void sendNote(String destination, String message)
	{
		Note	note	=	new	Note("UI", destination, message);
		Bundle	bundle	=	new	Bundle();
		Message msg		=	Message.obtain();
		
		bundle.putParcelable(destination, (Parcelable) note);
		msg.setData(bundle);
		
		switch (destination)
		{
		case "View":	msg.setTarget(handlerView);	break;
		case "Game":	msg.setTarget(handlerGame);	break;
		default:									break;
		}
		msg.sendToTarget();
	}
}
