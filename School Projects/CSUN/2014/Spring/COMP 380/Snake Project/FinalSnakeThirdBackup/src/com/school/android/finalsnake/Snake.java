package com.school.android.finalsnake;

import android.graphics.Bitmap;
import android.graphics.Matrix;

public class Snake	extends	Thread	//	Each Snake holds their own previous and current positions and their own acceleration. For added realism each Snake has its own friction coefficient.
{	
	private	Matrix			snakeHeadAngleMatrix	=	new Matrix();
			MainActivity	ui;
			private long	mLastT;
			private float	mLastDeltaT;
			float			bodyDiameter;
			float			mPosX;
			float			mPosY;
			float			mAccelX					=	1.0f;
			float			mAccelY					=	1.0f;
			float			mLastPosX;
			float			mLastPosY;
			float			mOneMinusFriction;
			float			RotationAngle;
			Bitmap			bmpSnake;			
			
	Snake(MainActivity ui)
	{
		this.ui	=	ui;
	}
	
	/* Performs one iteration of the simulation. First updating the position of all the particles and
	 * resolving the constraints and collisions. */
	public void moveSnake(	float sx, float sy, long now)
	{
		final long t = now;
		if (mLastT != 0)
		{
			final float dT = (float) ( t - mLastT ) * ( 1.0f / 1000000000.0f );
			if (mLastDeltaT != 0)
			{
				final float dTC = dT / mLastDeltaT;
				final float dTdT = dT * dT;
				final float x = mPosX + mOneMinusFriction * dTC * ( mPosX - mLastPosX ) + mAccelX * dTdT;
				final float y = mPosY + mOneMinusFriction * dTC * ( mPosY - mLastPosY ) + mAccelY * dTdT;
				mLastPosX = mPosX;
				mLastPosY = mPosY;
				mPosX = x;
				mPosY = y;
			}
			mLastDeltaT = dT;
		}
		mLastT = t;
		
		resolveCollisionWithBounds();	//	Make sure the snake doesn't intersect with the walls.
		//rotateSnake();
	}
	
	/* Resolving constraints and collisions with the Verlet integrator can be very simple, we simply
	 * need to move a colliding or constrained particle in such way that the constraint is satisfied. */
	public void resolveCollisionWithBounds()
	{
		final float xmax = ui.gameView.mHorizontalBound;
		final float ymax = ui.gameView.mVerticalBound;
		final float x = mPosX;
		final float y = mPosY;
		if (x > xmax)
		{
			mPosX = xmax;
		}
		else if (x < -xmax)
		{
			mPosX = -xmax;
		}
		if (y > ymax)
		{
			mPosY = ymax;
		}
		else if (y < -ymax)
		{
			mPosY = -ymax;
		}
	}
		
	/*public void	rotateSnake()		// re-scale the Snake Head so it's about 1.5 cm on screen
	{
		if (bmpSnake == null)	return;
		
		// Use the same Matrix over and over again to minimize allocation in onDraw.
		Matrix matrix = snakeHeadAngleMatrix;
		matrix.reset();
		
		float vw = ui.gameView.mHorizontalBound;
		float vh = ui.gameView.mVerticalBound;
		float hvw = vw / 2;
		float hvh = vh / 2;
		float bw = (float) bmpSnake.getWidth();
		float bh = (float) bmpSnake.getHeight();
		
		// First scale the bitmap to fit into the view. Use either scale factor for width and height, whichever is the smallest.
		float s1x = vw / bw;
		float s1y = vh / bh;
		float s1 = ( s1x < s1y ) ? s1x : s1y;
		
		RotationAngle =	(int) (Math.atan2(mPosY-mLastPosY, mPosX-mLastPosX) / (Math.PI/180));
		matrix.postTranslate( -hvw, -hvh);		// Translate the image up and left half the height and width so rotation (below) is around the center.
		matrix.postRotate((int) RotationAngle);	// Rotate the bitmap the specified number of degrees.
		snakeHeadAngleMatrix	=	matrix;
		
		bmpSnake	=	Bitmap.createBitmap(bmpSnake, 0, 0, (int) bw, (int) bh, matrix, false);
	}*/
	
	public void run(){}
}