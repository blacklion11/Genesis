
import java.awt.*;
import javax.swing.*;
import java.io.*;
import java.util.ArrayList;

public class MapViewer extends JFrame
{
	
	BufferedReader br;
	int width;
	int height;
	int[][] map;
	Color[][] tiles;
	ArrayList<String> lines;
	MapPanel panel;
	
	public MapViewer()
	{
		setSize(400,400);
		setResizable(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
	}
	
	public MapViewer(String filename)
	{
		this();
		
		readFile(filename);
	}
	
	void readFile(String filename)
	{
		lines = new ArrayList<String>();
		
		try
		{
			br = new BufferedReader(new FileReader(filename));
			String line = br.readLine();
			while(line != null)
			{
				//System.out.println(line);
				lines.add(line);
				
				line = br.readLine();
			}
		}
		catch(IOException e){e.printStackTrace();}
	}
	
	void parseLines()
	{
		map = new int[lines.size()][];
		for(int i = 0; i < lines.size(); i++)
		{
			String[] tokens = lines.get(i).split(" ");
			if(i == 0)
			{
				for(int k = 0; k < map.length; k++)
				{
					map[k] = new int[tokens.length];
				}
			}
			
			for(int j = 0; j < tokens.length; j++)
			{
				map[i][j] = Integer.parseInt(tokens[j]);
			}
		}
	}
	
	void grade()
	{
		tiles = new Color[map.length][map[0].length];
		for(int y = 0; y < map.length; y++)
		{
			for(int x = 0; x < map[0].length; x++)
			{
				tiles[y][x] = new Color(map[y][x], map[y][x], map[y][x]);
			}
		}
	}
	
	void setPane()
	{
		System.out.println("\nSetting pane");
		
		panel = new MapPanel(tiles);
		//panel.setBackground(Color.BLUE);
		add(panel);
		
		setVisible(true);
	}
	
	void printMap()
	{
		for(int i = 0; i < map.length; i++)
		{
			for(int j = 0; j < map[0].length; j++)
			{
				System.out.print(map[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	
	public static void main(String[] args)
	{
		MapViewer viewer = new MapViewer(args[0]);
		
		viewer.parseLines();
		viewer.printMap();
		viewer.grade();
		viewer.setPane();
	}

}