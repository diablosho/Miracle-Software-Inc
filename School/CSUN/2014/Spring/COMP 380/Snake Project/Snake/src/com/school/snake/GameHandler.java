package com.school.snake;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.SurfaceTexture;
import android.view.TextureView.SurfaceTextureListener;

public class GameHandler extends Thread implements SurfaceTextureListener
{	
	FrameworkHandler	framework;
	
	volatile boolean	exitApp		=	false,
						gameOver	=	false,
						gameRunning	=	false;
	
	double				x,		y,		z;
	String				strX,	strY,	strZ;
	Canvas				canvas;
		
	public GameHandler(FrameworkHandler framework)
	{
		this.framework		=	framework;
		x		=	y		=	z		=	0;
		strX	=	strY	=	strZ	=	"";
	}
	
	public synchronized void run()
	{
		while (!exitApp)
		{
			if (gameRunning)
			{
				try
				{
					canvas	=	framework.threadUI.handlerView.LockCanvas();
					framework.threadUI.handlerView.printText(50,50,strX, Color.BLACK);
					framework.threadUI.handlerView.printText(50,100,strY, Color.BLACK);
					framework.threadUI.handlerView.printText(50,150,strZ, Color.BLACK);
					framework.threadUI.handlerView.unlockCanvas();
									
					x		=	framework.handlerInput.getX();
					y		=	framework.handlerInput.getY();
					z		=	framework.handlerInput.getZ();
					strX	=	"X:  Theta = " + String.valueOf(x);
					strY	=	"Y:  Theta = " + String.valueOf(y);
					strZ	=	"Z:  Theta = " + String.valueOf(z);
					
					canvas	=	framework.threadUI.handlerView.LockCanvas();
					framework.threadUI.handlerView.printText(50,50,strX, Color.WHITE);
					framework.threadUI.handlerView.printText(50,100,strY, Color.WHITE);
					framework.threadUI.handlerView.printText(50,150,strZ, Color.WHITE);
					framework.threadUI.handlerView.unlockCanvas();
					
					sleep(1000);
				}
				catch (InterruptedException e)
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
			if (gameOver)
			{
				gameRunning	=	false;
				endGame();
			}
		}
	}
	
	public void terminate()
	{
		endGame();
		interrupt();
	}
	
	public void startGame()
	{
		gameRunning	=	true;
		gameOver	=	false;
		exitApp		=	false;
	}
	
	public void endGame()
	{
		exitApp		=	false;
		gameOver	=	false;
		gameRunning	=	false;
	}

	@Override public void onSurfaceTextureAvailable(SurfaceTexture arg0, int arg1, int arg2)
	{
		// TODO Auto-generated method stub
		
	}

	@Override public boolean onSurfaceTextureDestroyed(	SurfaceTexture arg0)
	{
		// TODO Auto-generated method stub
		return false;
	}

	@Override public void onSurfaceTextureSizeChanged(	SurfaceTexture arg0, int arg1, int arg2)
	{
		// TODO Auto-generated method stub
		
	}

	@Override public void onSurfaceTextureUpdated(	SurfaceTexture arg0)
	{
		// TODO Auto-generated method stub
		
	}
}