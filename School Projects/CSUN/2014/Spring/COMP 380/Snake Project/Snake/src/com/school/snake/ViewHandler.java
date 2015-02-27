package com.school.snake;

import java.util.Random;

import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.opengl.GLSurfaceView;
import android.opengl.GLUtils;
import android.view.SurfaceHolder;

public class ViewHandler extends GLSurfaceView implements SurfaceHolder.Callback, Runnable
{
	volatile boolean	running	=	false;
	Thread				thread;
	Context 			context;
	SurfaceHolder		holderSurface;
	Paint				paint;
	Bitmap				bitmap;
	Random				random;
	Canvas				canvas;
	
	public ViewHandler(Context context)
	{
		super(context);
		this.context	=	context;
		paint			=	new	Paint(Paint.ANTI_ALIAS_FLAG);
		holderSurface	=	getHolder();
		random			=	new	Random();
		
		bitmap		=	Bitmap.createBitmap(256, 256, Bitmap.Config.ARGB_4444);
		canvas			=	new Canvas(bitmap);
		bitmap.eraseColor(0);
		paint.setARGB(0xff, 0x00, 0x00, 0x00);
		GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);
		bitmap.recycle();
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
			
	@Override public synchronized void run()
	{
		while (running)
		{
			if (holderSurface.getSurface().isValid())
			{
				canvas = LockCanvas();
				// ... actual drawing on canvas
				
				paint.setStyle(Paint.Style.STROKE);
				paint.setStrokeWidth(3);
				
				int width = canvas.getWidth();
				int height = canvas.getHeight();
				
				int x = random.nextInt(width - 1);
				int y = random.nextInt(height - 1);
				int r = random.nextInt(255);
				int g = random.nextInt(255);
				int b = random.nextInt(255);
				paint.setColor(0xff000000 + ( r << 16 ) + ( g << 8 ) + b);
				canvas.drawPoint(x, y, paint);
								
				unlockCanvas();
			}
		}
	}
	
	public Canvas LockCanvas()
	{
		Canvas canvas = holderSurface.lockCanvas();
		return canvas;
	}
	
	public void unlockCanvas()
	{
		holderSurface.unlockCanvasAndPost(canvas);
	}
	
	public void printText(float leftX, float topY, String stringToWrite, int color)
	{
		paint.setColor(color);
		paint.setTextSize(36);
		canvas.drawText(stringToWrite, leftX, topY, paint);
	}
	
	public void drawRect(float startX, float startY, float endX, float endY, int color)
	{
		paint.setColor(color);
		canvas.drawRect(startX, startY, endX, endY, paint);
	}
	
	public void destroyView()
	{
		thread.interrupt();
	}
	
	@Override public void surfaceChanged(	SurfaceHolder arg0, int arg1, int arg2, int arg3)	{	}
	@Override public void surfaceCreated(	SurfaceHolder arg0)									{	}
	@Override public void surfaceDestroyed(	SurfaceHolder arg0)									{	}
}