#include <stdio.h>
#include <stdlib.h>
#include "stringlist.h"

// Creates a new list which is empty
List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// Takes a list
// traverses list, printing each element on a new line
void print_list(List *self) {
	ListNodePtr current = self->head;

	while (current != NULL) {

		printf("%s", current->data);
		current = current->next;

		if (current != NULL)
			printf("\n");
	}
	printf("\n");
}

// Takes a list, and a string
// Inserts string into first position of list
void insert_at_front(List *self, char* data) {
	ListNodePtr new_node = malloc(sizeof *new_node);

	new_node->data = malloc(strlen(data)+1);
	new_node->next = NULL;
	strcpy(new_node->data, data);

	new_node->next = self->head;
	self->head = new_node;
}

// Takes a list, and a string
// Inserts string into first position of list
void delete_list(List *self, char* data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (strncmp(current->data, data) == 0) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
				free(current->data);
				free(current);
				current = self->head;
			}
			else {                    // middle of list
				prev->next = current->next;
				free(current->data);
				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// Takes a list
// Traverses list, freeing memory 
void destroy_list(List *self) {
	ListNodePtr current = self->head;

	while (current != NULL) {
		ListNodePtr to_free = current;
		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}

// Takes a list and asearch term (string)
// Traverses list, returns count of instances of search term in list.
// Can be used to check if string exists in list, or ro find total count of string in list
int list_contains(List *self, char* data) {
	ListNodePtr current = self->head;
	int count = 0;
	
	while (current != NULL) {
		if (strncmp(current->data, data) == 0) {
			count++;
			current = current->next;
		}
		else {
			current = current->next;
		}
	}
	return count;
}

// Takes a two lists; first one non-empty, second one empty
// Copies contents of non-empty list into empty list, without duplicates
void copy_list_without_duplicates(List *self, List *copy) {
	ListNodePtr current = self->head;
	
	while (current != NULL) {

		if (!list_contains(copy, current->data)) {
			insert_at_front(copy, current->data);
		}
		
		current = current->next;
	}
}

// Takes two lists; first one non-empty, second one empty
// Copies contents of non-empty list into empty list in reverse order
void copy_list(List *self, List *copy) {
	ListNodePtr current = self->head;

	while (current != NULL) {

		insert_at_front(copy, current->data);
		current = current->next;
	}

}

