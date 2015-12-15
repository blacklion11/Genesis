
import java.awt.*;
import javax.swing.*;
import java.io.*;

public class MapViewer extends JFrame
{
	
	BufferedReader br;
	int width;
	int height;
	int[][] map;
	
	
	public MapViewer()
	{
		setSize(400,400);
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setVisible(true);
	}
	
	public MapViewer(String filename)
	{
		this();
		
		readFile(filename);
	}
	
	public void readFile(String filename)
	{
		try
		{
			br = new BufferedReader(new FileReader(filename));
			String line = br.readLine();
			while(line != null)
			{
				System.out.println(line);
				
				line = br.readLine();
			}
		}
		catch(IOException e){e.printStackTrace();}
	}
	
	
	public static void main(String[] args)
	{
		MapViewer viewer = new MapViewer("test");
	}

}