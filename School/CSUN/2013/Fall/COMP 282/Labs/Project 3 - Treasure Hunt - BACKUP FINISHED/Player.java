import java.awt.Color;
import java.awt.Point;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Stack;

import SimulationFramework.Bot;
import SimulationFramework.Marker;

/**Custom Class to create a Player object that extends SimulationFramework.Bot*/
public class Player extends Bot
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////	PLAYER CLASS VARIABLES/FLAGS FOLLOW BELOW     /////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int							movesTotal[]		=	{0,0,0,0};
	Stack<Waypoint>				shortestPath		=	new	Stack<Waypoint>();
	PriorityQueue<Waypoint>		OPEN				=	new PriorityQueue<Waypoint>();
	HashMap<String, Waypoint>	CLOSED				=	new HashMap<String, Waypoint>();
	boolean						isPlaying			=	true,			
								isExploring			=	false,
								isSearching			=	true;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////	PROGRAM EXECUTION AND FLOW-CONTROL VARIABLES     //////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	JonesTreasureHunt					app					=	null;
	String								status				=	new String();
	Color								color				=	Color.red;
	Marker								startMarker,
										goalMarker;
	boolean								onTreasurePath		=	false;	
	enum								finishedCodes		{	foundShortestPath, noPath, tmapFinished, tmapNoPath};
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////	PLAYER INSTANTIATION VARIABLES FOLLOW BELOW     ///////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	int									PID					=	0,
										strength			=	2000,
										wealth				=	1000;
	Waypoint							startingWaypoint	=	new	Waypoint(),
										currentWaypoint		=	new Waypoint(),
										finalWaypoint		=	new	Waypoint(),
										goalWaypoint		=	new Waypoint();
	
	public Player(JonesTreasureHunt app, int PID, Point3D start, Point3D goal, Color color)
	{
		super("SimplePath", start.x, start.y, color);
		
		this.OPEN				=	new	PriorityQueue<Waypoint>();
		this.CLOSED				=	new	HashMap<String, Waypoint>();
		this.shortestPath		=	new	Stack<Waypoint>();
		isSearching				=	true;
		
		this.color				=	color;
		this.startMarker		=	new	Marker(start.x, start.y, color, 5);
		this.goalMarker			=	new	Marker(goal.x, goal.y, color, 5);
		this.PID				=	PID;
		this.wealth				=	1000;
		this.strength			=	2000;
		this.startingWaypoint	=	(Waypoint)app.data.table.get(	Integer.toString(start.x) +	
																	Integer.toString(start.y))
																	.clone();
		this.currentWaypoint	=	this.startingWaypoint;
		this.finalWaypoint		=	(Waypoint)app.data.table.get(	Integer.toString(goal.x) +
																	Integer.toString(goal.y))
																	.clone();
		this.goalWaypoint		=	this.finalWaypoint;
		
		this.OPEN.add(startingWaypoint);
		
	}
	@Override
	public void reset()
	{
		super.reset();		
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
		
	public boolean EvaluateNeighbors(int PID)		//	Determine which neighbor of currentWaypoint is optimal
	{
		for (int neighborIndex = 0; neighborIndex < currentWaypoint.countNeighbors; neighborIndex++)
		{
			String neighborKey = new Waypoint(currentWaypoint.Neighbor[neighborIndex]).getHash();
								
			if (!CLOSED.containsKey(neighborKey))
			{
				//	For Each Waypoint Neighbor, Add the Heuristic to their Cost
				Waypoint waypointNeighbor = (Waypoint)app.data.table.get(neighborKey).clone();
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
	
	/**Checks if the Simulation is over by looking for any of the FinishedAlgorithm codes */
	private void FinishedAlgorithm(finishedCodes code)
	{
		switch (code)
		{
		case foundShortestPath:	
		{
			BuildThePath();
			//setExploring();
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
	
	public void BuildThePath()
	{
		// Push each waypoint taken (from end to start) to form the shortest-path onto a stack
		shortestPath.add(currentWaypoint);
		while (currentWaypoint.previousWaypoint != null)
		{
			currentWaypoint = currentWaypoint.previousWaypoint;
			shortestPath.add(currentWaypoint);
		}
	}
	
	public void TakeAStep()
	{
		// Re-Integrate the waypoints to move the player-bot from start to
		// finish by popping the Waypoints off of the stack and analyzing them
		move();
		movesTotal[PID]++;
		
		String dbqTMapKey = app.data.dbqMap(currentWaypoint);
		if (!dbqTMapKey.equals("00") && !onTreasurePath) // Embark upon EPIC quest for Treasure!!!
		{
			OPEN.clear();
			CLOSED.clear();
			shortestPath.clear();
			
			goalWaypoint = (Waypoint)app.data.table.get(dbqTMapKey).clone();
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
		if (currentWaypoint.previousWaypoint != null)
		{
			currentWaypoint.distance(currentWaypoint.previousWaypoint.Location);
			currentWaypoint.distSoFar = currentWaypoint.previousWaypoint.distSoFar + distToMove;
		}
		strength -= distToMove;
			
		if (app.data.dbqTreasure(currentWaypoint) > 0)
		{
			wealth += app.data.dbqTreasure(currentWaypoint);
			System.out.println("Player "+PID+" found gold @ Location:  "+currentWaypoint.getHash()+";  Player wealth = "+wealth+", Gold = "+app.data.dbqTreasure(currentWaypoint));
			app.data.RemoveGold(currentWaypoint.getHash());
		}
		if (app.data.dbqCity(currentWaypoint) > 0)	//	City
		{
			//	...Pay Cost with Wealth and Increase Strength by the same amount, or...
			//	...if you can't pay the entire cost from wealth then you get no strength increase
			int dbCost = app.data.dbqGetCost(currentWaypoint);
			if (wealth >= dbCost)	//	Buy Strength...
			{
				wealth -= dbCost;
				strength += dbCost;
				System.out.println("Player "+PID+" arrived at City:  "+currentWaypoint.getHash()+";  Player wealth = "+wealth+" and strength = "+strength);
			}
			else
			{
				wealth -= dbCost;
			}
		}
		this.moveTo(new Point(currentWaypoint.Location.x, currentWaypoint.Location.y));
		//	Now update the Player table
		app.data.db.Update("Player", PID, currentWaypoint.getHash(), wealth);
	}
	
	public void setExploring()	{		isSearching = false;	isExploring = true;	}
	public void setSearching()	{		isSearching = true;		isExploring = false;	}
}