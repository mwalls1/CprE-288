package cybot;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.PopupMenu;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.InputStream;
import java.io.IOException;
import java.net.UnknownHostException;
import java.sql.Time;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import java.io.InputStream;
public class DisplayMain extends Canvas {
	static Hazard objs[] = new Hazard[10];
	static int numObjects = 0;
	static botTalk out;
	public static void calculate() {
		numObjects = 0;
		boolean f = true;
		String htjh = "#";
		int[] width = new int[10];
		int[] distance = new int[10];
		int[] degs = new int[20];
		String[] data = new String[30];
		int k = 0;
		int z = 0;
		String temp = "";
		while(f)
		{
			temp = out.readString();
			System.out.println(temp);
			if(temp.contains(htjh))
			{
				//out.closeCon();
				break;
			}
			
			
		}
		Scanner scan = new Scanner(temp);
		while(scan.hasNextLine())
		{
			data[k] = scan.nextLine();
			k++;
		}
		for(int x = 0; x < k; x++)
		{
			scan = new Scanner(data[x]);
			if(x==0)
			{
				while(scan.hasNext())
				{
					width[z] = (int)scan.nextDouble();
					z++;
					numObjects++;
				}
				z = 0;
			}
			if(x==1)
			{
				while(scan.hasNext())
				{
					distance[z] = scan.nextInt();
					z++;
				}
				z = 0;
			}
			if(x==2)
			{
				while(scan.hasNextInt())
				{
					degs[z] = scan.nextInt();
					z++;
				}
				z = 0;
			}
		}
		scan.close();
		for(int obj = 0; obj < numObjects; obj++)
		{
			objs[obj] = new Hazard(width[obj], distance[obj], degs[z],degs[z+1]);
			z+=2;
		}

	}
	public static void test1(JPanel panel, JTextArea textArea, JTextArea textArea2, Canvas canvas, JFrame frame, JButton start) throws UnknownHostException, IOException {
		out = new botTalk();
		// System.out.print(width[0]);
		KeyListener listener = new KeyListener() {

			@Override
			public void keyPressed(KeyEvent arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void keyReleased(KeyEvent e) {
				// TODO Auto-generated method stub
				if(e.getKeyCode() == KeyEvent.VK_M) {
					out.sendString("m");
					textArea2.setText(null);
					panel.repaint();
				}
				else if(e.getKeyCode() == KeyEvent.VK_W) {
					out.sendString("w");
					  try {
							TimeUnit.MILLISECONDS.sleep(1000);
						} catch (InterruptedException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
				  String tmp = out.readString();
				
					if(tmp.contains("cliff") || tmp.contains("boundary")) {
						
						textArea.setText(null);
						 if(tmp.contains("boundary")) 
						   {
								
								textArea.append("Boundary detected. Bot moved backwards and turned 180 degrees.\n");
								
							
							}
						 else {
						textArea.append("Cliff detected. Bot moved backwards and turned 180 degrees.\n");
						 }
				
					}
					else if(tmp.contains("bumpLeft") || tmp.contains("bumpRight"))
					{
						textArea.setText(null);
						if(tmp.contains("bumpRight"))
						{
						
							textArea.append("Bump detected on right side. Bot moved back and turned 90 degrees left.");
							


						}
						else {
						textArea.append("Bump detected on left side. Bot moved back and turned 90 degrees right");
						}
						
					}
					
					textArea2.setText(null);
					panel.repaint();
				}
				else if(e.getKeyCode() == KeyEvent.VK_R) {
					out.sendString("r");
					textArea.setText(null);
					textArea.append("Scanning finished!");
				
					calculate();
					
					canvas.repaint();
					panel.repaint();
					frame.repaint();
					textArea2.setText(null);
				}
				else if(e.getKeyCode() == KeyEvent.VK_D) {
					out.sendString("d");
					
					canvas.repaint();
					panel.repaint();
					frame.repaint();
					textArea2.setText(null);
				}
				else if(e.getKeyCode() == KeyEvent.VK_A) {
					out.sendString("a");
					
					panel.repaint();
					frame.repaint();
					textArea2.setText(null);
				}
			}

			@Override
			public void keyTyped(KeyEvent arg0) {
				// TODO Auto-generated method stub
				
			}
			
		};
		textArea.append("text");
		textArea2.append("key listener");
		textArea2.addKeyListener(listener);
		
		
        JButton scan = new JButton("Scan");
        JButton standby = new JButton("Standby");
        JButton forward = new JButton("Forward");
        JButton right = new JButton("right");
        JButton left = new JButton("left");
        
        JButton music = new JButton("Music");
        
        

       
	
		canvas.setSize(1010, 550);

	
		frame.getContentPane().add(panel);
		
		frame.setSize(1500, 1500);
		//frame.add(canvas);
		frame.pack();
		frame.setVisible(true);
		
		
		start.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
			out.sendString("b");
		    //panel.repaint();
			panel.remove(start);
			panel.add(standby);
			panel.add(canvas);
	/*		panel.add(scan);
		    panel.add(forward);
		    panel.add(left);
		    panel.add(right);*/
		   // panel.add(music);
	        panel.add(textArea);
	        panel.add(textArea2);
		  panel.repaint();
		    

		        frame.setSize(1500, 1500);
		        frame.repaint();
			}
		});
	/*	music.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
			out.sendString("m");
			panel.repaint();
			}
		});*/
	/*	forward.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
			out.sendString("w");
			  try {
					TimeUnit.MILLISECONDS.sleep(1000);
				} catch (InterruptedException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
		  String tmp = out.readString();
		
			if(tmp.contains("cliff") || tmp.contains("boundary")) {
				
				textArea.setText(null);
				 if(tmp.contains("boundary")) 
				   {
						
						textArea.append("Boundary detected. Bot moved backwards and turned 180 degrees.\n");
						
					
					}
				 else {
				textArea.append("Cliff detected. Bot moved backwards and turned 180 degrees.\n");
				 }
		
			}
			else if(tmp.contains("bumpLeft") || tmp.contains("bumpRight"))
			{
				textArea.setText(null);
				if(tmp.contains("bumpRight"))
				{
				
					textArea.append("Bump detected on right side. Bot moved back and turned 90 degrees left.");
					


				}
				else {
				textArea.append("Bump detected on left side. Bot moved back and turned 90 degrees right");
				}
				
			}
			
			
			panel.repaint();
		
			}
		});*/
		
		
	/*	scan.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
			out.sendString("r");
			textArea.setText(null);
			textArea.append("Scanning finished!");
		
			calculate();
			
			canvas.repaint();
			panel.repaint();
			frame.repaint();
			}
		});*/
		

