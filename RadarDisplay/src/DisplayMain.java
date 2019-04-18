import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JFrame;

public class DisplayMain extends Canvas {
	Hazard objs[] = new Hazard[3];

	public static void main(String args[]) {
		JFrame frame = new JFrame("My Drawing");
		Canvas canvas = new DisplayMain();
		canvas.setSize(1010, 550);
		frame.add(canvas);
		frame.pack();
		frame.setVisible(true);
	}

	public void paint(Graphics g) {
		objs[0] = new Hazard(10, 45, 30, 45);
		objs[1] = new Hazard(5, 20, 87, 93);
		objs[2] = new Hazard(5, 27, 145, 160);
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
		for (int i = 0; i < 3; i++) {
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
