import java.awt.Color;
import java.awt.Point;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Stack;

import SimulationFramework.Bot;
import SimulationFramework.Marker;

/**Custom Class to create a Player object that extends SimulationFramework.Bot*/
public class Player extends Bot
{
	JonesTreasureHunt			app					=	null;
	boolean						tmapRunning			=	false,
								isPlaying			=	true;	
	String						status				=	new String();
	
	Waypoint					startingWaypoint	=	new	Waypoint(),
								currentWaypoint		=	new Waypoint(),
								endingWaypoint		=	new Waypoint();
	Marker						marker;
	
	String						playerID			=	new	String(),
								playerStartLoc		=	new	String(),
								playerGoalLoc		=	new	String();
	int							playerWealth		=	1000,
								playerStrength		=	2000;
	Color						playerColor			=	Color.red;
	
	PriorityQueue<Waypoint>		OPEN				=	new PriorityQueue<Waypoint>();
	HashMap<String, Waypoint>	CLOSED				=	new HashMap<String, Waypoint>();
	Stack<Waypoint>				shortestPath		=	new	Stack<Waypoint>();
	int							movesTotal			=	0;
		
	public Player()
	{
		super("SimplePath", 20, 20, Color.red);
		this.playerColor = Color.red;
	}
	
	public Player(JonesTreasureHunt app, String name, Waypoint startingWaypoint, Color colorValue)
	{
		super(name, startingWaypoint.Location.x, startingWaypoint.Location.y, colorValue);
		this.app = app;
	}
	
	public Player(JonesTreasureHunt app, String playerID, int startX, int startY, int goalX, int goalY, int startWealth, int startStrength, Color color)
	{
		super("SimplePath", startX, startY, color);
		this.app			=	app;
		this.playerID		=	playerID;
		this.playerStartLoc	=	Integer.toString(startX) + Integer.toString(startY);
		this.playerGoalLoc	=	Integer.toString(goalX) + Integer.toString(goalY);
		this.playerWealth	=	startWealth;
		this.playerStrength	=	startStrength;
		this.playerColor	=	color;
		marker				=	new	Marker(startX, startY, color, 5);
	}

	public Player(JonesTreasureHunt app, String name, String playerID, Point start, Point goal, Color color)
	{
		super(name, start.x, start.y, color);
		this.app			= app;
		this.playerID		= playerID;
		this.playerStartLoc	= (Integer.toString(start.x) + Integer.toString(start.y));
		this.playerGoalLoc	= (Integer.toString(goal.x) + Integer.toString(goal.y));
		this.playerWealth	= 1000;
		this.playerStrength	= 2000;
		this.playerColor	= color;
		marker		= new Marker(start.x, start.y, color, 5);
	}
	
	@Override
	public void reset()
	{
		super.reset();		
	}
	
	public void move()
	{
		this.moveTo(new Point(currentWaypoint.Location.x, currentWaypoint.Location.y));
		int distToMove = 0;
		if (currentWaypoint.previousWaypoint != null)
		{
			currentWaypoint.distance(currentWaypoint.previousWaypoint.Location);
			currentWaypoint.distSoFar = currentWaypoint.previousWaypoint.distSoFar + distToMove;
		}
		playerStrength -= distToMove;
		
		if (app.isTreasureWaypoint(currentWaypoint))	
			playerWealth += currentWaypoint.Gold;
		if (app.isCityWaypoint(currentWaypoint))	//	City
		{
			//	...Pay Cost with Wealth and Increase Strength by the same amount, or...
			//	...if you can't pay the entire cost from wealth then you get no strength increase
			if (playerWealth >= currentWaypoint.Cost)
			{
				playerWealth -= currentWaypoint.Cost;
				playerStrength += currentWaypoint.Cost;
			}
			else	{	playerWealth -= currentWaypoint.Cost;		}
		}
	}
}