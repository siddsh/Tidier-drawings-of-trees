#include <iostream>
#include "tree.h"
#include <math.h>
#include <gl/glew.h>
#include <GL/GL.h>
#include <vector>
#include <GL/freeglut.h>

using namespace std;


void init() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1366, 768);
	glutCreateWindow("Tree Drawing");
	glClearColor(.0, 1.0, 1.0, 0);
	glColor3f(1.0, 1.0, 1.0);
	gluOrtho2D(0, 1366, 0, 768);

}
tree *t;
void draw_tree_tidier_wrapper(void)
{
	t->Start();
}

int main(int argc, char **argv)
{
	system("cls");
	glutInit(&argc, argv);
	init();
	int choose, n=0;
	vector <int> arr(10000000);
	int c = 1;
	while (c)
	{
		cout << " 1. Make a Randomized Tree of 'N' Nodes" << endl;
		cout << " 2. Make a User Input Iree in \"Binary Search\" Tree Form" << endl;
		cout << " 3. Make a Balanced Tree Of 'N' Nodes" << endl;
		cout << "Choose: ";
		cin >> choose;
		if (choose < 4 && choose > 0)
		{
			while (!(n >= 1))
			{
				cout << "Please enter number of vertices greater than 1: ";
				cin >> n;
			}
		}

		c = 0;
		if (choose == 2)
		{
			cout << "Please enter the array: ";
			for (int i = 0; i < n; ++i) cin >> arr[i];
			t = new tree(arr, n);
		}
		else if (choose == 1)
			t = new tree(n, false);
		else if (choose == 3)
			t = new tree(n, true);
		else c = 1;
	}
	glutDisplayFunc(draw_tree_tidier_wrapper);
	glutMainLoop();
	return 0;
}