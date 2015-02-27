/**Name:	Brian Jones
 * Date:	12/18/2013
 * Asst:	Project 3 - Treasure Hunt
 * Class:	Comp 282
 */
import java.awt.Color;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.PointerInfo;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Stack;

import javax.swing.ImageIcon;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;

import SimulationFramework.Connector;
import SimulationFramework.Marker;
import SimulationFramework.SimFrame;

public class JonesTreasureHunt extends SimFrame
{
	private static final long					serialVersionUID	=	42L;
	final	static	String						waypointFile		=	"waypointNeighbor.txt";
	final	static	String						terrainFile			=	"terrain282.png";
			static	Scanner						readerWayPoint		=	null;
			static	CollectionWaypoints			data				=	new	CollectionWaypoints();
					Player[]					player				=	new	Player[4];
					enum						finishedCodes		{	finished, noPath, tmapFinished, tmapNoPath};
					
					PriorityQueue<Waypoint>		OPEN				=	new PriorityQueue<Waypoint>();
					HashMap<String, Waypoint>	CLOSED				=	new HashMap<String, Waypoint>();
					Stack<Waypoint>				shortestPath		=	new	Stack<Waypoint>();
					int							movesTotal			=	0;
							
					
	public JonesTreasureHunt(String frameTitle, String imageFile)			//	Create the Mainframe
	{
		super(frameTitle, imageFile);
		JMenuBar menuBar = new JMenuBar();

		aboutMenu = new JMenu("About");
		aboutMenu.setMnemonic('A');
		aboutMenu.setToolTipText("Display information about this program");

		usageItem = new JMenuItem("usage");
		authorItem = new JMenuItem("author");
		usageItem.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				JOptionPane.showMessageDialog(JonesTreasureHunt.this, "An informational message string \n"
						+ "about how to use the program \n" + "that can span several lines \n" + "if needed.", "Usage",   // dialog
		
				JOptionPane.PLAIN_MESSAGE);
			}
		});

		authorItem.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				JOptionPane.showMessageDialog(JonesTreasureHunt.this, "Brian Jones \n" + "brian.jones.476@my.csun.edu \n"
						+ "Comp 282", "author", JOptionPane.INFORMATION_MESSAGE, new ImageIcon("author.png"));
			}
		});

		aboutMenu.add(usageItem);
		aboutMenu.add(authorItem);
		menuBar.add(aboutMenu);
		setJMenuBar(menuBar);
		validate();
	}
					
	public static void main(String args[])
	{
		JonesTreasureHunt app = new JonesTreasureHunt("SimplePath", terrainFile);	//	Create the app
		app.start();	//	Start the app*/
	}
		
	public static void PopulateWaypointContainers(String waypointFile)	//	Fill Collection with Waypoints
	{
		data.table.clear();
		data.graph.clear();
		try
		{
			readerWayPoint = new Scanner(new File(waypointFile));
			while (readerWayPoint.hasNext())
				data.Add(new Waypoint(readerWayPoint.nextLine()));		//	Add Waypoint to Collection	
			readerWayPoint.close();
		} catch (FileNotFoundException e)		//	If !fileFound...
		{
			e.printStackTrace();				//	Print out the Stack Trace and...
			System.exit(1);						//	...Exit
		}
	}
	
	public void InitializeVariables()	//	Initialize these variables to ensure consistent program runs.
	{
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:	player[i]	=	new	Player(this, "1", 20, 20, 500, 440, 1000, 2000, Color.red);		break;
			case 1:	player[i]	=	new	Player(this, "2", 500, 20, 20, 500, 1000, 2000, Color.pink);	break;
			case 2:	player[i]	=	new	Player(this, "3", 20, 500, 500, 20, 1000, 2000, Color.orange);	break;
			case 3:	player[i]	=	new	Player(this, "4", 500, 440, 20, 20, 1000, 2000, Color.blue);	break;
			}
			player[i].OPEN.clear();
			player[i].CLOSED.clear();
			
			player[i].startingWaypoint					=	data.dbQueryGetCurrentWaypoint(player[i]);
			player[i].currentWaypoint					=	player[i].startingWaypoint;
			player[i].endingWaypoint					=	data.table.get(player[i].playerGoalLoc);
			player[i].currentWaypoint.previousWaypoint	=	null;
			player[i].currentWaypoint.endingWaypoint	=	player[i].endingWaypoint;
		}
	}
	
	public void setSimModel()		//	Initialize the Simulation Model variables, and then create the Player bot
	{
		PopulateWaypointContainers(waypointFile);
		InitializeVariables();
		DrawWaypoints();		
		
		setStatus("Time to start Processing!!!");
		
		animatePanel.addBot(player[0]);
		animatePanel.addBot(player[1]);
		animatePanel.addBot(player[2]);
		animatePanel.addBot(player[3]);
	}
	
	public void DrawWaypoints()	//	Draw Waypoints to screen in grid pattern, and draw edges denoting potential neighboring-paths
	{
		Iterator<Waypoint> it = data.table.values().iterator();
		while (it.hasNext())
		{
			Waypoint	waypoint		=	it.next();
			
			int			x				=	waypoint.Location.x,
						y				=	waypoint.Location.y;
			
			Marker		markerCity		=	new Marker(x,	y,	Color.cyan,		5),
						markerGold		=	new	Marker(x,	y,	Color.yellow,	5),
						markerMap		=	new	Marker(x,	y,	Color.magenta,	5),
						markerDefault	=	new	Marker(x,	y,	Color.black,	2);
			
			if (isCityWaypoint(waypoint))			animatePanel.addPermanentDrawable(markerCity);
			else if (isTreasureWaypoint(waypoint))	animatePanel.addPermanentDrawable(markerGold);
			else if (isMapWaypoint(waypoint))		animatePanel.addPermanentDrawable(markerMap);
			else									animatePanel.addPermanentDrawable(markerDefault);
								
			for (int neighborCounter = 0; neighborCounter < waypoint.countNeighbors; neighborCounter++)
			{
				int neighborX = waypoint.Neighbor[neighborCounter].x;
				int neighborY = waypoint.Neighbor[neighborCounter].y;
					
				//	Draw Edges for Waypoint
				animatePanel.addPermanentDrawable(new Connector(x, y, neighborX, neighborY, Color.black));
			}
		}
	}
	
	public synchronized void simulateAlgorithm()
	{
		animatePanel.setComponentState(false, true, true, false, false);
		OPEN.clear();
		CLOSED.clear();
		shortestPath.clear();
		
		OPEN.add(player[0].currentWaypoint);
		while (runnable())
		{
			if (!OPEN.isEmpty())
			{
				player[0].currentWaypoint = OPEN.poll();
				CLOSED.put(player[0].currentWaypoint.getHash(), player[0].currentWaypoint);
				if (EvaluateNeighbors())
				{
					FinishedAlgorithm(finishedCodes.finished);
					if (player[0].tmapRunning)
						return;
				}
				else
				{
					drawOpen(OPEN);
					drawClosed(CLOSED);
				}
			}
			else	{	FinishedAlgorithm(finishedCodes.noPath);	}
			checkStateToWait();				
		}
	}
	
	public boolean EvaluateNeighbors()		//	Determine which neighbor of currentWaypoint is optimal
	{
		for (int neighborIndex = 0; neighborIndex < player[0].currentWaypoint.countNeighbors; neighborIndex++)
		{
			String neighborKey = new Waypoint(player[0].currentWaypoint.Neighbor[neighborIndex]).getHash();
			Waypoint waypointNeighbor = (Waypoint)data.table.get(neighborKey).clone();
			waypointNeighbor.endingWaypoint = player[0].currentWaypoint.endingWaypoint;
			if (!CLOSED.containsKey(neighborKey))
			{
				//	For Each Waypoint Neighbor, Add the Heuristic to their Cost
				waypointNeighbor.HEURISTIC = player[0].currentWaypoint.HEURISTIC + player[0].currentWaypoint.distance(waypointNeighbor.Location);
				waypointNeighbor.previousWaypoint = (Waypoint)player[0].currentWaypoint.clone();
				if (waypointNeighbor.Location.equals(player[0].endingWaypoint.Location))
				{
					CLOSED.put(neighborKey, waypointNeighbor);
					player[0].currentWaypoint = waypointNeighbor;
					return true;
				}
				if (OPEN.peek() != waypointNeighbor)
					OPEN.add(waypointNeighbor);
			}
		}
		return false;
	}

	public void RemoveTreasureMap()
	{
		player[0].currentWaypoint.mapX = 0;
		player[0].currentWaypoint.mapY = 0;
		data.table.get(player[0].currentWaypoint.getHash()).mapX = 0;
		data.table.get(player[0].currentWaypoint.getHash()).mapY = 0;
		data.rebuildGraphFromTable();
	}
	
	public void drawOpen(PriorityQueue<Waypoint> listOpen)	//	Draw OPEN waypoints
	{
		Iterator<Waypoint> it = listOpen.iterator();
		while (it.hasNext())
		{
			Waypoint tempNode = it.next();
			animatePanel.addTemporaryDrawable(new Marker(tempNode.Location.x, tempNode.Location.y, Color.white,	3));
		}
	}
	
	public void drawClosed(HashMap<String, Waypoint> listClosed)			//	Draw CLOSED waypoints
	{
		Iterator<Waypoint> it = listClosed.values().iterator();
		while (it.hasNext())
		{
			Waypoint tempNode = it.next();
			animatePanel.addTemporaryDrawable(new Marker(tempNode.Location.x, tempNode.Location.y, Color.gray,	2));
		}
	}
	
	/**Checks if the Simulation is over by looking for any of the FinishedAlgorithm codes */
	private void FinishedAlgorithm(finishedCodes code)
	{
		switch (code)
		{
		case finished:	
		{
			BuildTheDots();
			WalkTheDots();
			
			if (!player[0].tmapRunning)
			{
				setStatus("Success, goal (" + player[0].currentWaypoint.Location.x + ", " + player[0].currentWaypoint.Location.y + ") " +
				"player[0] " + player[0].playerStrength + " $" + player[0].playerWealth);
				setSimRunning(false);
				animatePanel.setComponentState(true, false, false, true, true);
			}
			break;
		}
		case noPath:
		{
			setStatus("Failure, no path");
			setSimRunning(false);
			animatePanel.setComponentState(true, false, false, true, true);
			break;
		}
		default:
			break;
		}
	}
	
	public void BuildTheDots()
	{
		// Push each waypoint taken (from end to start) to form the
		// shortest-path onto a stack
		shortestPath.add(player[0].currentWaypoint);
		while (player[0].currentWaypoint.previousWaypoint != null)
		{
			player[0].currentWaypoint = player[0].currentWaypoint.previousWaypoint;
			shortestPath.add(player[0].currentWaypoint);
		}
	}
	
	public void WalkTheDots()
	{
		// Re-Integrate the waypoints to move the player-bot from start to
		// finish by popping the
		// Waypoints off of the stack and analyzing them
		while (!shortestPath.isEmpty())
		{
			player[0].currentWaypoint = shortestPath.pop();
			player[0].move();
			movesTotal++;

			if (isMapWaypoint(player[0].currentWaypoint) && !player[0].tmapRunning) // Currently on a Treasure-Map Waypoint
			{
				// Save current shortest-path variables (starting/current/ending
				// Waypoints and OPEN/CLOSED waypoint lists
				player[0].tmapRunning = true;
				Waypoint originalEndingWaypoint = player[0].endingWaypoint;
				
				animatePanel.clearTemporaryDrawables();
				player[0].endingWaypoint = data.table.get(new Waypoint(new Point(	player[0].currentWaypoint.mapX,
																					player[0].currentWaypoint.mapY))
																					.getHash());
				data.SetStartAndFinishWaypoints(player[0].currentWaypoint, player[0].endingWaypoint);
				
				RemoveTreasureMap();
				simulateAlgorithm(); // Now find the shortest path from currentWaypoint to the Treasure				
				
				animatePanel.clearTemporaryDrawables();
				player[0].currentWaypoint = player[0].endingWaypoint;
				player[0].endingWaypoint = originalEndingWaypoint;
				data.SetStartAndFinishWaypoints(player[0].currentWaypoint, player[0].endingWaypoint);
				simulateAlgorithm(); // Find path back to original ending point

				animatePanel.clearTemporaryDrawables();
				player[0].tmapRunning = false;
			}
			if (player[0].status != null)
				setStatus(player[0].status);
			checkStateToWait();
		}
	}
	
	public boolean isCityWaypoint(Waypoint waypoint)
	{
		if (waypoint.Cost != 0) 	return true;
		else					return false;
	}

	public boolean isTreasureWaypoint(Waypoint waypoint)
	{
		if (waypoint.Gold != 0)	return true;
		else				return false;
	}

	public boolean isMapWaypoint(Waypoint waypoint)
	{
		if (waypoint.mapX != 0 || waypoint.mapY != 0)
			return true;
		else										return false;
	}
}