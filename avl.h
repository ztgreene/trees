#pragma once
#include "stringlist.h"
typedef struct AVLNodePtr {
	long data;
	List courses;
	struct AVLNodePtr *left;
	struct AVLNodePtr *right;
	int      height;
} *AVLNodePtr;

typedef struct avl {
	AVLNodePtr root;
} AVL;


AVLNodePtr find_avl_node(AVLNodePtr self, long n);
AVLNodePtr find_avl(AVL *self, long n);

AVLNodePtr insert_avl_node(AVLNodePtr self, long n);
void insert_avl(AVL *self, long n);

AVLNodePtr delete_avl_node(AVLNodePtr self, long n);
void delete_avl(AVL *self, long n);

AVLNodePtr min_node(AVLNodePtr self);

AVL new_avl();
