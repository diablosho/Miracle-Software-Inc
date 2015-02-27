package com.school.snake;

import java.util.Random;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class ViewHandler extends SurfaceView implements SurfaceHolder.Callback, Runnable
{
	Thread				thread;
	Context 			context;
	SurfaceHolder		holderSurface;
	Bitmap				image;
	Paint				paint;
	Random				random;
	volatile boolean	running	=	false;

	public ViewHandler(Context context)
	{
		super(context);
		this.context	=	context;
		paint			=	new	Paint(Paint.ANTI_ALIAS_FLAG);
		holderSurface	=	getHolder();
		random			=	new	Random();
	}
	
	public void onResumeViewHandler()
	{
		running = true;
		thread = new Thread(this);
		thread.start();
	}
	
	public void onPauseViewHandler()
	{
		boolean retry = true;
		running = false;
		while (retry)
		{
			try
			{
				thread.join();
				retry = false;
			}
			catch (InterruptedException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
			
	@Override public void run()
	{
		while (running)
		{
			if (holderSurface.getSurface().isValid())
			{
				Canvas canvas = holderSurface.lockCanvas();
				// ... actual drawing on canvas
				
				paint.setStyle(Paint.Style.STROKE);
				paint.setStrokeWidth(3);
				
				int w = canvas.getWidth();
				int h = canvas.getHeight();
				int x = random.nextInt(w - 1);
				int y = random.nextInt(h - 1);
				int r = random.nextInt(255);
				int g = random.nextInt(255);
				int b = random.nextInt(255);
				paint.setColor(0xff000000 + ( r << 16 ) + ( g << 8 ) + b);
				canvas.drawPoint(x, y, paint);
				
				holderSurface.unlockCanvasAndPost(canvas);
			}
		}
	}
	
	public void destroyView()
	{
		thread.interrupt();
	}
	
	@Override public void surfaceChanged(	SurfaceHolder arg0, int arg1, int arg2, int arg3)	{	}
	@Override public void surfaceCreated(	SurfaceHolder arg0)									{	}
	@Override public void surfaceDestroyed(	SurfaceHolder arg0)									{	}
}