import java.awt.Color;
import java.awt.Point;
import java.util.ArrayList;

import SimulationFramework.Bot;
import SimulationFramework.Marker;

/**Custom Class to create a Player object that extends SimulationFramework.Bot*/
public class Player extends Bot
{
	JonesTreasureHunt	app					=	null;
	boolean				tmapRunning			=	false,
						isPlaying			=	true;
	int					strength			=	2000,
						wealth				=	1000;
	String				ID					=	new	String(),
						goal				=	new String(),
						status				=	new String();
	Point				start				=	new	Point(),
						end					=	new	Point();
	Color				colorPlayer			=	null;
	Waypoint			currentWaypoint		=	new Waypoint(),
						endingWaypoint		=	new Waypoint();
	ArrayList<String>	path				=	new	ArrayList<String>();
	Marker				marker;
		
	public Player()
	{
		super("SimplePath", 20, 20, Color.red);
		this.colorPlayer = Color.red;
	}

	public Player(JonesTreasureHunt app, String name, String ID, Point start, Point end, Color colorValue)
	{
		super(name, start.x, start.y, colorValue);
		this.app	= app;
		this.ID		= ID;
		this.start	= start;
		this.end	= end;
		wealth		= 1000;
		strength	= 2000;
		this.color	= colorValue;
		marker		= new Marker(start.x, start.y, colorValue, 5);
	}
	
	public Player(JonesTreasureHunt app, String name, Waypoint startingWaypoint, Color colorValue)
	{
		super(name, startingWaypoint.Location.x, startingWaypoint.Location.y, colorValue);
		this.app = app;
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
		strength -= distToMove;
		
		if (app.isTreasureWaypoint(currentWaypoint))	
			wealth += currentWaypoint.Gold;
		if (app.isCityWaypoint(currentWaypoint))	//	City
		{
			//	...Pay Cost with Wealth and Increase Strength by the same amount, or...
			//	...if you can't pay the entire cost from wealth then you get no strength increase
			if (wealth >= currentWaypoint.Cost)
			{
				wealth -= currentWaypoint.Cost;
				strength += currentWaypoint.Cost;
			}
			else	{	wealth -= currentWaypoint.Cost;		}
		}
	}
}