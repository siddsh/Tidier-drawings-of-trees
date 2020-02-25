#pragma once
class circle {
public:
	circle(int center_x, int center_y, int r);//Constructor to construct the circle with center and radius
	/*Takes the input of Coordinates (x, y) and the center (cx, cy) and the color of the pixle (R, G, B)
	*/
	void draw();
private:
	int center_x, center_y, r; //Center coordinates and radius of the circle
	
/*Takes the input of Coordinates (x, y) and the center (cx, cy) and the color of the pixle (R, G, B)
*/
	void plot_circle(int x, int y, int cx, int cy, int r = 0, int g = 0, int b = 0);
};