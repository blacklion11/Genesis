
import javax.swing.JPanel;
import java.awt.*;
import java.awt.geom.*;

public class MapPanel extends JPanel
{

	Color[][] tiles;
	boolean canDraw = false;
	int tilesize;

	public MapPanel()
	{
		canDraw = false;
	}
	
	public MapPanel(Color[][] tiles)
	{
		this.tiles = tiles;
		this.tilesize = tilesize;
		canDraw = true;
	}
	
	
	@Override
	public void paintComponent(Graphics g)
	{
		tilesize = this.getSize().height / tiles.length;
		for(int y = 0; y < tiles.length; y++)
		{
			for(int x = 0; x < tiles[0].length; x++)
			{
				g.setColor(tiles[y][x]);
				g.fillRect(x * tilesize, y * tilesize, tilesize, tilesize);
			}
		}
	}


}