import java.awt.Color;
import java.awt.Point;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Stack;

import SimulationFramework.Bot;
import SimulationFramework.Marker;

/**Custom Class to create a Player object that extends SimulationFramework.Bot*/
public class Player extends Bot
{
	enum						finishedCodes		{	foundShortestPath, noPath, tmapFinished, tmapNoPath}
	boolean						isPlaying			=	true,			
								isExploring			=	false,
								isSearching			=	true,
								onTreasurePath		=	false;
	
	PriorityQueue<Waypoint>		OPEN				=	new PriorityQueue<Waypoint>();
	HashMap<String, Waypoint>	CLOSED				=	new HashMap<String, Waypoint>();
	Stack<Waypoint>				shortestPath		=	new	Stack<Waypoint>();
	
	Color						playerColor			=	Color.red;
	int							playerID			=	0,
								playerStrength		=	2000,
								playerWealth		=	1000,
								playerStepsTaken	=	0;
	Marker						playerStartMarker,
								playerGoalMarker;	
	Waypoint					startingWaypoint	=	new	Waypoint(),
								currentWaypoint		=	new Waypoint(),
								finalWaypoint		=	new	Waypoint(),
								goalWaypoint		=	new Waypoint();
	
	public Player(int PID, Point3D start, Point3D goal, Color color)
	{
		super("SimplePath", start.x, start.y, color);
		InitializeVariables(PID, start, goal, color);
	}
	public void InitializeVariables(int PID, Point3D start, Point3D goal, Color color)
	{
		this.OPEN				=	new	PriorityQueue<Waypoint>();
		this.CLOSED				=	new	HashMap<String, Waypoint>();
		this.shortestPath		=	new	Stack<Waypoint>();
		this.isSearching		=	true;
		
		this.color				=	color;
		this.playerStartMarker	=	new	Marker(start.x, start.y, color, 5);
		this.playerGoalMarker	=	new	Marker(goal.x, goal.y, color, 5);
		this.playerID			=	PID;
		this.playerWealth		=	1000;
		this.playerStrength		=	2000;
		this.startingWaypoint	=	(Waypoint)JonesTreasureHunt.data.table.get(	Integer.toString(start.x) +	
																	Integer.toString(start.y))
																	.clone();
		this.currentWaypoint	=	this.startingWaypoint;
		this.finalWaypoint		=	(Waypoint)JonesTreasureHunt.data.table.get(	Integer.toString(goal.x) +
																	Integer.toString(goal.y))
																	.clone();
		this.goalWaypoint		=	this.finalWaypoint;
		this.OPEN.add(this.startingWaypoint);
	}
	public void BuildThePath()
	{
		// Push each waypoint taken (from end to start) to form the shortest-path onto a stack
		Waypoint temp = (Waypoint)goalWaypoint.clone();
		temp.previousWaypoint = (Waypoint)currentWaypoint.clone();
		currentWaypoint = temp;
		shortestPath.add(currentWaypoint);
		while (currentWaypoint.previousWaypoint != null)
		{
			currentWaypoint = currentWaypoint.previousWaypoint;
			shortestPath.add(currentWaypoint);
		}
	}
	public boolean EvaluateNeighbors(int PID)		//	Determine which neighbor of currentWaypoint is optimal
	{
		for (int neighborIndex = 0; neighborIndex < currentWaypoint.countNeighbors; neighborIndex++)
		{
			String neighborKey = new Waypoint(currentWaypoint.Neighbor[neighborIndex]).getHash();
								
			if (!CLOSED.containsKey(neighborKey))
			{
				//	For Each Waypoint Neighbor, Add the Heuristic to their Cost
				Waypoint waypointNeighbor = (Waypoint)JonesTreasureHunt.data.table.get(neighborKey).clone();
				waypointNeighbor.HEURISTIC = currentWaypoint.HEURISTIC + currentWaypoint.distance(waypointNeighbor.Location);
				waypointNeighbor.previousWaypoint = currentWaypoint;
				
				if (OPEN.peek() != waypointNeighbor)
				{
					waypointNeighbor.endingWaypoint	=	goalWaypoint;
					OPEN.add(waypointNeighbor);
				}
			}
		}
		return false;
	}
	public synchronized void findShortestPath(int PID)
	{
		setSearching();
		
		while (!OPEN.isEmpty() && isSearching)
		{
			currentWaypoint = OPEN.poll();
			CLOSED.put(currentWaypoint.getHash(), currentWaypoint);	//	Mark Waypoint as completely evaluated
			if (currentWaypoint.equals(goalWaypoint))
			{
				//	We want to keep all the Waypoint.previousWaypoint chains
				goalWaypoint	=	currentWaypoint;
				FinishedAlgorithm(finishedCodes.foundShortestPath);
				setExploring();
				return;
			}
			
			EvaluateNeighbors(PID);
		}
		if (isSearching)	{	FinishedAlgorithm(finishedCodes.noPath);	}
	}
	/**Checks if the Simulation is over by looking for any of the FinishedAlgorithm codes */
	private void FinishedAlgorithm(finishedCodes code)
	{
		switch (code)
		{
		case foundShortestPath:	
		{
			BuildThePath();
			JonesTreasureHunt.data.db.Update("gamePlayer", playerID, currentWaypoint.getHash(), playerWealth);
			break;
		}
		case noPath:
		{
			isPlaying = false;
			break;
		}
		default:
			break;
		}
	}
	public void TakeAStep()
	{
		// Re-Integrate the waypoints to move the player-bot from start to
		// finish by popping the Waypoints off of the stack and analyzing them
		move();
				
		String dbqTMapKey = JonesTreasureHunt.data.dbqGetTreasureLocation(currentWaypoint);
		if (!dbqTMapKey.equals("00") && !onTreasurePath) // Embark upon EPIC quest for Treasure!!!
		{
			OPEN.clear();
			CLOSED.clear();
			shortestPath.clear();
			
			goalWaypoint = (Waypoint)JonesTreasureHunt.data.table.get(dbqTMapKey).clone();
			currentWaypoint.previousWaypoint	=	null;
			currentWaypoint.endingWaypoint		=	goalWaypoint;
			OPEN.add(currentWaypoint);
			setSearching();
			onTreasurePath = true;
		}
	}
	public void move()
	{
		int distToMove = 0;
		playerStepsTaken++;
		
		if (currentWaypoint.previousWaypoint != null)
		{
			currentWaypoint.distance(currentWaypoint.previousWaypoint.Location);
			currentWaypoint.distSoFar = currentWaypoint.previousWaypoint.distSoFar + distToMove;
		}
		playerStrength -= distToMove;
			
		if (JonesTreasureHunt.data.dbqGetGold(currentWaypoint) > 0)
		{
			playerWealth += JonesTreasureHunt.data.dbqGetGold(currentWaypoint);
			System.out.println("Player "+playerID+" found Gold at Location:  "+currentWaypoint.getHash()+";  Player wealth = $"+playerWealth+", Gold Found = $"+JonesTreasureHunt.data.dbqGetGold(currentWaypoint));
			JonesTreasureHunt.data.dbRemoveGold(currentWaypoint.getHash());
		}
		if (JonesTreasureHunt.data.dbqGetCost(currentWaypoint) > 0)	//	City
		{
			//	...Pay Cost with Wealth and Increase Strength by the same amount, or...
			//	...if you can't pay the entire cost from wealth then you get no strength increase
			int dbCost = JonesTreasureHunt.data.dbqGetCost(currentWaypoint);
			if (playerWealth >= dbCost)	//	Buy Strength...
			{
				playerWealth -= dbCost;
				playerStrength += dbCost;
				System.out.println("Player "+playerID+" arrived at City:  "+currentWaypoint.getHash()+";  Player Wealth = $"+playerWealth+" and Strength = "+playerStrength);
			}
			else
			{
				playerWealth -= dbCost;
			}
		}
		this.moveTo(new Point(currentWaypoint.Location.x, currentWaypoint.Location.y));
		//	Now update the Player table
		JonesTreasureHunt.data.db.Update("gamePlayer", playerID, currentWaypoint.getHash(), playerWealth);
	}
	@Override
	public void reset()
	{
		super.reset();
	}
	public void setExploring()
	{
		isSearching = false;
		isExploring = true;
	}
	public void setSearching()
	{
		isSearching = true;
		isExploring = false;
	}
}