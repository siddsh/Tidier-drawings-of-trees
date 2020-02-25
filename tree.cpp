#include "tree.h"
#include "Line.h"
#include "Circle.h"
#include <math.h>
#include <gl/glew.h>
#include <GL/GL.h>
#include<cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include<time.h>
#include<vector>
#define rr 10
#define MINSEP 50
#define YSCALE 30

using namespace std;
/*! Returns the grater number of the two
*/
int max(int a, int b)
{
	return a > b ? a : b;
}
/*! Returns a random number from l to u inclusive
*/
int Random_num(int l, int u)
{
	return rand() % (u - l + 1) + l;
}
/*! This function findulates all offsets for drawing the tree which are stored int the node defined in node class
*/
void setup_tdr(node* root, int level, extreme &rightmost, extreme &leftmost) {
	node* left;
	node* right;
	extreme LR, LL, RR, RL;
	int CURsep, ROOTsep, LOffsum, ROffsum;
	if (root == NULL) {
		leftmost.level = -1;
		rightmost.level = -1;
	}
	else {
		root->y = level;
		left = root->left;
		right = root->right;
		setup_tdr(left, level +1, LR, LL);       //Position left subtree recursively 
		setup_tdr(right, level +1, RR, RL);	  //Postion right subtree recursively
		if (left == NULL && right == NULL) {
			rightmost.adr = root;
			leftmost.adr = root;
			rightmost.level = level;
			leftmost.level = level;
			rightmost.offset = 0;
			leftmost.offset = 0;
			root->offset = 0;
		}
		else {

			//Set up for subtree pushing. Place roots of subtrees minimum distance apart
			CURsep = MINSEP;
			ROOTsep = MINSEP;
			LOffsum = 0;
			ROffsum = 0;
			/*Now consider each level  in turn until one subtree is exhausted
			pushing the subtrees apart when neccessary.*/
			while (left != NULL && right != NULL) {
				if (CURsep < MINSEP) {
					ROOTsep = ROOTsep + (MINSEP - CURsep);
					CURsep = MINSEP;
				}
				//Advance left 
				if (left->right != NULL) {
					LOffsum = LOffsum + left->offset;
					CURsep = CURsep - left->offset;
					left = left->right;
				}
				else {
					LOffsum = LOffsum - left->offset;
					CURsep = CURsep + left->offset;
					left = left->left;
				}
				//Advance right
				if (right->left != NULL) {
					ROffsum = ROffsum - right->offset;
					CURsep = CURsep - right->offset;
					right = right->left;
				}
				else {
					ROffsum = ROffsum + right->offset;
					CURsep = CURsep + right->offset;
					right = right->right;
				}
			}
			/*Set the offset in node root and include it in accumulated offsets in right and left*/
			root->offset = (ROOTsep + 1) / 2;
			LOffsum = LOffsum - root->offset;
			ROffsum = ROffsum + root->offset;
			/*Update extreme descendents information*/
			if (RL.level > LL.level || root->left == NULL) {
				leftmost = RL;
				leftmost.offset = leftmost.offset + root->offset;
			}
			else {
				leftmost = LL;
				leftmost.offset = leftmost.offset - root->offset;
			}
			if (LR.level > RR.level || root->right == NULL) {
				rightmost = LR;
				rightmost.offset = rightmost.offset - root->offset;
			}
			else {
				rightmost = RR;
				rightmost.offset = rightmost.offset + root->offset;
			}
			/*If subtrees of root were of uneven heights,check to see if threadng is necessary
			At most one thread needs to be inserted*/
			if (left != NULL && left != root->left) {
				(RR.adr)->thread = true;
				(RR.adr)->offset = abs((RR.offset + root->offset) - LOffsum);
				if ((LOffsum - root->offset) <= RR.offset) {
					(RR.adr)->left = left;
				}
				else {
					(RR.adr)->right = left;
				}
			}
			else if (right != NULL && right != root->right) {
				(LL.adr)->thread = true;
				(LL.adr)->offset = abs((LL.offset - root->offset) - ROffsum);
				if ((ROffsum + root->offset) >= LL.offset) {
					(LL.adr)->right = right;
				}
				else {
					(LL.adr)->left = right;
				}
			}
		}
	}
}
/*!This procedures forms the pre-order traversal of the tree
converting the relative coordinates to absolute coordinates*/
void petrify(node* root, int col) {
	/*This procedures forms the pre-order traversal of the tree
	converting the relative coordinates to absolute coordinates*/
	if (root != NULL) {
		root->x = col;
		if (root->thread==true) {
			root->thread = false;
			root->left = NULL;
			root->right = NULL;
		}
		petrify(root->left, col - root->offset);
		petrify(root->right, col + root->offset);
	}
}
/*! Array to Balanced Bianary tree;
*/
void tree::GenBST(vector <int> &a, int start, int finish, int beg = 0) //needs to be private
{
	if (start > finish) return;
	int mid = (start + finish) / 2;
	a[beg] = mid;
	GenBST(a, start, mid - 1, beg+1);
	GenBST(a, mid + 1, finish, mid - start + beg+1);
}
/*! tree constructor which will take the number of nodes n
and a boolean dataue which tells if the tree to be generated is balanced or not
*/
tree::tree(int n, bool balanced)
{
	node *N = new node;
	root = N;
	root->left = NULL;
	root->right = NULL;
	root->thread = false;
	vector <int> arr(10000000);
	if (balanced == true)
		GenBST(arr, 0, n - 1);
	else
	{
		srand(time(NULL));
		for (int i = 0; i < n; ++i)
			arr[i] = Random_num(0, n);
	}
	//for (int i = 0; i < n; ++i) cout << arr[i] << " ";
	this->iniz(arr, n);
}

