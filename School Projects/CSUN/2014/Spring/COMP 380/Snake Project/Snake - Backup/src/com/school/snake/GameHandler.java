package com.school.snake;

public class GameHandler extends Thread
{	
	FrameworkHandler	framework;
	
	boolean				exitApp		=	false,
						gameOver	=	false,
						gameRunning	=	false;
	
	public GameHandler(FrameworkHandler framework)
	{
		this.framework	=	framework;
	}
	
	public void run()
	{
		while (!exitApp)
		{
			if (gameRunning)
			{
				/*framework.threadUI.runOnUiThread(new	Runnable()
														{
															public synchronized void run()
															{
																framework.threadUI.ctrlStrX.setText(String.valueOf(framework.handlerInput.getX()));
																framework.threadUI.ctrlStrX.invalidate();
																framework.threadUI.ctrlStrY.setText(String.valueOf(framework.handlerInput.getY()));
																framework.threadUI.ctrlStrY.invalidate();
																framework.threadUI.ctrlStrZ.setText(String.valueOf(framework.handlerInput.getZ()));
																framework.threadUI.ctrlStrZ.invalidate();
																framework.threadUI.ctrlStrCos.setText(String.valueOf(framework.handlerInput.getCos()));
																framework.threadUI.ctrlStrCos.invalidate();
																framework.threadUI.ctrlStrHeading.setText(String.valueOf(framework.handlerInput.getHeading()));
																framework.threadUI.ctrlStrHeading.invalidate();
															}
														});*/
				try
				{
					sleep(100);
				}
				catch (InterruptedException e)
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
			if (gameOver)
			{
				gameRunning	=	false;
				endGame();
			}
		}
	}
	
	public void terminate()
	{
		endGame();
		interrupt();
	}
	
	public void startGame()
	{
		gameRunning	=	true;
		gameOver	=	false;
		exitApp		=	false;
	}
	
	public void endGame()
	{
		exitApp		=	false;
		gameOver	=	false;
		gameRunning	=	false;
	}
}