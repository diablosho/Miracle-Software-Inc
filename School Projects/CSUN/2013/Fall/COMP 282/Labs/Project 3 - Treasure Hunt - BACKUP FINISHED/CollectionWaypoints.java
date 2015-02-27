import java.awt.Point;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

public class CollectionWaypoints
{
	HashMap<String, Waypoint>	table;
	Graph<Waypoint>				graph;
	Database					db;
	String						driver	=	"com.mysql.jdbc.Driver",
								url		=	"jdbc:mysql://vrlab.ecs.csun.edu/jones69db",
								uname	=	"jones69",
								pword	=	"brian931";
				
	public CollectionWaypoints()
	{
		table	=	new HashMap<String, Waypoint>();
		graph	=	new Graph<Waypoint>();
		try
		{
			db		=	new Database(driver,	url,	uname,	pword);
			Database.BuildTablesFromFiles();
		}
		catch (Exception e)	{}
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
	
	public void rebuildGraphFromTable()
	{
		Iterator<Waypoint> it = table.values().iterator();
		while (it.hasNext())
			graph.add(it.next());
	}
	
	public void RemoveTreasureMap(Waypoint waypoint)
	{
		try
		{
			db.pst = db.conn.prepareStatement("UPDATE Map SET treasurePlace='00' WHERE place = ?");
			db.pst.setString(1, waypoint.getHash());
			db.pst.executeUpdate();
		}	
		catch (SQLException e)	{}
	}
	public void RemoveGold(String location)
	{
		try
		{
			db.pst	=	db.conn.prepareStatement("UPDATE Treasure SET gold=0 WHERE place=?; ");
			db.pst.setString(1, location);
			db.pst.executeUpdate();
		}
		catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
	public String dbqMap(Waypoint waypoint)
	{
		try
		{
			db.pst	=	db.conn.prepareStatement("SELECT treasurePlace FROM Map WHERE place = ? AND treasurePlace != '00'");
			db.pst.setString(1, waypoint.getHash());
			ResultSet rs = db.pst.executeQuery();
			if (rs.next())	
				return rs.getString("treasurePlace").trim();
			else			
				return "00";
		}
		catch	(SQLException e)
		{
			return null;
		}
	}
	public int dbqTreasure(Waypoint waypoint)
	{
		try
		{
			db.pst	=	db.conn.prepareStatement("SELECT gold FROM Treasure WHERE place = ? AND gold != 0");
			db.pst.setString(1, waypoint.getHash());
			ResultSet rs = db.pst.executeQuery();
			if (rs.next())	
				return rs.getInt("gold");
			else			
				return 0;
		}
		catch	(SQLException e)
		{
			return 0;
		}
	}
	public int dbqCity(Waypoint waypoint)
	{
		try
		{
			db.pst	=	db.conn.prepareStatement("SELECT cost FROM City WHERE place = ? AND cost != 0");
			db.pst.setString(1, waypoint.getHash());
			ResultSet rs = db.pst.executeQuery();
			if (rs.next())	
				return rs.getInt("cost");
			else			
				return 0;
		}
		catch	(SQLException e)
		{
			return 0;
		}
	}
	public Waypoint dbqCurrentWaypoint(int PID)
	{
		try
		{
			db.pst	=	db.conn.prepareStatement("SELECT place FROM Player WHERE id = ?");
			db.pst.setInt(1, PID);
			ResultSet rs = db.pst.executeQuery();
			if (rs.next())	
				return table.get(rs.getString("place").trim());
			else			
				return null;
		}
		catch	(SQLException e)
		{
			return null;
		}
	}
	
	/////	NEWEST METHODS...GET THESE TO WORK	/////
	public Point3D dbqResultOfContest(Waypoint contestedWaypoint)
	{
		int winnerID	=	-1,
			loserID		=	-1,
			winnings	=	-1;
	
		try
		{
			db.pst = db.conn.prepareStatement("SELECT id, wealth FROM Player WHERE place=? ORDER By wealth DESC;");
			db.pst.setString(1, contestedWaypoint.getHash());
			ResultSet rs = db.pst.executeQuery();
			if (rs.next())
			{
				winnerID	=	rs.getInt("id");
				while (rs.next())
				{
					loserID		=	rs.getInt("id");
					winnings	=	rs.getInt("wealth") / 3;
				}
				if (loserID != -1 && winnerID != -1 && winnings != -1)
						return (new Point3D(winnerID, loserID, winnings));
				else	return null;
			}
			else	return null;
		}	
		catch	(SQLException e)	{return null;}
	}
	
	public int dbqGetCost(Waypoint currentWaypoint)
	{
		try
		{
			db.pst	=	db.conn.prepareStatement("SELECT cost FROM City WHERE place = ?");
			db.pst.setString(1, currentWaypoint.getHash());
			ResultSet rs = db.pst.executeQuery();
			if (rs.next())	
				return rs.getInt("cost");
			else			
				return 0;
		}
		catch	(SQLException e)
		{
			return 0;
		}
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
	
	public Point3D(int x, int y)
	{
		setPos(x,y,0);
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
	int			Cost				=	0,
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
		
		strVarList		=	strList.split(" +");
		Location.x		=	Integer.parseInt(strVarList[1]);
		Location.y		=	Integer.parseInt(strVarList[2]);
		Location.Height	=	Integer.parseInt(strVarList[3]);
		Cost			=	Integer.parseInt(strVarList[4]);
		Gold			=	Integer.parseInt(strVarList[5]);
		mapX			=	Integer.parseInt(strVarList[6]);
		mapY			=	Integer.parseInt(strVarList[7]);
		
		countNeighbors	=	Integer.parseInt(strVarList[8]);
				
		for (int i = 0, x = 9, y = 10; i < countNeighbors; i++, x= 9 + (i*2), y = 10 + (i*2))
		{
			Point neighbor = new Point(	Integer.parseInt(strVarList[x]), 
										Integer.parseInt(strVarList[y]));
			
			Neighbor[i] = neighbor;
		}
	}			
	
	public int compareTo(Waypoint waypoint1)
	{
		Waypoint waypoint2 = this;
		
		int distRemaining1	=	waypoint1.distance(endingWaypoint.Location);
		int distRemaining2	=	waypoint2.distance(endingWaypoint.Location);
		int sumcost1		=	waypoint1.HEURISTIC + distRemaining1;
		int sumcost2		=	waypoint1.HEURISTIC + distRemaining2;
		
		return Integer.compare(	sumcost2, sumcost1);
	}
	
	public int distance(Point3D locNext)
	{
		int	distance	=	(int)(Math.sqrt(Math.pow(this.Location.x		-	locNext.x,			2)
										+	Math.pow(this.Location.y		-	locNext.y,			2)
										+	Math.pow(this.Location.Height	-	locNext.Height,		2)));
		return distance;
	}
	
	public String getHash()
	{
		if (this != null && this.Location != null)
			return 	Integer.toString(this.Location.x) +	Integer.toString(this.Location.y);
		else	return null;
	}
	
	public boolean equals(Waypoint waypointToCompareTo)
	{
		if (this.getHash().equals(waypointToCompareTo.getHash()))
			return true;
		return false;
	}
	
	public boolean isCityWaypoint()
	{
		if (this.Cost != 0) 	return true;
		else					return false;
	}

	public boolean isTreasureWaypoint()
	{
		if (this.Gold != 0)	return true;
		else				return false;
	}

	public boolean isMapWaypoint()
	{
		if (this.mapX != 0 || this.mapY != 0)	return true;
		else									return false;
	}
}