package com.school.android.finalsnake;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;

/* Each of our particle holds its previous and current position, its acceleration. for added realism each particle has its own friction coefficient. */
public class Snake
{	
	static	MainActivity	ui;
	final	private	float 	mass 				= 	25.0f; 	// mass of our Snake head
	final	private	float	headLength			=	1.0f;
					float	curXPos				=	0.1f;
					float	curYPos				=	0.1f;
			private	float	prevPosX			=	0.0f;
			private	float	prevPosY			=	0.0f;
			private	float	mOneMinusFriction;
			private	float	RotationAngle;
					Bitmap	bmpSnake;
					int		snakeHeadWidth;
					int		snakeHeadHeight;
			private	Matrix	snakeHeadAngleMatrix	=	new Matrix();
		
	public Snake(MainActivity ui)
	{
		// make each Snake a little bit different by randomizing its coefficient of friction
		Snake.ui			=	ui;
		mOneMinusFriction 	= 	1.0f - 0.1f + ((float) Math.random() - 0.5f) * 0.2f;
	}
	
	public void setBitmap(Bitmap bmp)
	{
		bmpSnake		=	bmp;
		
		snakeHeadWidth	=	bmpSnake.getWidth();
		snakeHeadHeight	=	bmpSnake.getHeight();
	}
	
	public void setPosition(int x, int y)
	{
		prevPosX	=	curXPos;
		prevPosY	=	curYPos;
		curXPos		=	x;
		curYPos		=	y;
	}
	
	public void computePhysics(	float sensorX, float sensorY, float dT, float dTC)
	{
		float dTdT			=	dT*dT;				//	Change in time squared
		float gravityX 		= 	(-sensorX) * mass;	//	Force of gravity applied to our Snake head in X-axis
		float gravityY 		= 	(-sensorY) * mass;	//	Force of gravity applied to our Snake head in Y-axis
		float curAccelX 	= 	gravityX / mass;	//	Acceleration applied to our Snake's X-Axis
		float curAccelY 	= 	gravityY / mass;	//	Acceleration applied to our Snake's Y-Axis
				
		prevPosX 			=	curXPos;
		prevPosY			=	curYPos;
		curXPos 			=	curXPos + mOneMinusFriction * dTC * ( curXPos - prevPosX ) + curAccelX * dTdT;
		curYPos 			=	curYPos + mOneMinusFriction * dTC * ( curYPos - prevPosY ) + curAccelY * dTdT;
	}
	
	public void resolveCollisionWithBounds()
	{
		float 	xmax 	= 	ui.gameView.screenBoundsPixelX;
		float 	ymax 	= 	ui.gameView.screenBoundsPixelY;
		float 	x 		= 	curXPos;
		float 	y 		= 	curYPos;
				
		if (x > xmax)		{	curXPos = xmax;		}
		else if (x < -xmax)	{	curXPos = -xmax;	}
		if (y > ymax)		{	curYPos = ymax;		}
		else if (y < -ymax)	{	curYPos = -ymax;	}
	}
	
	public Matrix	prepareBitmap(Canvas canvas)		// re-scale the Snake Head so it's about 1.5 cm on screen
	{
		if (bmpSnake == null)	return null;
		
		// Use the same Matrix over and over again to minimize allocation in onDraw.
		Matrix matrix = snakeHeadAngleMatrix;
		matrix.reset();
		
		float vw = ui.gameView.screenBoundsPixelX;
		float vh = ui.gameView.screenBoundsPixelY;
		float hvw = vw / 2;
		float hvh = vh / 2;
		float bw = (float) bmpSnake.getWidth();
		float bh = (float) bmpSnake.getHeight();
		
		// First scale the bitmap to fit into the view. Use either scale factor for width and height, whichever is the smallest.
		float s1x = vw / bw;
		float s1y = vh / bh;
		float s1 = ( s1x < s1y ) ? s1x : s1y;
		
		RotationAngle =	(int) (Math.atan2(curXPos-prevPosX, curYPos-prevPosY) / (Math.PI/180));
		matrix.postTranslate( -hvw, -hvh);		// Translate the image up and left half the height and width so rotation (below) is around the center.
		matrix.postRotate((int) RotationAngle);	// Rotate the bitmap the specified number of degrees.
		
		snakeHeadAngleMatrix	=	matrix;
		
		return matrix;
	}
}