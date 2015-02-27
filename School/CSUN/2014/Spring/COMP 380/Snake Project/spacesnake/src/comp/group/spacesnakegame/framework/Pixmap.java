package comp.group.spacesnakegame.framework;

import comp.group.spacesnakegame.framework.Graphics.PixmapFormat;

public interface Pixmap
{
	public int getWidth();
	
	public int getHeight();
	
	public PixmapFormat getFormat();
	
	public void dispose();
}
