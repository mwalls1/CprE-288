package cybot;
public class Hazard {

	int width;
	int distance;
	int degree1;
	int degree2;

	public Hazard(int w, int d, int d1, int d2) {
		width = w;
		distance = d;
		degree1 = d1;
		degree2 = d2;
	}

	public int getDist() {
		return distance;
	}

	public int getDeg1() {
		return degree1;
	}

	public int getDeg2() {
		return degree2;
	}

	public int getWidth() {
		return width;
	}
}