/*! tree constructor which takes an input array of n nodes and converts it into a BST
*/
tree::tree(vector <int> &input, int n)
{
	node *N = new node;
	root = N;
	root->left = NULL;
	root->right = NULL;
	this->iniz(input, n);
}
/*! This is an private function which generates a BST from a given input array
It is used by constructor calls
*/
void tree::iniz(vector <int> &input, int n) //needs to be private
{
	root->data = input[0];
	root->parent = NULL;
	root->level = 0;
	for (int i = 1; i < n; ++i)
	{
		node *N = new node;
		N->left = NULL;
		N->right = NULL;
		N->data = input[i];
		node *curr = this->root, *parent;
		while (curr != NULL)
		{
			parent = curr;
			if (N->data >= curr->data)
				curr = (curr->right);
			else
				curr = (curr->left);
		}
		if (N->data >= parent->data)
		{
			parent->right = N;		
		}
		else
		{
			parent->left = N;
		}
		N->parent = parent;
		N->level = parent->level + 1;
	}
}
/*! Finds the height of the tree
*/
int tree::findHeight(node *N = NULL)
{
	if (N == NULL) N = root;
	if (N->left == NULL && N->right == NULL) return 0;
	if (N->left == NULL) return 1 + findHeight(N->right);
	if (N->right == NULL) return 1 + findHeight(N->left);
	return 1 + max(findHeight(N->left), findHeight(N->right));
}
/*!Draws the Binary tree recursively one child at a time.
This function takes in the values of x and y of the parent node and draws the daughter node
as well as the line connecting it with the parent node
The function does this recursively for each child of the node
No parameters need to be passed when calling it
*/
void tree::drawTree(int cx = 0, int cy = 0, node *N = NULL)
{
	if (N == NULL) N = root;
	if (N == NULL)
		return;
	int dx = N->x;
	int dy = (N->y)*YSCALE-200;
	if (cx == 0 && cy == 0)
	{
		cx = dx;
		cy = dy;
	}
	if (N->left != NULL) //draw the root -> left subtree
		drawTree(dx, dy, N->left);
	if (N->right != NULL) //draw the root -> right subtree
		drawTree(dx, dy, N->right);
	line *l = new line(dx, dy, cx, cy);
	l->draw();//draws line l
	circle* c = new circle(dx, dy, rr);
	c->draw();//draws circle c

}
/*! This function sets up the initial conditions and calls the functions to implement 'TR' algorithm
and draws the tree
*/
void tree::Start(void)
{
	clock_t start=clock();
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	extreme rightmost, leftmost;
	setup_tdr(root,0,rightmost, leftmost);
	petrify(root, 680);
	clock_t end = clock();
	double duration = (end - start) / (double)CLOCKS_PER_SEC;
	cout << "Duration:" << duration << endl;
	cout << "Rendering...\n";
	drawTree();
	clock_t afterdraw = clock();
	duration = (afterdraw - end) / (double)CLOCKS_PER_SEC;
	cout << "Tree drawing Time:" << duration << endl;
	cout << "DRAWING DONE\n";
}
