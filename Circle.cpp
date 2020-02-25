#include <GL/glew.h>
#include "Circle.h"
#include <GL/freeglut.h>
/*Renders the pixles (x, y) with the color given (R, G, B) using openGL's function 'glBegin'
'glVertex2i' and 'glEnd' with size 2.
*/
void Plot_Px(GLint x, GLint y, double r = 0, double g = 0, double b = 0)
{
	glColor3f(r, g, b);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, 500-y);
	glEnd();
}
/*It Generates the coordinates (x, y) which lie on circle and call the function 'plot_circle' 
to plot them in all 8 part symmetries corresponding its center.
*/
void circle::draw()
{
	int cx = this->center_x, cy = this->center_y, r1 = this->r;
	for (int r = 0; r < r1; r++)
	{
		int x = 0;
		int y = r;
		int d = 1 - r;
		int Est = 3;
		int SthEst = -2 * r + 5;
		while (y > x)
		{
			if (d < 0)
			{
				d += Est;
				Est += 2;
				SthEst += 2;
			}
			else
			{
				d += SthEst;
				Est += 2;
				SthEst += 4;
				--y;
			}
			++x;
			plot_circle(x, y, cx, cy, 1, 0, 0);
		}
	}
	int r = r1;
	int x = 0;
	int y = r;
	int d = 1 - r;
	int Est = 3;
	int SthEst = -2 * r + 5;
	while (y > x)
	{
		if (d < 0)
		{
			d += Est;
			Est += 2;
			SthEst += 2;
		}
		else
		{
			d += SthEst;
			Est += 2;
			SthEst += 4;
			--y;
		}
		++x;
		plot_circle(x, y, cx, cy);
	}
	glFlush();
	
}
/*Takes the input of Coordinates (x, y) and the center (cx, cy) and the color of the pixle (R, G, B)
*/
void circle::plot_circle(int x, int y, int cx, int cy, int r, int g, int b)
{
	Plot_Px(cx + x, cy + y, r, g, b);
	Plot_Px(cx + y, cy + x, r, g, b);

	Plot_Px(cx - x, cy + y, r, g, b);
	Plot_Px(cx + y, cy - x, r, g, b);

	Plot_Px(cx + x, cy - y, r, g, b);
	Plot_Px(cx - y, cy + x, r, g, b);

	Plot_Px(cx - y, cy - x, r, g, b);
	Plot_Px(cx - x, cy - y, r, g, b);
}
/*Constructor to construct the circle with center and radius
*/
circle::circle(int center_x, int center_y, int r)
{
	this-> center_x = center_x;
	this->center_y = center_y;
	this->r = r;
}



