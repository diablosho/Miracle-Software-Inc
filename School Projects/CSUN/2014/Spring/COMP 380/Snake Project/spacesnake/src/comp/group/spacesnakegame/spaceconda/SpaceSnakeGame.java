package comp.group.spacesnakegame.spaceconda;

import comp.group.spacesnakegame.framework.Screen;
import comp.group.spacesnakegame.framework.impl.AndroidGame;

public class SpaceSnakeGame extends AndroidGame
{
	public Screen getStartScreen()
	{
		return new LoadingScreen(this);
	}
}