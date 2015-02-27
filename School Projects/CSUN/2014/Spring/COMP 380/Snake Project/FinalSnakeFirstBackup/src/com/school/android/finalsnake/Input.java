package com.school.android.finalsnake;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.view.Surface;

public class Input	implements	SensorEventListener
{	
	static	MainActivity	ui;
			float			mSensorX;
			float			mSensorY;
			float			mSensorZ;
			long			mAccelTimeStamp;
			long			mAccelCpuTimeStamp;
	
	public Input(MainActivity ui)
	{
		Input.ui = ui;
	}

	@Override public void onSensorChanged(	SensorEvent event)
	{
		/* Record input events, the event's timestamps, as well as the current time. The latter is needed so we can calculate the "present" time during rendering. 
		 * In this application, we need to take into account how the screen is rotated with respect to the sensors (which always return data in a coordinate space 
		 * aligned to with the screen in its native orientation). */
		
		switch (event.sensor.getType())
		{
		case Sensor.TYPE_ACCELEROMETER:					//	Record Accelerometer data
		{
			mSensorX	=	event.values[0];
			mSensorY	=	event.values[1];
			float mSensorZ	=	event.values[2];
					
			switch (Input.ui.mDisplay.getRotation())
			{
	            case Surface.ROTATION_0:
	            {
	                mSensorX = event.values[0];
	                mSensorY = event.values[1];
	                break;
	            }
	            case Surface.ROTATION_90:
	            {
	                mSensorX = -event.values[1];
	                mSensorY = event.values[0];
	                break;
	            }
	            case Surface.ROTATION_180:
	            {
	                mSensorX = -event.values[0];
	                mSensorY = -event.values[1];
	                break;
	            }
	            case Surface.ROTATION_270:
	            {
	            	mSensorX = event.values[1];
	                mSensorY = -event.values[0];
	                break;
	            }
	            default:	break;
			}
       		
			float x 	=	ui.gameView.originX + (ui.gameView.nest.snake.curXPos * ui.gameView.screenBoundsPixelX);
			float y 	=	ui.gameView.originY - (ui.gameView.nest.snake.curYPos * ui.gameView.screenBoundsPixelY);
			
			mAccelTimeStamp 	=	event.timestamp;	//	Record Accelerometer event time-stamp
			mAccelCpuTimeStamp 	=	System.nanoTime();	//	Record CPU time-stamp when Accelerometer event occurred
			
			/* compute the new position of our object, based on accelerometer data and present time. */
			//ui.gameView.nest.update(x, y, (ui.input.mAccelTimeStamp + System.nanoTime() - ui.input.mAccelCpuTimeStamp));
			
			break;
		}
		default:	return;
		}
	}

	@Override public void onAccuracyChanged(Sensor sensor, int accuracy){}	
}
