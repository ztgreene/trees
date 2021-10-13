#pragma once

typedef struct listNode {
	char *data;
	struct listNode *next;
} *ListNodePtr;

typedef struct list {
	ListNodePtr head;
} List;

List new_list();

void print_list(List *self);

void insert_at_front(List *self, char* data);

void delete_list(List *self, char* data);

void destroy_list(List *self);


// Added utility functions
int list_contains(List *self, char* data);
void copy_list(List *self, List *copy);
void copy_list_without_duplicates(List *self, List *copy);