	/*right.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
			out.sendString("d");
		
			canvas.repaint();
			panel.repaint();
			frame.repaint();
			}
		});*/
	/*	left.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
			out.sendString("a");
		
			panel.repaint();
			frame.repaint();
			}
		});*/
	}
	public static void main(String args[])throws UnknownHostException, IOException, InterruptedException {
		out = new botTalk();
		String temp = out.readString();
		Canvas canvas = new DisplayMain();
		JFrame frame = new JFrame("My Drawing");
		JPanel panel = new JPanel();
		JTextArea textArea = new JTextArea();
		JTextArea textArea2 = new JTextArea();
		JButton start = new JButton("Start");
		JButton standby = new JButton("Standby");
		start.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				out.sendString("b");
				// panel.repaint();
				panel.remove(start);
				panel.add(standby);
				panel.add(canvas);
				/*
				 * panel.add(scan); panel.add(forward); panel.add(left); panel.add(right);
				 */
				// panel.add(music);
				panel.add(textArea);
				panel.add(textArea2);
				panel.repaint();

				frame.setSize(1500, 1500);
				frame.repaint();
			}
		});
		panel.add(start);
		canvas.setSize(1010, 550);
		frame.getContentPane().add(panel);
		frame.setSize(1500, 1500);
		frame.pack();
		frame.setVisible(true);
		JButton scan = new JButton("Scan");
		JButton forward = new JButton("Forward");
		JButton right = new JButton("right");
		JButton left = new JButton("left");
		JButton music = new JButton("Music");
		// System.out.print(width[0]);
		KeyListener listener = new KeyListener() {

			@Override
			public void keyPressed(KeyEvent arg0) {
				// TODO Auto-generated method stub

			}

			@Override
			public void keyReleased(KeyEvent e) {
				// TODO Auto-generated method stub
				if (e.getKeyCode() == KeyEvent.VK_M) {
					out.sendString("m");
					textArea2.setText(null);
					panel.repaint();
				} else if (e.getKeyCode() == KeyEvent.VK_W) {
					out.sendString("w");
					try {
						TimeUnit.MILLISECONDS.sleep(1000);
					} catch (InterruptedException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					String tmp = out.readString();

					if (tmp.contains("cliff") || tmp.contains("boundary")) {

						textArea.setText(null);
						if (tmp.contains("boundary")) {

							textArea.append("Boundary detected. Bot moved backwards and turned 180 degrees.\n");

						} else {
							textArea.append("Cliff detected. Bot moved backwards and turned 180 degrees.\n");
						}

					} else if (tmp.contains("bumpLeft") || tmp.contains("bumpRight")) {
						textArea.setText(null);
						if (tmp.contains("bumpRight")) {

							textArea.append("Bump detected on right side. Bot moved back and turned 90 degrees left.");

						} else {
							textArea.append("Bump detected on left side. Bot moved back and turned 90 degrees right");
						}

					}

					textArea2.setText(null);
					panel.repaint();
				} else if (e.getKeyCode() == KeyEvent.VK_R) {
					out.sendString("r");
					textArea.setText(null);
					textArea.append("Scanning finished!");

					calculate();

					canvas.repaint();
					panel.repaint();
					frame.repaint();
					textArea2.setText(null);
				} else if (e.getKeyCode() == KeyEvent.VK_D) {
					out.sendString("d");

					canvas.repaint();
					panel.repaint();
					frame.repaint();
					textArea2.setText(null);
				} else if (e.getKeyCode() == KeyEvent.VK_A) {
					out.sendString("a");

					panel.repaint();
					frame.repaint();
					textArea2.setText(null);
				}
			}

			@Override
			public void keyTyped(KeyEvent arg0) {
				// TODO Auto-generated method stub

			}

		};
		textArea.append("text");
		textArea2.append("key listener");
		textArea2.addKeyListener(listener);
		canvas.setSize(1010, 550);

		frame.getContentPane().add(panel);

		frame.setSize(1500, 1500);
		// frame.add(canvas);
		frame.pack();
		frame.setVisible(true);

		
		//test1(panel, textArea, textArea2,canvas,frame, start);
	}

	public void paint(Graphics g) {
		g.drawArc(0, 0, 1000, 1000, 0, 180);
		g.drawArc(50, 50, 900, 900, 0, 180);
		g.drawArc(100, 100, 800, 800, 0, 180);
		g.drawArc(150, 150, 700, 700, 0, 180);
		g.drawArc(200, 200, 600, 600, 0, 180);
		g.drawArc(250, 250, 500, 500, 0, 180);
		g.drawArc(300, 300, 400, 400, 0, 180);
		g.drawArc(350, 350, 300, 300, 0, 180);
		g.drawArc(400, 400, 200, 200, 0, 180);
		g.drawArc(450, 450, 100, 100, 0, 180);
		g.drawString("50", 0, 520);
		g.drawString("45", 50, 520);
		g.drawString("40", 100, 520);
		g.drawString("35", 150, 520);
		g.drawString("30", 200, 520);
		g.drawString("25", 250, 520);
		g.drawString("20", 300, 520);
		g.drawString("15", 350, 520);
		g.drawString("10", 400, 520);
		g.drawString("50", 990, 520);
		g.drawString("45", 940, 520);
		g.drawString("40", 890, 520);
		g.drawString("35", 840, 520);
		g.drawString("30", 790, 520);
		g.drawString("25", 740, 520);
		g.drawString("20", 690, 520);
		g.drawString("15", 640, 520);
		g.drawString("10", 590, 520);
		g.drawLine(0, 500, 1000, 500);
		g.fillOval(320, 500, 360, 360);
		g.drawLine(320,500, 320, 0);
		g.drawLine(680,500, 680, 0);
		for (int i = 0; i < numObjects; i++) {
			if (((objs[i].getDeg1() + objs[i].getDeg2()) / 2) < 90) {
				int distance = objs[i].getDist() + (objs[i].getWidth() / 2);
				int xDist = (int) (distance * Math.cos(Math.toRadians((objs[i].getDeg2() + objs[i].getDeg1()) / 2)));
				int yDist = (int) (distance * Math.sin(Math.toRadians((objs[i].getDeg2() + objs[i].getDeg1()) / 2)));
				xDist = 49 + xDist;
				yDist = 49 - yDist;
				int xMin = 10*(xDist - objs[i].getWidth() / 2);
				int yMin = 10*(yDist - objs[i].getWidth() / 2);
				if(objs[i].getWidth()<10)
					g.setColor(new Color(0,0,255));
				if(objs[i].getWidth()>9)
					g.setColor(new Color(0,255,0));
				g.fillOval(xMin, yMin, 10*objs[i].getWidth(), 10*objs[i].getWidth());
			} else if (((objs[i].getDeg1() + objs[i].getDeg2()) / 2) > 90) {
				int distance = objs[i].getDist() + (objs[i].getWidth() / 2);
				int angle = (objs[i].getDeg1() + objs[i].getDeg2()) / 2;
				angle = 180 - angle;
				int xDist = (int) (distance * Math.cos(Math.toRadians(angle)));
				int yDist = (int) (distance * Math.sin(Math.toRadians(angle)));
				xDist = 49 - xDist;
				yDist = 49 - yDist;
				int xMin = 10*(xDist - objs[i].getWidth() / 2);
				int yMin = 10*(yDist - objs[i].getWidth() / 2);
				if(objs[i].getWidth()<10)
					g.setColor(new Color(0,0,255));
				if(objs[i].getWidth()>9)
					g.setColor(new Color(0,255,0));
				g.fillOval(xMin, yMin, 10*objs[i].getWidth(), 10*objs[i].getWidth());
			}
			else if (((objs[i].getDeg1() + objs[i].getDeg2()) / 2) == 90) {
				int distance = objs[i].getDist() + (objs[i].getWidth() / 2);
				int xDist = 0;
				int yDist = distance;
				xDist = 49 + xDist;
				yDist = 49 - yDist;
				int xMin = 10*(xDist - objs[i].getWidth() / 2);
				int yMin = 10*(yDist - objs[i].getWidth() / 2);
				if(objs[i].getWidth()<10)
					g.setColor(new Color(0,0,255));
				if(objs[i].getWidth()>9)
					g.setColor(new Color(0,255,0));
				g.fillOval(xMin, yMin, 10*objs[i].getWidth(), 10*objs[i].getWidth());
			}
		}

	}
}
