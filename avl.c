#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

// Gets height of the tree
int height(AVLNodePtr self)
{
	if (self == NULL)
		return 0;
	return self->height;
}

// Gets maximum of two integers
int maximum(int a, int b)
{
	return (a > b) ? a : b;
}

// Creates/allocates new node, sets fields to NULL
// Used in insertion
AVLNodePtr new_node(long data)
{
	AVLNodePtr node = (AVLNodePtr)malloc(sizeof(AVLNodePtr));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->courses = new_list();
	node->height = 1;  // new node is initially added at leaf
	return(node);
}

// Rotating functions
AVLNodePtr rightRotate(AVLNodePtr y)
{
	AVLNodePtr x = y->left;
	AVLNodePtr T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = maximum(height(y->left), height(y->right)) + 1;
	x->height = maximum(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

AVLNodePtr leftRotate(AVLNodePtr x)
{
	AVLNodePtr y = x->right;
	AVLNodePtr T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	//  Update heights
	x->height = maximum(height(x->left), height(x->right)) + 1;
	y->height = maximum(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}

// Gets balance of node N
int getBalance(AVLNodePtr N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

AVLNodePtr min_node(AVLNodePtr node)
{
	AVLNodePtr current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

// Find node function
AVLNodePtr find_avl_node(AVLNodePtr self, long n) {
	if (self == NULL || (n == self->data)) {
		return self;
	}
	else if (n < self->data) {
		return find_avl_node(self->left, n);
	}
	else {
		return find_avl_node(self->right, n);
	}
}

// Wrapper for find node
AVLNodePtr find_avl(AVL *self, long n) {
	return find_avl_node(self->root, n);
}

// Insert function
AVLNodePtr insert_avl_node(AVLNodePtr node, long data)
{
	if (node == NULL)
		return(new_node(data));

	if (data < node->data)
		node->left = insert_avl_node(node->left, data);
	else if (data > node->data)
		node->right = insert_avl_node(node->right, data);
	else // Equal data not allowed
		return node;

	// Update height of this ancestor node
	node->height = 1 + maximum(height(node->left),
		height(node->right));

	//Get the balance factor of this ancestor
	//node to check whether this node became
	//unbalanced
	int balance = getBalance(node);


	// Rotations
	if (balance > 1 && data < node->left->data)
		return rightRotate(node);

	if (balance < -1 && data > node->right->data)
		return leftRotate(node);

	if (balance > 1 && data > node->left->data)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && data < node->right->data)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

// Wrapper for insert
void insert_avl(AVL *self, long n) {
	self->root = insert_avl_node(self->root, n);
}

// Given a non-empty binary search tree, return the
// node with minimum key value found in that tree.

// Delete a node with given data value
AVLNodePtr delete_avl_node(AVLNodePtr root, long data)
{
	if (root == NULL) {
		return root;
	}

	if (data < root->data) {
		root->left = delete_avl_node(root->left, data);
	}

	else if (data > root->data) {
		root->right = delete_avl_node(root->right, data);
	}

	else
	{
		// node with only one child or no child
		if ((root->left == NULL) || (root->right == NULL))
		{
			AVLNodePtr temp = root->left ? root->left :
				root->right;

			// Zero child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
				*root = *temp; // Copy the contents of
							   // the non-empty child
			free(temp);
		}
		else
		{
			// node with two children
			AVLNodePtr temp = min_node(root->right);

			// Copy the in-order successor's data to this node
			root->data = temp->data;

			// Delete the in-order successor
			root->right = delete_avl_node(root->right, temp->data);
		}
	}

	if (root == NULL) {
		return root;
	}

	root->height = 1 + maximum(height(root->left), height(root->right));

	int balance = getBalance(root);

	// Rotations
	if (balance > 1 && getBalance(root->left) >= 0) {
		return rightRotate(root);
	}

	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}


	if (balance < -1 && getBalance(root->right) <= 0) {
		return leftRotate(root);
	}

	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

// wrapper for delete
void delete_avl(AVL *self, long n) {
	self->root = delete_avl_node(self->root, n);
}

// Creates empty BST                
AVL new_avl() {
	AVL temp;
	temp.root = NULL;
	return temp;
}