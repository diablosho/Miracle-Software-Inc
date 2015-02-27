package com.school.android.finalsnake;

import android.graphics.Bitmap;

import com.school.android.finalsnake.Snake;

public class SnakesNest	
{	
	static	MainActivity	ui;
			long			mLastT;
			float			mLastDeltaT;
			Snake			snake;
			
	public SnakesNest(MainActivity ui)
	{
		SnakesNest.ui	=	ui;
		snake			=	new Snake(ui);
	}
		
	/* Updates the position of the Snake and then resolves any collisions. */
	public void update(	float newX, float newY, long newTime)
	{
		updatePositions(newX, newY, newTime);	// update the system's positions
		snake.resolveCollisionWithBounds();
	}
	
	private void updatePositions(	float newX, float newY, long timestamp)	
	{
		long t = timestamp;
		if (mLastT != 0)
		{
			float dT = (float) ( t - mLastT ) * ( 1.0f / 1000000000.0f );
			if (mLastDeltaT != 0)
			{
				float dTC = dT / mLastDeltaT;
				snake.computePhysics(newX, newY, dT, dTC);
			}
			mLastDeltaT = dT;
		}
		mLastT = t;
	}
}