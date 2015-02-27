package com.school.android.accelerometerplay;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.view.Surface;

public class Input	implements	SensorEventListener
{	
	AccelerometerPlayActivity	ui;
	float						mSensorX;
	float						mSensorY;
	long						mSensorTimeStamp;
	long						mCpuTimeStamp;
	
	public Input(AccelerometerPlayActivity ui)
	{
		this.ui = ui;
	}

	@Override public void onSensorChanged(	SensorEvent event)
	{
		if (event.sensor.getType() != Sensor.TYPE_ACCELEROMETER) return;
		/* record the accelerometer data, the event's timestamp as well as the current time. The latter is
		 * needed so we can calculate the "present" time during rendering. In this application, we need to
		 * take into account how the screen is rotated with respect to the sensors (which always return data
		 * in a coordinate space aligned to with the screen in its native orientation). */
		
		switch (ui.mDisplay.getRotation())
		{
		case Surface.ROTATION_0:
			mSensorX = event.values[0];
			mSensorY = event.values[1];
			break;
		case Surface.ROTATION_90:
			mSensorX = -event.values[1];
			mSensorY = event.values[0];
			break;
		case Surface.ROTATION_180:
			mSensorX = -event.values[0];
			mSensorY = -event.values[1];
			break;
		case Surface.ROTATION_270:
			mSensorX = event.values[1];
			mSensorY = -event.values[0];
			break;
		}
		
		mSensorTimeStamp = event.timestamp;
		mCpuTimeStamp = System.nanoTime();
	}

	@Override public void onAccuracyChanged(Sensor sensor, int accuracy){}	
}
