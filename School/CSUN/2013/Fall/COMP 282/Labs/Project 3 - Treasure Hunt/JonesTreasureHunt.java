/**Name:	Brian Jones
 * Date:	12/10/2013
 * Asst:	Project 3 - Treasure Hunt - COMPLETELY FINISHED
 * Class:	Comp 282
 */
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Random;
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
	private static	final	long						serialVersionUID	=	42L;
			static	final	String						terrainFile			=	"terrain282.png",
														waypointFile		=	"waypointNeighbor.txt";		
			static			Scanner						readerWayPoint		=	null;
			static			CollectionWaypoints			data				=	new	CollectionWaypoints();
							ArrayList<Player>			player				=	new ArrayList<Player>();	
							Waypoint					currentWaypoint,
														goalWaypoint,
														finalWaypoint;
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
			@Override
			public void actionPerformed(ActionEvent event)
			{
				JOptionPane.showMessageDialog(JonesTreasureHunt.this, "An informational message string \n"
						+ "about how to use the program \n" + "that can span several lines \n" + "if needed.", "Usage",   // dialog
		
				JOptionPane.PLAIN_MESSAGE);
			}
		});

		authorItem.addActionListener(new ActionListener()
		{
			@Override
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
	public void setSimModel()		//	Initialize the Simulation Model variables, and then create the Player bot
	{
		InitializeVariables();		
		PopulateWaypointContainers(waypointFile);
		InitializePlayers();
		DrawWaypoints();
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
				data.AddWaypoint(new Waypoint(readerWayPoint.nextLine()));		//	Add Waypoint to Collection	
			readerWayPoint.close();
		} catch (FileNotFoundException e)		//	If !fileFound...
		{
			e.printStackTrace();				//	Print out the Stack Trace and...
			System.exit(1);						//	...Exit
		}
	}
	public void InitializePlayers()		//	Initialize Players' starting positions from gamePlayer DB Table...
	{									//	... which was created from the player.txt file
		player.add(new	Player(0, data.dbqCurrentWaypoint(0).Location, new Point3D(500, 440), Color.red));
		player.add(new	Player(1, data.dbqCurrentWaypoint(1).Location, new Point3D(20, 500), Color.pink));
		player.add(new	Player(2, data.dbqCurrentWaypoint(2).Location, new Point3D(500, 20), Color.orange));
		player.add(new	Player(3, data.dbqCurrentWaypoint(3).Location, new Point3D(20, 20), Color.blue));
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
			animatePanel.addTemporaryDrawable(player.get(PID).playerStartMarker);
			animatePanel.addTemporaryDrawable(player.get(PID).playerGoalMarker);
			animatePanel.addBot(player.get(PID));
		}
	}
	public void FindShortestPaths()
	{
		for (PID = 0; PID < 4; PID++)
			if (player.get(PID).isSearching)
				player.get(PID).findShortestPath(PID);
	}
	public synchronized void simulateAlgorithm()	//	NEW TURN, SO CHECK GAME-STATE AND/OR SELECT PLAYER
	{
		//	GAME IN PATH-FINDING MODE UNTIL ALL PLAYERS HAVE FOUND PATH
		Random rand = new Random();
		
		while (runnable())
		{
			FindShortestPaths();
						
			PID 				=	rand.nextInt(4);
			Player	curPlayer	=	player.get(PID);
			
			HashMap<String, Waypoint>	CLOSED				=	curPlayer.CLOSED;
			PriorityQueue<Waypoint>		OPEN				=	curPlayer.OPEN;
			Stack<Waypoint>				shortestPath		=	curPlayer.shortestPath;
			Waypoint					currentWaypoint		=	curPlayer.currentWaypoint,
										goalWaypoint		=	curPlayer.goalWaypoint,
										finalWaypoint		=	curPlayer.finalWaypoint;
			String						keyCurrentWaypoint	=	curPlayer.currentWaypoint.getHash(),
										keyGoalWaypoint		=	curPlayer.goalWaypoint.getHash();
			
			if (!shortestPath.empty())
			{
				currentWaypoint = shortestPath.pop();
				
				curPlayer.TakeAStep();
				
				//drawOpen(OPEN);		//	Un-comment if you want to visualize the algorithm's OPEN Priority-Queue 
				//drawClosed(CLOSED);	//	Un-comment if you want to visualize the algorithm's CLOSED HashMap
				
				if (data.dbqResultOfContest(currentWaypoint) != null)
				{
					int winner 		=	data.dbqResultOfContest(currentWaypoint).x;
					int loser		=	data.dbqResultOfContest(currentWaypoint).y;
					int winnings	=	data.dbqResultOfContest(currentWaypoint).Height;
					System.out.println("Contest!  Player "+winner+" with $"+player.get(winner).playerWealth+" Wealth wins against player "+loser+" with $"+player.get(loser).playerWealth+" Wealth");
					
					player.get(winner).playerWealth += winnings;
					player.get(loser).playerWealth -= winnings;
					data.db.Update("gamePlayer", winner, player.get(winner).currentWaypoint.getHash(), player.get(winner).playerWealth);
					data.db.Update("gamePlayer", loser, player.get(loser).currentWaypoint.getHash(), player.get(loser).playerWealth);
				}
				
				if (!(data.dbqGetTreasureLocation(currentWaypoint).equals("00")))
				{
					System.out.println("Player "+PID+" found treasure Map at Location: "+keyCurrentWaypoint+".  Finding path to Treasure at: "+data.dbqGetTreasureLocation(currentWaypoint)+" now...");
					data.dbRemoveTreasureMap(currentWaypoint);
				}
			}
			else
			{
				if (curPlayer.onTreasurePath)
				{
					OPEN.clear();
					CLOSED.clear();
					shortestPath.clear();
					
					currentWaypoint.previousWaypoint	=	null;
					currentWaypoint.endingWaypoint		=	finalWaypoint;
					goalWaypoint	=	finalWaypoint;
					OPEN.add(currentWaypoint);
					curPlayer.onTreasurePath	=	false;
					
					System.out.println("Player "+PID+" found his Treasure...Moving on to new goal at:  "+keyGoalWaypoint+", Wealth = $"+curPlayer.playerWealth);
					curPlayer.setSearching();
				}
				else
				{
					if (curPlayer.isPlaying)
					{
						curPlayer.isPlaying		=	false;
						System.out.println("Player "+PID+" is Done!  Goal:  "+keyCurrentWaypoint+" and Wealth = $"+curPlayer.playerWealth);
						curPlayer.playerWealth += curPlayer.playerStrength;
						System.out.println("Player "+PID+" now has $"+curPlayer.playerWealth+" Gold after adding his "+curPlayer.playerStrength+" strength to his $"+((curPlayer.playerWealth)-(curPlayer.playerStrength))+" wealth (per the Project Instructions)");
						data.db.Update("gamePlayer", PID, keyCurrentWaypoint, curPlayer.playerWealth);
					}
				}
			}
			checkStateToWait();
		
			if (!player.get(0).isPlaying && !player.get(1).isPlaying && !player.get(2).isPlaying && !player.get(3).isPlaying)
			{
				if (!curPlayer.onTreasurePath)
				{
					setStatus("Finished Searching");
					System.out.println("All Players have Made It To Their Goal Waypoints!!!");
					setSimRunning(false);
					animatePanel.setComponentState(true, false, false, true, true);
					break;
				}
				else
				{
					setStatus("Found Treasure...continuing to Original Goal");
					currentWaypoint.endingWaypoint	=	finalWaypoint;
					data.dbRemoveGold(keyCurrentWaypoint);
					curPlayer.setSearching();
					break;
				}
			}
			
			curPlayer.CLOSED			=	CLOSED;
			curPlayer.OPEN				=	OPEN;
			curPlayer.shortestPath		=	shortestPath;
			curPlayer.currentWaypoint	=	currentWaypoint;
			curPlayer.goalWaypoint		=	goalWaypoint;
			curPlayer.finalWaypoint		=	finalWaypoint;
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
}