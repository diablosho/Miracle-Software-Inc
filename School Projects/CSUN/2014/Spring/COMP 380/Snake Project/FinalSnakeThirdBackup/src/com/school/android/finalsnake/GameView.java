package com.school.android.finalsnake;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Canvas;
import android.util.DisplayMetrics;
import android.view.View;

public class GameView extends View	implements	Runnable
{
	static	MainActivity	ui;
	static	DisplayMetrics	metrics;
	private float			mXDpi;
	private float			mYDpi;
	private float			mMetersToPixelsX;
	private float			mMetersToPixelsY;
	private Bitmap			bmpBackground;
			float			mXOrigin;
			float			mYOrigin;
	 		Snake			snake;
			float			mHorizontalBound;
			float			mVerticalBound;
			int				screenBoundsPixelsX;
			int				screenBoundsPixelsY;
	
	public GameView(MainActivity ui, Context context)
	{
		super(context);
		GameView.ui	=	ui;
		snake	= new Snake(GameView.ui);
		snake.start();
		
		metrics = new DisplayMetrics();
		GameView.ui.getWindowManager().getDefaultDisplay().getMetrics(metrics);
		mXDpi = metrics.xdpi;
		mYDpi = metrics.ydpi;
		mMetersToPixelsX 		=	mXDpi / 0.0254f;
		mMetersToPixelsY 		=	mYDpi / 0.0254f;
		screenBoundsPixelsX		=	metrics.widthPixels;
		screenBoundsPixelsY		=	metrics.heightPixels;
				
		// rescale the ball so it's about 0.5 cm on screen
		snake.bmpSnake = BitmapFactory.decodeResource(getResources(), R.drawable.headisleft);
		final int dstWidth = (int) ( snake.bodyDiameter * mMetersToPixelsX + 0.5f );
		final int dstHeight = (int) ( snake.bodyDiameter * mMetersToPixelsY + 0.5f );
		snake.bmpSnake = Bitmap.createScaledBitmap(snake.bmpSnake, dstWidth, dstHeight, true);
		
		Options opts = new Options();
		opts.inDither = true;
		opts.inPreferredConfig = Bitmap.Config.RGB_565;
		bmpBackground 	=	BitmapFactory.decodeResource(getResources(), R.drawable.backgroundimage, opts);
		bmpBackground	=	Bitmap.createScaledBitmap(bmpBackground, screenBoundsPixelsX, screenBoundsPixelsY, true);
	}
		
	public void startSimulation()	{	ui.startListeningForInput();	}
	public void stopSimulation()	{	ui.stopListeningForInput();		}
	
	@Override protected void onSizeChanged(	int w, int h, int oldw, int oldh)
	{
		mXOrigin 			=	( w - snake.bmpSnake.getWidth() ) * 0.5f;
		mYOrigin 			=	( h - snake.bmpSnake.getHeight() ) * 0.5f;
		mHorizontalBound	=	( ( w / mMetersToPixelsX - snake.bodyDiameter ) * 0.5f );
		mVerticalBound 		=	( ( h / mMetersToPixelsY - snake.bodyDiameter ) * 0.5f );
		screenBoundsPixelsX	=	metrics.widthPixels;
		screenBoundsPixelsY	=	metrics.heightPixels;
		bmpBackground		=	Bitmap.createScaledBitmap(bmpBackground, screenBoundsPixelsX, screenBoundsPixelsY, true);
	}
	
	@Override protected void onDraw(Canvas canvas)
	{
		canvas.drawBitmap(bmpBackground, 0, 0, null);
		
		if (snake != null)
		{
			snake.moveSnake	(GameView.ui.input.mSensorX, GameView.ui.input.mSensorY, 
			               	(GameView.ui.input.mAccelTimeStamp + ( System.nanoTime() - GameView.ui.input.mAccelCpuTimeStamp )));
			
			final float xc = mXOrigin;
			final float yc = mYOrigin;
			final float xs = mMetersToPixelsX;
			final float ys = mMetersToPixelsY;
		
			/* We transform the canvas so that the coordinate system matches the sensors coordinate system
			 * with the origin in the center of the screen and the unit is the meter. */
			
			final float x = xc + snake.mPosX * xs;
			final float y = yc - snake.mPosY * ys;
			canvas.drawBitmap(snake.bmpSnake, x, y, null);				
		}
		invalidate();
	}

	@Override public void run()	{	}
}