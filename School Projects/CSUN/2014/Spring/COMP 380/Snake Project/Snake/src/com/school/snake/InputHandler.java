package com.school.snake;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class InputHandler extends Thread implements SensorEventListener, Runnable
{	
	final int			unitLength	=	1;
	
	SensorManager		mgrSensors;
	SensorEventListener	listRotation;
	SensorEvent			eventCurrentPosition;
	Sensor				sensorRotation;
	FrameworkHandler	framework;
	
	double				x			=	0,
						y			=	0,
						z			=	0,
						cos			=	0,
						heading		=	0;
	
	public InputHandler(FrameworkHandler framework)
	{
		this.framework	=	framework;
		
		mgrSensors			=	(SensorManager) framework.activityUI.getBaseContext().getSystemService(Context.SENSOR_SERVICE);
		sensorRotation		=	mgrSensors.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
		mgrSensors.registerListener(this, sensorRotation, SensorManager.SENSOR_DELAY_GAME);
	}
	
	public void run()
	{
				
	}
	
	public void onSensorChanged(SensorEvent event)
	{
		 if (event.sensor.getType() != Sensor.TYPE_ROTATION_VECTOR)
		 {
			 event.sensor = null;
			 return;
		 }
		 else		/*	SENSOR CHANGING CODE HERE	*/
		 {
			 eventCurrentPosition = event;		 
		 }
	}

	public void onAccuracyChanged(Sensor sensor, int accuracy)
	{
		
	}
	
	public double getX()
	{
		x	=	(2.0 * Math.acos(eventCurrentPosition.values[0]) / Math.PI);
		return x;
	}
	
	public double getY()
	{
		y	=	(2.0 * Math.acos(eventCurrentPosition.values[1]) / Math.PI);
		return y;
	}
	
	public double getZ()
	{
		z	=	(2.0 * Math.acos(eventCurrentPosition.values[2]) / Math.PI);
		return z;
	}
	
	public void terminate()
	{
		mgrSensors.unregisterListener(this);
		interrupt();
	}
	
	public void pause()
	{
		
	}
}