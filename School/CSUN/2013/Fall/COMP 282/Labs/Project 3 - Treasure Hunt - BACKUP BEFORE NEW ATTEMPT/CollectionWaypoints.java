import java.awt.Point;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

public class CollectionWaypoints
{
	HashMap<String, Waypoint>	table;
	Graph<Waypoint>				graph;
	Database					db;
				
	public CollectionWaypoints()
	{
		table	=	new HashMap<String, Waypoint>();
		graph	=	new Graph<Waypoint>();
		try
		{
			db		=	new Database(	"com.mysql.jdbc.Driver",
										"jdbc:mysql://vrlab.ecs.csun.edu/jones69db", 
										"jones69", 
										"brian931");
			Database.BuildTablesFromFiles();
		}	catch (Exception e)	{}
	}
	
	public void Add(Waypoint waypoint)
	{
		table.put(waypoint.getHash(), waypoint);
		graph.AddNode(waypoint);
	}
	
	public void Remove(Waypoint waypoint)
	{
		table.remove(table.get(waypoint.getHash()));
		graph.remove(graph.indexOf(waypoint));
	}
	
	public void SetStartAndFinishWaypoints(Waypoint start, Waypoint end)
	{
		Iterator<Waypoint> tableIT = table.values().iterator();
		Iterator<Waypoint> graphIT = graph.iterator();
		while (tableIT.hasNext())
		{
			Waypoint tableTemp = tableIT.next();
			Waypoint graphTemp = graphIT.next();
			tableTemp.endingWaypoint = end;			
			graphTemp.endingWaypoint = end;
		}
	}
	
	public void rebuildGraphFromTable()
	{
		Iterator<Waypoint> it = table.values().iterator();
		while (it.hasNext())
			graph.add(it.next());
	}
	
	public boolean dbQueryIsMap()
	{
		return false;
	}
	public boolean dbQueryIsTreasure(Waypoint waypoint)
	{
		return false;
	}
	public boolean dbQueryIsCity(Waypoint waypoint)
	{
		return false;
	}
	
	public Waypoint dbQueryGetCurrentWaypoint(Player player)
	{
		return (Waypoint)table.get(Integer.toString(player.getPoint().x)+Integer.toString(player.getPoint().y)).clone();
	}
}

/**Custom class to create a Generic Node */
class Node<T> extends ArrayList<T>
{
	private static final long serialVersionUID = 1L;
	
	public Node()	{	}
}

/**Custom class to create a Graph of Nodes;
 * Graph<Node> will contain the CURRENT state of the Nodes */
class Graph<T> extends ArrayList<T>
{
	private static final long	serialVersionUID = 1L;
	int							countWaypoints		=	0;
	
	public Graph()
	{

	}
	
	public void AddNode(T nodeToAdd)
	{
		this.add(nodeToAdd);
		countWaypoints++;
	}
	
	public boolean contains(Object nodeToFind)
	{
		Iterator<T> it = this.iterator();
		while (it.hasNext())
		{
			if (it.next().equals(nodeToFind))
				return true;
		}
		
		return false;
	}
}

class Point3D
{
	int x = 0,
		y = 0,
		Height = 0;
	
	public Point3D()
	{
		setPos(0,0,0);
	}
	
	public Point3D(int x, int y, int Height)
	{
		setPos(x,y,Height);
	}
	
	public void setPos(int x, int y, int Height)
	{
		this.x = x;
		this.y = y;
		this.Height = Height;
	}
}

/**Custom Class to create a Waypoint object*/
class Waypoint extends Node<Waypoint> implements Comparable<Waypoint>
{
	private static final long serialVersionUID = 1L;
	
	Point3D		Location			=	new Point3D();
	Point		Neighbor[]			=	new Point[8];
	int			Height				=	0,
				Cost				=	0,
				Gold				=	0,
				mapX				=	0,
				mapY				=	0,
				countNeighbors 		=	8;
	Waypoint	previousWaypoint	=	null;
	Waypoint	endingWaypoint		=	null;
	int			costRemaining		=	0;			//	
	int			HEURISTIC			=	0;			//	Cost from Start-Node to Current-Node
	int			distSoFar			=	0;
	
	/**Constructor to initialize all variables in a Default Empty Waypoint*/
	public Waypoint()
	{
		
	}
	
	/**Constructor;
	 * Initializes all variables*/
	public Waypoint(String strList)
	{
		super();
		setVars(strList);
	}
	
	/**Constructor;
	 * Initializes variables to point to certain location;
	 * Used to create a BASIC Waypoint so we can find a hash-key for COMPLETE Waypoints in the HashMap*/
	public Waypoint(Point location)
	{
		super();
		String newString = " " + Integer.toString(location.x) + " " + location.y + " 0 0 0 0 0 0";
		setVars(newString);
	}
	
	/**Initializes all variables by Parsing them from strList*/
	public void setVars(String strList)
	{
		String[]	strVarList	=	new	String[8];
		
		strVarList	=	strList.split(" +");
		Location.x	=	Integer.parseInt(strVarList[1]);
		Location.y	=	Integer.parseInt(strVarList[2]);
		Height		=	Integer.parseInt(strVarList[3]);
		Cost		=	Integer.parseInt(strVarList[4]);
		Gold		=	Integer.parseInt(strVarList[5]);
		mapX		=	Integer.parseInt(strVarList[6]);
		mapY		=	Integer.parseInt(strVarList[7]);
		
		countNeighbors	=	Integer.parseInt(strVarList[8]);
				
		for (int i = 0, x = 9, y = 10; i < countNeighbors; i++, x= 9 + (i*2), y = 10 + (i*2))
		{
			Point neighbor = new Point(	Integer.parseInt(strVarList[x]), 
										Integer.parseInt(strVarList[y]));
			
			Neighbor[i] = neighbor;
		}
	}
		
	public int compareTo(Waypoint waypoint2)
	{
		Waypoint waypoint1 = this;
		
		int distRemaining2	=	waypoint2.distance(endingWaypoint.Location);
		int distRemaining1	=	waypoint1.distance(endingWaypoint.Location);
		int sumcost2		=	waypoint2.HEURISTIC + distRemaining2;
		int sumcost1		=	waypoint2.HEURISTIC + distRemaining1;
		
		return Integer.compare(	sumcost2, sumcost1);
	}
	
	public int distance(Point3D locNext)
	{
		int	distance	=	(int)(Math.sqrt(Math.pow(this.Location.x	-	locNext.x,			2)
										+	Math.pow(this.Location.y	-	locNext.y,			2)
										+	Math.pow(this.Height		-	locNext.Height,		2)));
		return distance;
	}
	
	public String getHash()
	{
		if (this != null && this.Location != null)
			return 	Integer.toString(this.Location.x) +	Integer.toString(this.Location.y);
		else	
			return null;
	}
	
	public boolean equals(Waypoint waypointToCompareTo)
	{
		if ((this.Location.x == waypointToCompareTo.Location.x) && 
			(this.Location.y == waypointToCompareTo.Location.y))
			return true;
		else
			return false;
	}
}