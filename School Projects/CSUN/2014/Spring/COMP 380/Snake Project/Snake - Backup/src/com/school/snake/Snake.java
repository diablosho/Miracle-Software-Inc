package com.school.snake;


public class Snake
{	
	InputHandler	handlerGame;
	
	protected Snake(InputHandler handlerGame)
	{
		this.handlerGame	=	handlerGame;
	}
	
	protected void newSnake()
	{
		
	}
	
	protected void moveSnake(int[] pos)
	{
		
	}	
	
	protected void growSnake()
	{
		
	}
	
	public int[] getNextSnakePosition()
	{
		int[]	newPos	=	{1,1,1};
		
		return newPos;
	}
}