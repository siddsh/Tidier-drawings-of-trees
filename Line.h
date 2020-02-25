class line {
public:	
	/*Constructor for line
	*/
	line(int sx, int sy, int ex, int ey);
	/*Calculates the values of coordinates on the line and Renders them with double the width and black colour
	*/
	void draw();
private:
	int sx, sy, ex, ey;//start and end coordinates of the line 
};