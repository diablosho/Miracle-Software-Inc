import java.util.Random;
public class Life
{
	public static final int ROWS = 10;
	public static final int COLS = 10;
	
	public static void main(String[] args)
	{
		boolean[][] world = new boolean[ROWS][COLS];
		int count;
		
		setWorld(world);
		printWorld(world);
		for(count = 0; count < 4; count++)
		{
			getNextGen(world);
			printWorld(world);
		}
	}
	public static void setWorld(boolean[][] world)
	{
		Random gen = new Random();
		int row, col, num;
		
		for(row = 0;row < ROWS; row++)
			for(col = 0; col < COLS; col++)
			{
				num = gen.nextInt(2);
				if(num == 0)
					world[row][col] = false;
				else
					world[row][col] = true;
			}
	}
	public static void printWorld(boolean[][] world)
	{
		int row, col;
		
		System.out.println("----------");
		for(row = 0; row < ROWS; row++)
		{
			for(col = 0; col < COLS; col++)
				if(world[row][col])
					System.out.print("X");
				else
					System.out.print(".");
			System.out.println();
		}
	}
	public static void getNextGen(boolean[][] world)
	{
		boolean[][] newWorld = new boolean[ROWS][COLS];
		int row, col, neighbors;
		
		for(row = 1; row < ROWS - 1; row++)
			for(col = 1; col < COLS -1; col++)
			{
				neighbors = countNeighbors(world, row, col);
				if(neighbors < 2 || neighbors > 3)
					newWorld[row][col] = false;
				else if (neighbors == 3)
					newWorld[row][col] = true;
				else
					newWorld[row][col] = world[row][col];
			}
		for(row = 0; row < ROWS; row++)
			for(col = 0; col < COLS; col++)
				world[row][col] = newWorld[row][col];
	}
	
	public static int countNeighbors(boolean[][] world, int curRow, int curCol)
	{
		int row, col, count = 0;
		
		for(row = curRow - 1; row <= curRow + 1; row++)
			for(col = curCol - 1; col <= curCol + 1; col++)
				if(world[row][col])
					count++;
		if(world[curRow][curCol])
			count--;
		return count;
			
	}
}