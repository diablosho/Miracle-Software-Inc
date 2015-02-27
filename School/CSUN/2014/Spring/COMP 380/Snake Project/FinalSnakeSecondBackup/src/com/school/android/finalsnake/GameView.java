package com.school.android.finalsnake;

import java.io.IOException;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.DisplayMetrics;
import android.view.View;

public class GameView extends View
{
	static 	MainActivity	ui;
			AssetManager	Assets;
					
			float			screenBoundsPixelX;
			float			screenBoundsPixelY;
			Bitmap			bmpBackground;
			float			originX;
			float			originY;
			float			screenBoundsMetersToPixelsX,
							screenBoundsMetersToPixelsY;
			SnakesNest		nest;
			Bitmap			temp;
	
	public GameView(MainActivity ui, Context context)
	{
		super(context);
		Assets						=	context.getAssets();
		GameView.ui					=	ui;
						
		DisplayMetrics metrics		=	new DisplayMetrics();
		ui.getWindowManager().getDefaultDisplay().getMetrics(metrics);
		
		float	XDpi				=	metrics.xdpi;
		float	YDpi				=	metrics.ydpi;
						
		screenBoundsPixelX			=	metrics.widthPixels;
		screenBoundsPixelY			=	metrics.heightPixels;
			
		screenBoundsMetersToPixelsX	=	XDpi / 0.0254f;
		screenBoundsMetersToPixelsY	=	YDpi / 0.0254f;
		         
		nest						= 	new SnakesNest(ui);
		nest.snake.setPosition((int) (screenBoundsPixelX / 2.0f), (int) (screenBoundsPixelY / 2.0f));
		        
		try
		{
			bmpBackground	=	Bitmap.createScaledBitmap(BitmapFactory.decodeStream(Assets.open("backgroundimage.png")), metrics.widthPixels, metrics.heightPixels, false);
			temp			=	Bitmap.createBitmap(BitmapFactory.decodeStream(Assets.open("headisleft.png")));
			nest.snake.setBitmap(temp);	//	re-scale the Snake Head so it's about 0.5 cm on screen
		}
		catch (IOException e)		{	e.printStackTrace();			}
	}
		
	public void startSimulation()	{	ui.startListeningForInput();	}
	public void stopSimulation()	{	ui.stopListeningForInput();		}
	
	@Override protected void onSizeChanged(	int w, int h, int oldw, int oldh)
	{
		originX 			= 	( w - nest.snake.snakeHeadWidth 	) * 0.5f;
		originY 			= 	( h - nest.snake.snakeHeadHeight	) * 0.5f;
		screenBoundsPixelX	=	w;
		screenBoundsPixelY	=	h;
	}
	
	@Override protected void onDraw(Canvas canvas)
	{
		canvas.drawBitmap(bmpBackground, 0, 0, null);	//	Draw the background
		
		/* compute the new position of our object, based on accelerometer data and present time. */
		final long now = ui.input.mAccelTimeStamp + ( System.nanoTime() - ui.input.mAccelCpuTimeStamp );
		final float sensorX = ui.input.mSensorX;
		final float sensorY = ui.input.mSensorY;
		nest.update(sensorX, sensorY, now);
		final SnakesNest snakesNest = nest;
		
		canvas.drawBitmap(snakesNest.snake.bmpSnake, snakesNest.snake.prepareBitmap(canvas), null);
				
		invalidate();	// and make sure to redraw asap
	}
}