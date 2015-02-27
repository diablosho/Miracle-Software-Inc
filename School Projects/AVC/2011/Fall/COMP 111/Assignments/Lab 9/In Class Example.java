import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class MyApplet extends JApplet
{
	private Timer timer;
	private final int TIME_DELAY = 500;
	private int x2 = 0;
	private boolean on = true;
	public void init()
	{
		getContentPane().setBackground(Color.black);
		timer = new Timer(TIME_DELAY, new TimerListener());
		timer.start();
	}
	
	public void paint(Graphics g)
	{
		int x;
		super.paint(g);
		
		g.setColor(Color.black);
		g.drawRect(0,0,499,299);
		/*
		g.setColor(Color.red);
		g.drawLine(0,0,40,40);
		g.fillRect(40,40,20,30);
		g.drawOval(60,70,40,40);
		g.drawArc(100,100,50,50,-10,180);
		g.setColor(Color.green);
		g.drawArc(98,100,50,50,0,170);
		g.drawString("My Masterpiece", 10,299);
		g.setColor(Color.blue);
		for(x = 0; x < 500; x+=20)
			g.drawLine(x,0,499-x,299);
		for(x=0;x<500;x+=4)
			g.drawLine(0,x,x,299);
		*/
		g.setColor(Color.yellow);
		if(on)
		{
			on = false;
			g.fillArc(x2,150,20,20,0,360);
		}
		else
		{
			on = true;
			g.fillArc(x2,150,20,20,45,270);
		}
	}
	
	private class TimerListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			x2+=2;
			if(x2 > 480)
				x2 = 0;
			repaint();
		}
	}
}






