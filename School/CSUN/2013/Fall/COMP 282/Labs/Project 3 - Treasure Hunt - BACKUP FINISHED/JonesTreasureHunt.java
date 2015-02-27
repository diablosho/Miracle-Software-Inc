/**Name:	Brian Jones
 * Date:	12/9/2013
 * Asst:	Project 3 - Treasure Hunt - FINISHED
 * Class:	Comp 282
 */
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Random;
import java.util.Scanner;

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
					Player[]					player				=	new Player[4];
					int							PID					=	0;
			
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
		app.start();																//	Start the app*/
	}
	public void InitializePlayers()
	{
		player[0]	=	new	Player(this, 0, new Point3D(20,20), new Point3D(500, 440), Color.red);
		player[1]	=	new	Player(this, 1, new Point3D(500,20), new Point3D(20, 500), Color.pink);
		player[2]	=	new	Player(this, 2, new Point3D(20,500), new Point3D(500, 20), Color.orange);
		player[3]	=	new	Player(this, 3, new Point3D(500,440), new Point3D(20, 20), Color.blue);
	}
	public void InitializeVariables()	//	Initialize these variables to ensure consistent program runs.
	{
		animatePanel.setComponentState(false, true, true, false, false);
		data.graph.clear();
		data.table.clear();
	}
	public void PopulateWaypointContainers(String waypointFile)	//	Fill Collection with Waypoints
	{
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
	public void setSimModel()		//	Initialize the Simulation Model variables, and then create the Player bot
	{
		InitializeVariables();		
		PopulateWaypointContainers(waypointFile);
		InitializePlayers();
		DrawWaypoints();
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
			
			if (waypoint.isCityWaypoint())			animatePanel.addPermanentDrawable(markerCity);
			else if (waypoint.isTreasureWaypoint())	animatePanel.addPermanentDrawable(markerGold);
			else if (waypoint.isMapWaypoint())		animatePanel.addPermanentDrawable(markerMap);
			else									animatePanel.addPermanentDrawable(markerDefault);
								
			for (int neighborCounter = 0; neighborCounter < waypoint.countNeighbors; neighborCounter++)
			{
				int neighborX = waypoint.Neighbor[neighborCounter].x;
				int neighborY = waypoint.Neighbor[neighborCounter].y;
					
				//	Draw Edges for Waypoint
				animatePanel.addPermanentDrawable(new Connector(x, y, neighborX, neighborY, Color.black));
			}
		}
		for (PID = 0; PID < 4; PID++)
		{
			animatePanel.addTemporaryDrawable(player[PID].startMarker);
			animatePanel.addTemporaryDrawable(player[PID].goalMarker);
			animatePanel.addBot(player[PID]);
		}
	}
	
	public synchronized void simulateAlgorithm()	//	NEW TURN, SO CHECK GAME-STATE AND/OR SELECT PLAYER
	{
		//	GAME IN PATH-FINDING MODE UNTIL ALL PLAYERS HAVE FOUND PATH
		Random rand = new Random();
		
		while (runnable())
		{
			for (PID = 0; PID < 4; PID++)
				if (player[PID].isSearching)
					player[PID].findShortestPath(PID);
						
			PID = rand.nextInt(4);
			if (!player[PID].shortestPath.empty())
			{
				player[PID].currentWaypoint = player[PID].shortestPath.pop();
				
				player[PID].TakeAStep();
				
				if (data.dbqResultOfContest(player[PID].currentWaypoint) != null)
				{
					int winner 		=	data.dbqResultOfContest(player[PID].currentWaypoint).x;
					int loser		=	data.dbqResultOfContest(player[PID].currentWaypoint).y;
					int winnings	=	data.dbqResultOfContest(player[PID].currentWaypoint).Height;
					System.out.println("Contest!  Player "+winner+" with "+player[winner].wealth+" wins against player "+loser+" with "+player[loser].wealth+" wealth");
					
					player[winner].wealth += winnings;
					player[loser].wealth -= winnings;
					data.db.Update("Player", winner, player[winner].currentWaypoint.getHash(), player[winner].wealth);
					data.db.Update("Player", loser, player[loser].currentWaypoint.getHash(), player[loser].wealth);
				}
				
				if (!(data.dbqMap(player[PID].currentWaypoint).equals("00")))
				{
					System.out.println("Player "+PID+" found treasure Map @ Location: "+player[PID].currentWaypoint.getHash()+".  Finding path to Treasure at: "+data.dbqMap(player[PID].currentWaypoint)+" now...");
					data.RemoveTreasureMap(player[PID].currentWaypoint);
				}
			}
			else
			{
				if (player[PID].onTreasurePath)
				{
					player[PID].OPEN.clear();
					player[PID].CLOSED.clear();
					player[PID].shortestPath.clear();
					
					player[PID].currentWaypoint.previousWaypoint	=	null;
					player[PID].currentWaypoint.endingWaypoint		=	player[PID].finalWaypoint;
					player[PID].goalWaypoint	=	player[PID].finalWaypoint;
					player[PID].OPEN.add(player[PID].currentWaypoint);
					player[PID].onTreasurePath	=	false;
					
					System.out.println("Player "+PID+" found his Treasure...Moving on to new goal:  "+player[PID].goalWaypoint.getHash()+" wealth = "+player[PID].wealth);
					player[PID].setSearching();
				}
				else
				{
					if (player[PID].isPlaying)
					{
						player[PID].isPlaying		=	false;
						player[PID].wealth += player[PID].strength;
						System.out.println("Player "+PID+" is Done!  Goal:  "+player[PID].goalWaypoint.getHash()+" wealth = "+player[PID].wealth);
					}
				}
			}
			checkStateToWait();
		
			if (!player[0].isPlaying && !player[1].isPlaying && !player[2].isPlaying && !player[3].isPlaying)
			{
				if (!player[PID].onTreasurePath)
				{
					setStatus("Finished Searching");
					setSimRunning(false);
					animatePanel.setComponentState(true, false, false, true, true);
					break;
				}
				else				{
					setStatus("Found Treasure...continuing to Original Goal");
					player[PID].currentWaypoint.endingWaypoint	=	player[PID].finalWaypoint;
					data.RemoveGold(player[PID].currentWaypoint.getHash());
					player[PID].setSearching();
					break;
				}
			}
		}
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
	
	public void ClearTemporaryDrawables()	{	animatePanel.clearTemporaryDrawables();	}
	public void CheckStateToWait()			{	checkStateToWait();						}
	public void SetStatus(String status)	{	setStatus(status);						}
}