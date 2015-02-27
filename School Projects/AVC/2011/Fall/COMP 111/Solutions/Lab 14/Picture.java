/* Name:  Brian Joens
	Assignment:    Chapter 14
	Date: 			2011-12-05
	Course:         CIS 111
	Instructor:     Prof. Mummaw
 *
 *This program will draw two conic objects touching each other in the center of the screen.
 *----It does this by drawing a series of ellipses, whose width gradually decreases as they
 *----approach the center of the screen.  This forms the vertex of the cones.
 **/
import javax.swing.*;
import java.awt.*;

public class Picture extends JApplet
{
    	public void init()														// "main" function for applets
 	{
    		getContentPane().setBackground(Color.white);			// Set background to white
     }
     public void paint(Graphics g)										// Paint function
     {
		final int topBound = 0;
		final int leftBound = 0;
		final int rightBound = 500;
		final int bottomBound = 500;
		final int ovalHeight=200;
		
		int ovalWidth=400;													// Changes with height to form conic image
		int middleX = (rightBound/2)-(ovalWidth/2);				// Changes with ovalWidth to keep cone centered
		int currentY=bottomBound;									// Current elevation for center of ellipse
		int ellipseCounter=0;													// Number of ellipses (to be) created
		
		super.paint(g);														// identify "g" as paint object
		g.setColor(Color.red);												

		while (ellipseCounter<(bottomBound/2))					// While number of ellipses created < 1/2 screen height
		{
			g.drawOval(middleX++, currentY--, ovalWidth-=2, ovalHeight);
			ellipseCounter++;													// Increment number of ellipses created
		}
		while (ellipseCounter>0)											// While number of ellipses to be created is greater than  0
		{
			g.drawOval(middleX--, currentY--, ovalWidth+=2, ovalHeight);
			ellipseCounter--;													// Decrement number of ellipses to be created
		}
	}
}