#pragma once
#include <vector>

using namespace std;

typedef struct node {
	int data;				//data
	struct node *left;		//pointer to left child
	struct node *right;		//pointer to right child
	struct node *parent;
	int status;
	int modifier;
	int level;
	int x;						//x coordinate of node
	int y;						//y coordinate of node
	int offset;					//distance to each daughter
	bool thread;				//Threading active or not
}node;
typedef struct extreme {
	node *adr;		//address to a node
	int offset;		//offset from root of subtree
	int level;		//height of the tree
}extreme;
class tree
{
private:
	/*! Points to the root of the tree.*/
	node *root;
	/*! Array to Balanced Bianary tree;
	*/
	void GenBST(vector <int> & , int , int, int);
	/*! Finds the height of the tree
	*/
	int findHeight(node *N);
	/*! Generates a BST from a given input array 
	It is used by constructor
	*/
	void iniz(vector <int>&, int n);
	/*!Draws the Binary tree recursively one child at a time. 
	This function takes in the values of x and y of the parent node and draws the daughter node
	as well as the line connecting it with the parent node
	The function does this recursively for each child of the node
	No parameters need to be passed when calling it
	*/
	void drawTree(int cx, int cy, node *N);
public:
	/*! tree constructor which will take the number of nodes n and the array which has the data of each node
	*/
	tree(vector <int>&, int n); 
	/*! tree constructor which will take the number of nodes n
	and a boolean value which tells if the tree to be generated is balanced or not
	*/
	tree(int n, bool balanced); 
	/*! This function sets up the initial conditions and calls the functions to implement 'TR' algorithm
	and draws the tree
	*/
	void Start(); 											
};



