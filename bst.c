#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

// Search function
BSTNodePtr find_bst_node(BSTNodePtr self, long n) {
	if (self == NULL || (n == self->data)) {
		return self;
	}
	else if (n < self->data) {
		return find_bst_node(self->left, n);
	}
	else {
		return find_bst_node(self->right, n);
	}
}
// Wrapper for search function
BSTNodePtr find_bst(BST *self, long n) {
	return find_bst_node(self->root, n);
}


// Insert function
BSTNodePtr insert_bst_node(BSTNodePtr self, long n) {
	if (self == NULL) {								// Found where to put it
		self = malloc(sizeof *self);
		self->courses = new_list();
		self->data = n; self->left = self->right = NULL;
	}
	else if (n < self->data) {
		self->left = insert_bst_node(self->left, n);
	}
	else if (n > self->data) {
		self->right = insert_bst_node(self->right, n);
	}
	return self;
}
// Wrapper for insert
void insert_bst(BST *self, long n) {
	self->root = insert_bst_node(self->root, n);
}


// Finds minimum node
BSTNodePtr min_node(BSTNodePtr self) {
	BSTNodePtr current = self;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}


// Delete function
BSTNodePtr delete_bst_node(BSTNodePtr self, long n) {
	if (self != NULL) {
		if (n == self->data) {				// Found it
			if (self->left != NULL && self->right != NULL) { // Two child case
				BSTNodePtr successor = min_node(self->right);
				self->data = successor->data;
				self->right = delete_bst_node(self->right, self->data);
			}
			else {									// One/zero child case
				BSTNodePtr to_free = self;
				if (self->left) {
					self = self->left;
				}
				else {
					self = self->right;
				}
				free(to_free);
			}
		}
		else if (n < self->data) {
			self->left = delete_bst_node(self->left, n);
		}
		else {
			self->right = delete_bst_node(self->right, n);
		}
		return self;
	}
}
// Wrapper for delete
void delete_bst(BST *self, long n) {
	self->root = delete_bst_node(self->root, n);
}

// Creates empty BST                
BST new_bst() {
	BST temp;
	temp.root = NULL;
	return temp;
}



/////////////////////////////////////////////////////////////////
// not-needed functions
void in_order_traversal_node(BSTNodePtr self) {
	if (self != NULL) {
		in_order_traversal_node(self->left);
		printf("%ld\n", self->data);
		in_order_traversal_node(self->right);
	}
}
// Wrapper for in-order traversal
void in_order_traversal(BST *self) {
	in_order_traversal_node(self->root);
}

// Pre-order print
void print_pre_order_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		printf("(");
		printf(" %d", self->data);
		print_pre_order_bst_node(self->left);
		print_pre_order_bst_node(self->right);
		printf(")");
	}
	else {
		printf("_");
	}
}
// Wrapper for pre-order print
void print_pre_order_bst(BST *self) {
	print_pre_order_bst_node(self->root);
}

// In-order print
void print_in_order_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		printf("(");
		print_in_order_bst_node(self->left);
		printf(" %d", self->data);
		print_in_order_bst_node(self->right);
		printf(")");
	}
	else {
		printf("_");
	}
}
// Wrapper for in-order print
void print_in_order_bst(BST *self) {
	print_in_order_bst_node(self->root);
}

// Post-order print
void print_post_order_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		printf("(");
		print_post_order_bst_node(self->left);
		print_post_order_bst_node(self->right);
		printf(" %d", self->data);
		printf(")");
	}
	else {
		printf("_");
	}
}
// Wrapper for pre-order print
void print_post_order_bst(BST *self) {
	print_post_order_bst_node(self->root);
}

