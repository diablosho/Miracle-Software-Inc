import java.awt.Point;
import java.sql.Connection;
import java.sql.Driver;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

public class CollectionWaypoints
{
	Graph<Waypoint>				graph;
	HashMap<String, Waypoint>	table;
	Database					db;
	String						driver	=	"com.mysql.jdbc.Driver",
								url		=	"jdbc:mysql://vrlab.ecs.csun.edu/jones69db",
								uname	=	"jones69",
								pword	=	"brian931";	
				
	public CollectionWaypoints()
	{
		table	=	new HashMap<String, Waypoint>();
		graph	=	new Graph<Waypoint>();
		try					{	db	=	new Database(driver,	url,	uname,	pword);	}
		catch (Exception e)	{															}
	}
	public void AddWaypoint(Waypoint waypoint)
	{
		table.put(waypoint.getHash(), waypoint);
		graph.AddNode(waypoint);
	}
	public void RemoveWaypoint(Waypoint waypoint)
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
	public Waypoint dbqCurrentWaypoint(int PID)
	{
		try
		{
			Database.pst	=	Database.conn.prepareStatement("SELECT place FROM gamePlayer WHERE id = ?");
			Database.pst.setInt(1, PID);
			ResultSet rs = Database.pst.executeQuery();
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
	public int dbqGetCost(Waypoint waypoint)
	{
		try
		{
			Database.pst	=	Database.conn.prepareStatement("SELECT cost FROM gameCity WHERE place = ? AND cost != 0");
			Database.pst.setString(1, waypoint.getHash());
			ResultSet rs = Database.pst.executeQuery();
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
	public String dbqGetTreasureLocation(Waypoint waypoint)
	{
		try
		{
			Database.pst	=	Database.conn.prepareStatement("SELECT treasurePlace FROM gameMap WHERE place = ? AND treasurePlace != '00'");
			Database.pst.setString(1, waypoint.getHash());
			ResultSet rs = Database.pst.executeQuery();
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
	public Point3D dbqResultOfContest(Waypoint contestedWaypoint)
	{
		int winnerID	=	-1,
			loserID		=	-1,
			winnings	=	-1;
	
		try
		{
			Database.pst = Database.conn.prepareStatement("SELECT id, wealth FROM gamePlayer WHERE place=? ORDER By wealth DESC;");
			Database.pst.setString(1, contestedWaypoint.getHash());
			ResultSet rs = Database.pst.executeQuery();
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
	public int dbqGetGold(Waypoint waypoint)
	{
		try
		{
			Database.pst	=	Database.conn.prepareStatement("SELECT gold FROM gameTreasure WHERE place = ? AND gold != 0");
			Database.pst.setString(1, waypoint.getHash());
			ResultSet rs = Database.pst.executeQuery();
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
	public void dbRemoveGold(String location)
	{
		try
		{
			Database.pst	=	Database.conn.prepareStatement("UPDATE gameTreasure SET gold=0 WHERE place=?; ");
			Database.pst.setString(1, location);
			Database.pst.executeUpdate();
		}
		catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
	public void dbRemoveTreasureMap(Waypoint waypoint)
	{
		try
		{
			Database.pst = Database.conn.prepareStatement("UPDATE gameMap SET treasurePlace='00' WHERE place = ?");
			Database.pst.setString(1, waypoint.getHash());
			Database.pst.executeUpdate();
		}	
		catch (SQLException e)	{}
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
	
	public Graph()	{}
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

class Database
{
	static	Connection			conn;
	static	Driver				dbDriver;
	static	PreparedStatement	pst;
	static	ResultSet			res;
	static	Statement			stmt;
	
	public Database(String driver, String url, String uname, String pword) throws Exception
	{
		ConnectToCHAOSNet(driver, url, uname, pword);
		DropTables();
		BuildTablesFromFiles();
	}
	public static void ConnectToCHAOSNet(String driver, String url, String uname, String pword) throws Exception
	{
		dbDriver = (Driver) Class.forName(driver).newInstance();
		conn	=	DriverManager.getConnection(url,uname,pword);
		stmt	=	conn.createStatement();
		System.out.println("OK  " + dbDriver);
	}
	public static void DropTables() throws SQLException
	{
		String	tableString	=	new	String();
		
		for (int tableNum = 0; tableNum < 4; tableNum++)
		{
			tableString = "DROP TABLE IF EXISTS ";
			switch (tableNum)
			{
			case 0:	tableString += "gamePlayer";		break;
			case 1:	tableString += "gameTreasure";	break;
			case 2:	tableString += "gameCity";		break;
			case 3:	tableString += "gameMap";		break;
			/*case 4:	tableString += "initialPlayer";	break;
			case 5:	tableString += "initialTreasure";	break;
			case 6:	tableString += "initialCity";		break;
			case 7:	tableString += "initialMap";		break;*/
			}
			pst = conn.prepareStatement(tableString);
			pst.executeUpdate();
		}
	}
	public static void BuildTablesFromFiles() throws SQLException
	{
		pst.addBatch("CREATE TABLE IF NOT EXISTS initialPlayer "
					+"(id int(1) NOT NULL, place varchar(6) NOT NULL, wealth int NOT NULL, "
					+"PRIMARY KEY (id)); ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS initialTreasure "
					+"(place varchar(6) NOT NULL, gold int NOT NULL, "
					+"PRIMARY KEY (place)); ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS initialMap "
					+"(place varchar(6) NOT NULL, treasurePlace varchar(6) NOT NULL, "
					+"PRIMARY KEY (place)); ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS initialCity "
					+"(place varchar(6) NOT NULL, cost int NOT NULL, "
					+"PRIMARY KEY (place)); ");
		
		pst.addBatch("CREATE TABLE IF NOT EXISTS gamePlayer LIKE initialPlayer; ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS gameTreasure LIKE initialTreasure; ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS gameMap LIKE initialMap; ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS gameCity LIKE initialCity; ");
		
		pst.addBatch("LOAD DATA LOCAL INFILE 'player.txt' INTO TABLE gamePlayer");
		pst.addBatch("LOAD DATA LOCAL INFILE 'player.txt' INTO TABLE initialPlayer");
		pst.addBatch("LOAD DATA LOCAL INFILE 'treasure.txt' INTO TABLE gameTreasure");
		pst.addBatch("LOAD DATA LOCAL INFILE 'treasure.txt' INTO TABLE initialTreasure");
		pst.addBatch("LOAD DATA LOCAL INFILE 'map.txt' INTO TABLE gameMap");
		pst.addBatch("LOAD DATA LOCAL INFILE 'map.txt' INTO TABLE initialMap");
		pst.addBatch("LOAD DATA LOCAL INFILE 'city.txt' INTO TABLE gameCity");
		pst.addBatch("LOAD DATA LOCAL INFILE 'city.txt' INTO TABLE initialCity");
		
		pst.executeBatch();
	}
	public void Update(String Table, int PID, String place, int wealth)
	{
		try
		{
			pst	=	conn.prepareStatement("UPDATE gamePlayer SET place=?, wealth=? WHERE id = ?; ");
			pst.setString(1, place);
			pst.setInt(2, wealth);
			pst.setInt(3, PID);
			pst.executeUpdate();
		}
		catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
}

/**Custom Class to create a Waypoint object*/
class Waypoint extends Node<Waypoint> implements Comparable<Waypoint>
{
	private static final long serialVersionUID = 1L;
	
	int			Cost				=	0,
				Gold				=	0,
				mapX				=	0,
				mapY				=	0,
				countNeighbors 		=	8,
				costRemaining		=	0,	//	Cost from Start-Node to Current-Node	
				distSoFar			=	0,
				HEURISTIC			=	0;
	Waypoint	previousWaypoint	=	null,
				endingWaypoint		=	null;
	Point3D		Location			=	new Point3D();
	Point		Neighbor[]			=	new Point[8];
	
	/**Constructor to initialize all variables in a Default Empty Waypoint*/
	public Waypoint()	{}
	/**Constructor;
	 * Initializes variables to point to certain location;
	 * Used to create a BASIC Waypoint so we can find a hash-key for COMPLETE Waypoints in the HashMap*/
	public Waypoint(Point location)
	{
		super();
		String newString = " " + Integer.toString(location.x) + " " + location.y + " 0 0 0 0 0 0";
		setVars(newString);
	}
	/**Constructor;
	 * Initializes all variables*/
	public Waypoint(String strList)
	{
		super();
		setVars(strList);
	}
	@Override
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
	public boolean equals(Waypoint waypointToCompareTo)
	{
		if (this.getHash().equals(waypointToCompareTo.getHash()))
			return true;
		return false;
	}
	public String getHash()
	{
		if (this != null && this.Location != null)
			return 	Integer.toString(this.Location.x) +	Integer.toString(this.Location.y);
		else	return null;
	}
	public boolean isCityWaypoint()
	{
		if (this.Cost != 0) 	return true;
		else					return false;
	}
	public boolean isMapWaypoint()
	{
		if (this.mapX != 0 || this.mapY != 0)	return true;
		else									return false;
	}
	public boolean isTreasureWaypoint()
	{
		if (this.Gold != 0)	return true;
		else				return false;
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