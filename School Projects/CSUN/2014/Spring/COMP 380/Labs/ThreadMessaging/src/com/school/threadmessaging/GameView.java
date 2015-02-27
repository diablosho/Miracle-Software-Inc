package com.school.threadmessaging;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.Parcelable;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GameView extends SurfaceView implements Runnable, SurfaceHolder.Callback
{	
	private Game	game	= null;
	private Bitmap	bitmap;
			Canvas	canvas;
	private double	x, y;
	
	SurfaceHolder	surface;
	Context			context;
	Handler			handlerUI,
					handlerGame,
					handlerInput,
					handlerView	=	new	Handler()
					{
						public void handleMessage(Message msg)
						{
				            Bundle	msgData	=	msg.getData();
				            Note	note	=	(Note) msg.getData().get("View");
				            
				            switch (note.message)
				            {
				            case "Prepare Fresh View":									break;
				            case "Move Snake":			setPos(note);	draw(canvas);	break; 
				            default:													break;
				            }
							super.handleMessage(msg);
				        }
					};	
					
	public GameView(Context context, UI ui)
	{
		super(context);
		
		this.context	=	context;
						
		bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.ic_launcher);
		surface	=	getHolder();
		surface.addCallback(this);
			
		x = 50;
		y = 50;
	}
	
	@Override public void run()
	{
		Looper.prepare();
		Looper.loop();
	}
	
	@Override public void surfaceChanged(	SurfaceHolder holder, int format, int width, int height)	{	}
	@Override public void surfaceCreated(	SurfaceHolder holder)
	{
		sendNote("Game", "setRunnable(true)");
		//game.setRunnable(true);
	}
	@Override public void surfaceDestroyed(	SurfaceHolder holder)
	{
		boolean retry = true;
		sendNote("Game", "setRunnable(false)");
		//game.setRunnable(false);
		while (retry)
		{
			try
			{
				game.join();
				retry = false;
			}
			catch (InterruptedException ie){}
			break;
		}
		game = null;
	}
	
	public void setPos(Note note)
	{
		x = note.data[0];
		y = note.data[1];
	}
	
	public void draw(	Canvas canvas)
	{
		canvas.drawColor(Color.WHITE);
		canvas.drawBitmap(bitmap, (float) x, (float) y, null);
	}
	
	public void onDraw(	Canvas canvas)
	{
		super.onDraw(canvas);
		draw(canvas);
	}
	
	public Handler getHandler()	{	return handlerView;	}
	
	public void setHandlers(Handler ui, Handler handlerview, Handler handlergame, Handler handlerinput)
	{
		this.handlerUI		=	ui;
		this.handlerGame	=	handlergame;
		this.handlerInput	=	handlerinput;
	}
	
	public void sendNote(String destination, String message)
	{
		Note	note	=	new	Note("View", destination, message);
		Bundle	bundle	=	new	Bundle();
		Message msg		=	Message.obtain();
		
		bundle.putParcelable(destination, (Parcelable) note);
		msg.setData(bundle);
		
		switch (destination)
		{
		case "UI":		msg.setTarget(handlerUI);		break;
		case "Game":	msg.setTarget(handlerGame);		break;
		case "Input":	msg.setTarget(handlerInput);	break;
		default:										break;
		}
		msg.sendToTarget();
	}
}