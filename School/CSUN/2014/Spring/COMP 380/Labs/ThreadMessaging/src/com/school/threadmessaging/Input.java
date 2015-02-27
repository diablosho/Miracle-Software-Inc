package com.school.threadmessaging;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.Parcelable;

public class Input extends Thread implements SensorEventListener, Runnable
{	
	final int			unitLength	=	1;
	
	Handler				handlerUI,
						handlerGame,
						handlerView,
						handlerInput	=	new	Handler()
						{
							public void handleMessage(Message msg)
							{
					            Bundle	msgData	=	msg.getData();
					            Note	note	=	(Note) msg.getData().get("Input");
					            
					            switch (note.message)
					            {
					            case "Get Input":	reportResults(note.from);	break;	
					            default:										break;
					            }					            
					            super.handleMessage(msg);
					        }
						};
	
	SensorManager		mgrSensors;
	SensorEventListener	listRotation;
	SensorEvent			eventCurrentPosition;
	Sensor				sensorRotation;
	UI					ui;
	
	double				x			=	0,
						y			=	0,
						z			=	0,
						cos			=	0,
						heading		=	0;
	
	public Input(UI ui)
	{
		mgrSensors			=	(SensorManager) ui.getBaseContext().getSystemService(Context.SENSOR_SERVICE);
		sensorRotation		=	mgrSensors.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
		mgrSensors.registerListener(this, sensorRotation, SensorManager.SENSOR_DELAY_GAME);
	}
	
	public void run()
	{
		Looper.prepare();		
		Looper.loop();
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
	
	public Handler getHandler()
	{
		return handlerInput;
	}
	public void setHandlers(Handler ui, Handler handlerview, Handler handlergame, Handler handlerinput)
	{
		this.handlerUI		=	ui;
		this.handlerView	=	handlerview;
		this.handlerGame	=	handlergame;
	}

	public void onAccuracyChanged(Sensor sensor, int accuracy)	{	}
	
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
	
	public void reportResults(String returnAddress)
	{
		double data[]	=	{	getX(),	getY(),	getZ()	};
		sendNote(returnAddress, "Current Input", data);
	}
	
	public void sendNote(String destination, String message, double[] data)
	{
		Note	note	=	new	Note("Input", destination, message, data);
		Bundle	bundle	=	new	Bundle();
		Message msg		=	Message.obtain();
		
		bundle.putParcelable(destination, (Parcelable) note);
		msg.setData(bundle);
		
		switch (destination)
		{
		case "UI":		msg.setTarget(handlerUI);	break;
		case "Game":	msg.setTarget(handlerGame);	break;
		case "View":	msg.setTarget(handlerView);	break;
		default:									break;
		}
		msg.sendToTarget();
	}
	
	public void pause()	{	}
}