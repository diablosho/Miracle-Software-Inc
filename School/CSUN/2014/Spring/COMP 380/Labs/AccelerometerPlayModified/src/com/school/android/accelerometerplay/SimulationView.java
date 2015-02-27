package com.school.android.accelerometerplay;

import com.example.android.accelerometerplay.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.BitmapFactory.Options;
import android.util.DisplayMetrics;
import android.view.View;

public class SimulationView extends View
{
	protected	AccelerometerPlayActivity	ui;
	
	// diameter of the balls in meters
	static final float		sBallDiameter	= 0.004f;
	static final float		sBallDiameter2	= sBallDiameter * sBallDiameter;
		
	private float			mXDpi;
	private float			mYDpi;
	private float			mMetersToPixelsX;
	private float			mMetersToPixelsY;
	private Bitmap			mBitmap;
	private Bitmap			mWood;
	private float			mXOrigin;
	private float			mYOrigin;
			float			mHorizontalBound;
			float			mVerticalBound;
	
	private ParticleSystem	mParticleSystem;
	
	public SimulationView(AccelerometerPlayActivity ui, Context context)
	{
		super(context);
		this.ui	=	ui;
		mParticleSystem	= new ParticleSystem(ui);
		
		DisplayMetrics metrics = new DisplayMetrics();
		ui.getWindowManager().getDefaultDisplay().getMetrics(metrics);
		mXDpi = metrics.xdpi;
		mYDpi = metrics.ydpi;
		mMetersToPixelsX = mXDpi / 0.0254f;
		mMetersToPixelsY = mYDpi / 0.0254f;
		
		// rescale the ball so it's about 0.5 cm on screen
		Bitmap ball = BitmapFactory.decodeResource(getResources(), R.drawable.ball);
		final int dstWidth = (int) ( sBallDiameter * mMetersToPixelsX + 0.5f );
		final int dstHeight = (int) ( sBallDiameter * mMetersToPixelsY + 0.5f );
		mBitmap = Bitmap.createScaledBitmap(ball, dstWidth, dstHeight, true);
		
		Options opts = new Options();
		opts.inDither = true;
		opts.inPreferredConfig = Bitmap.Config.RGB_565;
		mWood = BitmapFactory.decodeResource(getResources(), R.drawable.wood, opts);
	}
	
	public void startSimulation()
	{
		/* It is not necessary to get accelerometer events at a very high rate, by using a slower rate
		 * (SENSOR_DELAY_UI), we get an automatic low-pass filter, which "extracts" the gravity component of
		 * the acceleration. As an added benefit, we use less power and CPU resources. */
		ui.startListeningForInput();
	}
	
	public void stopSimulation()
	{
		ui.stopListeningForInput();
	}
	
	@Override protected void onSizeChanged(	int w, int h, int oldw, int oldh)
	{
		// compute the origin of the screen relative to the origin of the bitmap
		mXOrigin = ( w - mBitmap.getWidth() ) * 0.5f;
		mYOrigin = ( h - mBitmap.getHeight() ) * 0.5f;
		mHorizontalBound = ( ( w / mMetersToPixelsX - sBallDiameter ) * 0.5f );
		mVerticalBound = ( ( h / mMetersToPixelsY - sBallDiameter ) * 0.5f );
	}
	
	@Override protected void onDraw(Canvas canvas)
	{
		canvas.drawBitmap(mWood, 0, 0, null);	//	Draw the background
		
		/* compute the new position of our object, based on accelerometer data and present time. */
		final ParticleSystem particleSystem = mParticleSystem;
				
		particleSystem.update(ui.getSx(), ui.getSy(), ui.getNow());
		
		final float xc = mXOrigin;
		final float yc = mYOrigin;
		final float xs = mMetersToPixelsX;
		final float ys = mMetersToPixelsY;
		final Bitmap bitmap = mBitmap;
		final int count = particleSystem.getParticleCount();
		
		for (int i = 0; i < count; i++ )
		{
			/* We transform the canvas so that the coordinate system matches the sensors coordinate system
			 * with the origin in the center of the screen and the unit is the meter. */
			
			final float x = xc + particleSystem.getPosX(i) * xs;
			final float y = yc - particleSystem.getPosY(i) * ys;
			canvas.drawBitmap(bitmap, x, y, null);
		}
		
		invalidate();	// and make sure to redraw asap
	}
}