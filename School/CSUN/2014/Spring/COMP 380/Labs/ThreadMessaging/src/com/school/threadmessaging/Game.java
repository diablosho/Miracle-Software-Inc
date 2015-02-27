package com.school.threadmessaging;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.Parcelable;
import android.view.SurfaceHolder;

public class Game	extends	Thread
{	
	private 	SurfaceHolder	surfaceHolder;
	private 	GameView		view;
	
	private 	boolean			run	= false;
	
				double			posX,
								posY,
								posZ;
	
				double[]		data	=	new	double[3];
				Handler			handlerUI,
								handlerView,
								handlerInput,
								handlerGame	=	new	Handler()
								{
									public void handleMessage(Message msg)
									{
										super.handleMessage(msg);
										
										Bundle	msgData	=	msg.getData();
							            Note	note	=	(Note) msg.getData().get("Game");
							            
							            switch (note.message)
							            {
							            	case "New Game":			startNewGame();			break;
							            	case "Pause Game":			pauseGame();			break;
							            	case "Resume Game":			resumeGame();			break;
							            	case "End Game":			endGame();				break;
							            	case "Current Input":		retrieveInput(note);	break;	//	Retrieving requested data
							            	case "setRunnable(true)":	setRunnable(true);		break;
							            	case "setRunnable(false)":	setRunnable(false);		break;
							            	default:											break;
							            }
							        }
								};
			
	public Game(SurfaceHolder surfaceHolder, GameView view)
	{
		super();
		this.surfaceHolder = surfaceHolder;
		this.view = view;
	}
	
	public void setRunnable(boolean run)
	{
		this.run = run;
	}
	
	public void run()
	{
		super.run();
		Looper.prepare();
		Looper.loop();
		
		while (run)
		{
			view.canvas = null;
			try
			{
				view.canvas = surfaceHolder.lockCanvas(null);
				synchronized (surfaceHolder)
				{
					view.draw(view.canvas);
					Thread.sleep(300);
				}
			}
			catch (Exception e)	{}
			finally
			{
				if (view.canvas != null)
				{
					surfaceHolder.unlockCanvasAndPost(view.canvas);
				}
			}
		}
	}
	
	public Handler getHandler()	{	return handlerGame;	}
	public void setHandlers(Handler ui, Handler handlerview, Handler handlergame, Handler handlerinput)
	{
		this.handlerUI		=	ui;
		this.handlerView	=	handlerview;
		this.handlerInput	=	handlerinput;
	}
	
	public void startNewGame()	//	Initialize New Game here
	{
		//sendNote("View", "Prepare Fresh View", null);
		setRunnable(true);
		playGame();
	}
	public void getCurrentPosition()
	{
		sendNote("Input", "Get Input", data);
	}
	public void playGame()		//	Play game here
	{
		getCurrentPosition();
		outputPosition();
	}	
	public void outputPosition()
	{
		sendNote("View", "Move Snake", data);
		playGame();
	}
	
	public void pauseGame()		{}
	public void resumeGame()	{}
	public void endGame()		{}
	public void retrieveInput(Note note)
	{
		data	=	note.data;
		posX	=	note.data[0];
		posY	=	note.data[1];
		posZ	=	note.data[2];
	}
	public void sendNote(String destination, String message, double[] data)
	{
		Note	note	=	new	Note("Game", destination, message);
		Bundle	bundle	=	new	Bundle();
		Message msg		=	Message.obtain();
		
		bundle.putParcelable(destination, (Parcelable) note);
		msg.setData(bundle);
		
		switch (destination)
		{
		case "View":	msg.setTarget(handlerView);		break;
		case "UI":		msg.setTarget(handlerUI);		break;
		case "Input":	msg.setTarget(handlerInput);	break;
		default:										break;
		}
		msg.sendToTarget();
	}
}