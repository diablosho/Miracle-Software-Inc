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
			static	CollectionWaypoints			localdata			=	new	CollectionWaypoints();
					Player						player;
					Waypoint					startingWaypoint	=	null,
												endingWaypoint		=	null;
					PriorityQueue<Waypoint>		OPEN				=	new PriorityQueue<Waypoint>();
					HashMap<String, Waypoint>	CLOSED				=	new HashMap<String, Waypoint>();
					Stack<Waypoint>				shortestPath		=	new	Stack<Waypoint>();
					
					enum						finishedCodes		{	finished, noPath, tmapFinished, tmapNoPath};
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
		app.start();															//	Start the app*/
	}
		
	public void InitializeVariables()	//	Initialize these variables to ensure consistent program runs.
	{
		OPEN.clear();
		CLOSED.clear();
		localdata.graph.clear();
		localdata.table.clear();
		startingWaypoint = new Waypoint();
		endingWaypoint = new Waypoint();
	}
	
	public static void PopulateWaypointContainers(String waypointFile)	//	Fill Collection with Waypoints
	{
		try
		{
			readerWayPoint = new Scanner(new File(waypointFile));
			while (readerWayPoint.hasNext())
				localdata.Add(new Waypoint(readerWayPoint.nextLine()));		//	Add Waypoint to Collection	
			readerWayPoint.close();
		} catch (FileNotFoundException e)		//	If !fileFound...
		{
			e.printStackTrace();				//	Print out the Stack Trace and...
			System.exit(1);						//	...Exit
		}
	}
	
	public void setSimModel()		//	Initialize the Simulation Model variables, and then create the Player bot
	{
		InitializeVariables();
		PopulateWaypointContainers(waypointFile);
		
		setStatus("Initial state of simulation");
		DrawWaypoints();
		
		GetStartingWaypoint();
		GetEndingWaypoint();
			
		OPEN.add(startingWaypoint);
		localdata.SetStartAndFinishWaypoints(startingWaypoint, endingWaypoint);
			
		setStatus("Time to start Processing!!!");
		player = new Player(this, "SimplePath", startingWaypoint, Color.red);
		animatePanel.addBot(player);
		player.currentWaypoint = startingWaypoint;
		player.endingWaypoint = endingWaypoint;
	}
	
	public void DrawWaypoints()	//	Draw Waypoints to screen in grid pattern, and draw edges denoting potential neighboring-paths
	{
		Iterator<Waypoint> it = localdata.table.values().iterator();
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
	
	public void GetStartingWaypoint()	//	Retrieve starting Waypoint from user
	{
		PointerInfo info = null;
		Point point = null;

		setStatus("Enter starting position");
		do
		{
			point = null;
			info = null;
			waitForMousePosition();
			info = MouseInfo.getPointerInfo();
			point = info.getLocation();
			point.x = ((point.x / 20) * 20) - 20;
			point.y = ((point.y / 20) * 20) - 60;
			
			startingWaypoint = localdata.table.get((new Waypoint(point)).getHash());
			if (startingWaypoint == null) 
				setStatus("Starting Waypoint NOT Found!!!  Try again!!!");
		} while (startingWaypoint == null);
		animatePanel.addTemporaryDrawable(new Marker(startingWaypoint.Location.x, startingWaypoint.Location.y, Color.blue, 5));
	}
	
	public void GetEndingWaypoint()	//	Retrieve ending Waypoint from user
	{
		PointerInfo info = null;
		Point point = null;
		setStatus("Enter ending position");
		
		do
		{
			point = null;
			info = null;
			waitForMousePosition();
			info = MouseInfo.getPointerInfo();
			point = info.getLocation();
			point.x = ((point.x / 20) * 20) - 20;
			point.y = ((point.y / 20) * 20) - 60;
			
			endingWaypoint = localdata.table.get((new Waypoint(point)).getHash());
			if (endingWaypoint == startingWaypoint)
			{
				animatePanel.clearTemporaryDrawables();
				GetStartingWaypoint();
				GetEndingWaypoint();
			}
			if (endingWaypoint == null) 
				setStatus("Ending Waypoint NOT Found!!!  Try again!!!");
		} while (endingWaypoint == null);
		animatePanel.addTemporaryDrawable(new Marker(endingWaypoint.Location.x, endingWaypoint.Location.y, Color.blue, 5));
	}
	
	public synchronized void simulateAlgorithm()
	{
		animatePanel.setComponentState(false, true, true, false, false);
		OPEN.clear();
		player.currentWaypoint.previousWaypoint = null;
		OPEN.add(player.currentWaypoint);
		CLOSED.clear();
		shortestPath.clear();
		
		while (runnable())
		{
			if (!OPEN.isEmpty())
			{
				player.currentWaypoint = OPEN.poll();
				CLOSED.put(player.currentWaypoint.getHash(), player.currentWaypoint);		//	Mark Waypoint as completely evaluated
				if (EvaluateNeighbors())
				{
					FinishedAlgorithm(finishedCodes.finished);
					if (player.tmapRunning)
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
		for (int neighborIndex = 0; neighborIndex < player.currentWaypoint.countNeighbors; neighborIndex++)
		{
			String neighborKey = new Waypoint(player.currentWaypoint.Neighbor[neighborIndex]).getHash();
			Waypoint waypointNeighbor = localdata.table.get(neighborKey);
		
			if (!CLOSED.containsKey(neighborKey))
			{
				//	For Each Waypoint Neighbor, Add the Heuristic to their Cost
				waypointNeighbor.HEURISTIC = player.currentWaypoint.HEURISTIC + player.currentWaypoint.distance(waypointNeighbor.Location);
				waypointNeighbor.previousWaypoint = player.currentWaypoint;
				if (waypointNeighbor.Location.equals(player.endingWaypoint.Location))
				{
					CLOSED.put(neighborKey, waypointNeighbor);
					player.currentWaypoint = waypointNeighbor;
					return true;
				}
				if (OPEN.peek() != waypointNeighbor)
					OPEN.add(waypointNeighbor);
			}
		}
		return false;
	}
	
	public void BuildTheDots()
	{
		// Push each waypoint taken (from end to start) to form the
		// shortest-path onto a stack
		shortestPath.add(player.currentWaypoint);
		while (player.currentWaypoint.previousWaypoint != null)
		{
			player.currentWaypoint = player.currentWaypoint.previousWaypoint;
			shortestPath.add(player.currentWaypoint);
		}
	}
	
	public void WalkTheDots()
	{
		// Re-Integrate the waypoints to move the player-bot from start to
		// finish by popping the
		// Waypoints off of the stack and analyzing them
		while (!shortestPath.isEmpty())
		{
			player.currentWaypoint = shortestPath.pop();
			player.move();
			movesTotal++;

			if (isMapWaypoint(player.currentWaypoint) && !player.tmapRunning) // Currently on a Treasure-Map Waypoint
			{
				// Save current shortest-path variables (starting/current/ending
				// Waypoints and OPEN/CLOSED waypoint lists
				player.tmapRunning = true;
				Waypoint originalEndingWaypoint = endingWaypoint;
				
				animatePanel.clearTemporaryDrawables();
				player.endingWaypoint = localdata.table.get(new Waypoint(new Point(	player.currentWaypoint.mapX,
																					player.currentWaypoint.mapY))
																					.getHash());
				localdata.SetStartAndFinishWaypoints(player.currentWaypoint, player.endingWaypoint);
				
				RemoveTreasureMap();
				simulateAlgorithm(); // Now find the shortest path from currentWaypoint to the Treasure				
				
				animatePanel.clearTemporaryDrawables();
				player.currentWaypoint = player.endingWaypoint;
				player.endingWaypoint = originalEndingWaypoint;
				localdata.SetStartAndFinishWaypoints(player.currentWaypoint, player.endingWaypoint);
				simulateAlgorithm(); // Find path back to original ending point

				animatePanel.clearTemporaryDrawables();
				player.tmapRunning = false;
			}
			if (player.status != null)
				setStatus(player.status);
			checkStateToWait();
		}
	}
	
	public void RemoveTreasureMap()
	{
		player.currentWaypoint.mapX = 0;
		player.currentWaypoint.mapY = 0;
		localdata.table.get(player.currentWaypoint.getHash()).mapX = 0;
		localdata.table.get(player.currentWaypoint.getHash()).mapY = 0;
		localdata.rebuildGraphFromTable();
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
			
			if (!player.tmapRunning)
			{
				setStatus("Success, goal (" + player.currentWaypoint.Location.x + ", " + player.currentWaypoint.Location.y + ") " +
				"Player " + player.strength + " $" + player.wealth);
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