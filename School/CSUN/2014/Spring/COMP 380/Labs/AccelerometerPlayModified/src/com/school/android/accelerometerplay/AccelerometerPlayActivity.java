/* Copyright (C) 2010 The Android Open Source Project Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License. You may obtain a copy of the
 * License at http://www.apache.org/licenses/LICENSE-2.0 Unless required by applicable law or agreed to in
 * writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing
 * permissions and limitations under the License. */

package com.school.android.accelerometerplay;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.view.Display;
import android.view.WindowManager;

public class AccelerometerPlayActivity extends Activity
{	
	SimulationView	mSimulationView;
	SensorManager	mSensorManager;
	PowerManager	mPowerManager;
	WindowManager	mWindowManager;
	Display			mDisplay;
	WakeLock		mWakeLock;
	Sensor			mAccelerometer;
	Input			input;
	
	@SuppressWarnings("deprecation") @Override public void onCreate(	Bundle savedInstanceState)	/** Called when the activity is first created. */
	{
		super.onCreate(savedInstanceState);
		
		mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);	// Get an instance of the SensorManager
		mPowerManager = (PowerManager) getSystemService(POWER_SERVICE);		// Get an instance of the PowerManager
		mWindowManager = (WindowManager) getSystemService(WINDOW_SERVICE);	// Get an instance of the WindowManager
		mDisplay = mWindowManager.getDefaultDisplay();
		mWakeLock = mPowerManager.newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, getClass().getName());	// Create a bright wake lock
		mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		
		input	=	new	Input(this);
		mSimulationView = new SimulationView(this, this);					// instantiate our simulation view and set it as the activity's content
		
		setContentView(mSimulationView);
	}
	
	@Override protected void onResume()
	{
		// when the activity is resumed, we acquire a wake-lock so that the screen stays on, since the user will likely not be fiddling with the screen or buttons.
		super.onResume();
		mWakeLock.acquire();
		mSimulationView.startSimulation();
	}
	
	@Override protected void onPause()		/* When the activity is paused, we make sure to stop the simulation, release our sensor resources and wake locks */		
	{
		super.onPause();
		mSimulationView.stopSimulation();	// Stop the simulation
		mWakeLock.release();				// and release our wake-lock
	}
	
	public void startListeningForInput()
	{
		mSensorManager.registerListener(input, mAccelerometer, SensorManager.SENSOR_DELAY_UI);
	}
	
	public void stopListeningForInput()
	{
		mSensorManager.unregisterListener(input);
	}
	
	public float getSx()
	{
		return (float) input.mSensorX;
	}
	
	public float getSy()
	{
		return (float) input.mSensorY;
	}
	
	public long getNow()
	{
		return (long) (input.mSensorTimeStamp + ( System.nanoTime() - input.mCpuTimeStamp ));
	}
}
