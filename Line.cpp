#include "Line.h"
#include<math.h>
#include <gl/glew.h>
#include <GL/GL.h>
/*Calculates the values of coordinates on the line and Renders them with double the width and black colour 
*/
void line::draw()
{
	if ((ex >= sx) && (ey >= sy))
	{
		if (ex - sx > ey - sy)
		{
			int k = ey > sy ? 1 : -1;
			int dx = ex - sx;
			int dy = abs(ey - sy);
			int d = 2 * dy - dx;
			int Est = 2 * dy;
			int NorEst = 2 * (dy - dx);
			int x = sx;
			int y = sy;
			glColor3f(0.0, 0.0, 0.0);
			glPointSize(2.0);
			glBegin(GL_POINTS);
			glVertex2i(x, 500 - y);
			glEnd();
			while (x < ex)
			{
				if (d <= 0)
					d += Est;
				else
				{
					d += NorEst;
					y += k;
				}
				x += 1;
				glColor3f(0.0, 0.0, 0.0);
				glPointSize(2.0);
				glBegin(GL_POINTS);
				glVertex2i(x, 500 - y);
				glEnd();
			}
		}
		else
		{
			int k = ex > sx ? 1 : -1;
			int dx = abs(ex - sx);
			int dy = ey - sy;
			int d = 2 * dx - dy;
			int Est = 2 * dx;
			int NorEst = 2 * (dx - dy);
			int x = sx;
			int y = sy;
			glColor3f(0.0, 0.0, 0.0);
			glPointSize(2.0);
			glBegin(GL_POINTS);
			glVertex2i(x, 500 - y);
			glEnd();
			while (y < ey)
			{
				if (d <= 0)
					d += Est;
				else
				{
					d += NorEst;
					x += k;
				}
				y += 1;
				glColor3f(0.0, 0.0, 0.0);
				glPointSize(2.0);
				glBegin(GL_POINTS);
				glVertex2i(x, 500 - y);
				glEnd();
			}
		}
	}
	else if ((ex >= sx) && (ey < sy))
	{
		if (ex - sx > sy - ey)
		{
			int k = ey > sy ? 1 : -1;
			int dx = ex - sx;
			int dy = abs(ey - sy);
			int d = 2 * dy - dx;
			int Est = 2 * dy;
			int NorEst = 2 * (dy - dx);
			int x = sx;
			int y = sy;
			glColor3f(0.0, 0.0, 0.0);
			glPointSize(2.0);
			glBegin(GL_POINTS);
			glVertex2i(x, 500 - y);
			glEnd();
			while (x < ex)
			{
				if (d <= 0)
					d += Est;
				else
				{
					d += NorEst;
					y += k;
				}
				x += 1;
				glColor3f(0.0, 0.0, 0.0);
				glPointSize(2.0);
				glBegin(GL_POINTS);
				glVertex2i(x, 500 - y);
				glEnd();
			}
		}
		else
		{
			int temp = sx;
			sx = ex;
			ex = temp;
			temp = ey;
			ey = sy;
			sy = temp;
			int k = ex > sx ? 1 : -1;
			int dx = abs(ex - sx);
			int dy = ey - sy;
			int d = 2 * dx - dy;
			int Est = 2 * dx;
			int NorEst = 2 * (dx - dy);
			int x = sx;
			int y = sy;
			glColor3f(0.0, 0.0, 0.0);
			glPointSize(2.0);
			glBegin(GL_POINTS);
			glVertex2i(x, 500 - y);
			glEnd();
			while (y < ey)
			{
				if (d <= 0)
					d += Est;
				else
				{
					d += NorEst;
					x += k;
				}
				y += 1;
				glColor3f(0.0, 0.0, 0.0);
				glPointSize(2.0);
				glBegin(GL_POINTS);
				glVertex2i(x, 500 - y);
				glEnd();
			}
		}
	}
	else
	{
		sy += ey;
		ey = sy - ey;
		sy -= ey;

		sx += ex;
		ex = sx - ex;
		sx -= ex;
		draw();
	}
}
/*Constructor for line
*/
line::line(int sx, int sy, int ex, int ey)
{
	this->sx = sx;
	this->sy = sy;
	this->ex = ex;
	this->ey = ey;
}