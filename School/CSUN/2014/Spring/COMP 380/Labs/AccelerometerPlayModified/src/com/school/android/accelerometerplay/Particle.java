package com.school.android.accelerometerplay;

/* Each of our particle holds its previous and current position, its acceleration. for added realism each particle has its own friction coefficient. */
public class Particle
{	
	AccelerometerPlayActivity	ui;
	float						mPosX;
	float						mPosY;
	float						mAccelX;
	float						mAccelY;
	float						mLastPosX;
	float						mLastPosY;
	float						sFriction			= 0.1f;	// friction of the virtual table and air
	float						mOneMinusFriction;
		
	Particle(AccelerometerPlayActivity ui)
	{
		// make each particle a bit different by randomizing its coefficient of friction
		this.ui	=	ui;
		final float r = ( (float) Math.random() - 0.5f ) * 0.2f;
		mOneMinusFriction = 1.0f - sFriction + r;
	}
	
	public void computePhysics(	float sx, float sy, float dT, float dTC)
	{
		// Force of gravity applied to our virtual object
		final float m = 1000.0f; // mass of our virtual object
		final float gx = -sx * m;
		final float gy = -sy * m;
		
		/* �F = mA <=> A = �F / m We could simplify the code by completely eliminating "m" (the mass)
		 * from all the equations, but it would hide the concepts from this sample code. */
		final float invm = 1.0f / m;
		final float ax = gx * invm;
		final float ay = gy * invm;
		
		/* Time-corrected Verlet integration The position Verlet integrator is defined as x(t+�t) = x(t)
		 * + x(t) - x(t-�t) + a(t)�t�2 However, the above equation doesn't handle variable �t very well,
		 * a time-corrected version is needed: x(t+�t) = x(t) + (x(t) - x(t-�t)) * (�t/�t_prev) +
		 * a(t)�t�2 We also add a simple friction term (f) to the equation: x(t+�t) = x(t) + (1-f) *
		 * (x(t) - x(t-�t)) * (�t/�t_prev) + a(t)�t�2 */
		final float dTdT = dT * dT;
		final float x = mPosX + mOneMinusFriction * dTC * ( mPosX - mLastPosX ) + mAccelX * dTdT;
		final float y = mPosY + mOneMinusFriction * dTC * ( mPosY - mLastPosY ) + mAccelY * dTdT;
		mLastPosX = mPosX;
		mLastPosY = mPosY;
		mPosX = x;
		mPosY = y;
		mAccelX = ax;
		mAccelY = ay;
	}
	
	/* Resolving constraints and collisions with the Verlet integrator can be very simple, we simply
	 * need to move a colliding or constrained particle in such way that the constraint is satisfied. */
	public void resolveCollisionWithBounds()
	{
		final float xmax = ui.mSimulationView.mHorizontalBound;
		final float ymax = ui.mSimulationView.mVerticalBound;
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
}