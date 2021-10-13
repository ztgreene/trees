#pragma once
#include "stringlist.h"
typedef struct bstNode {
	long data;
	List courses;
	struct bstNode *left;
	struct bstNode *right;
} *BSTNodePtr;

typedef struct bst {
	BSTNodePtr root;
} BST;


BSTNodePtr find_bst_node(BSTNodePtr self, long n);
BSTNodePtr find_bst(BST *self, long n);

BSTNodePtr insert_bst_node(BSTNodePtr self, long n);
void insert_bst(BST *self, long n);

BSTNodePtr delete_bst_node(BSTNodePtr self, long n);
void delete_bst(BST *self, long n);

BSTNodePtr min_node(BSTNodePtr self);

BST new_bst();

///////////////////////////////////////// Not needed functions
void in_order_traversal(BST *self);

void print_pre_order_bst(BST *self);
void print_in_order_bst(BST *self);
void print_post_order_bst(BST *self);