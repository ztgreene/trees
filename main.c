#include <stdio.h>
#include <stdlib.h>
#include "stringlist.h"
#include "bst.h"

// Helper functions

// Prompts user to input a studentID (long), returns it
long get_studentID() {
	long studentID;
	printf("Enter Student ID: ");
	scanf("%ld", &studentID);
	return studentID;
}

// Takes a char array
// Prompts user to input a course name (string), returns it
char *get_courseID(char *buffer) {
	printf("Enter Course Name: ");		// memory for string length?/////////////
	scanf("%99s", buffer);
	return buffer;
}
// For option 6
// Takes a tree, and a course name.
// Traverses tree in-order, printing students enrolled in class
void search_print_in_order(BSTNodePtr self, char *search) {

	if (self != NULL) {
		search_print_in_order(self->left, search);

		if (list_contains(&self->courses, search)) { // Prints if student enrolled in course
			printf("%ld\n", self->data);
		}
		search_print_in_order(self->right, search);
	}
}

// These functions are used for option 5
// Takes a tree, and an empty list
// Traverses tree, adds all enrolments (courses) to list, before returning it

// Creates list of all enrolments (could pass this directly to copy_without_duplicates)
void get_all_enrolments(BSTNodePtr tree, List *list) {

	if (tree != NULL) {

		get_all_enrolments(tree->left, list);

		List student_courses = tree->courses;
		copy_list(&student_courses, list);    /////// Copies list in reverse
		
		get_all_enrolments(tree->right, list);
	}
}

// Takes a tree, and an empty list
// Traverses tree, checking the enrolments students, and adding unique
// classes to the list, before returning it.

// Removes duplicates from list of all enrolments (maybe don't need)
void make_all_courses_list(BSTNodePtr tree, List *list) {

	if (tree != NULL) {

		make_all_courses_list(tree->left, list);

		List student_courses = tree->courses;
		copy_list_without_duplicates(&student_courses, list);

		make_all_courses_list(tree->right, list);
	}

}
// Takes two lists
// Prints each course, and number of students enrolled in it
void print_total_course_summary(List *total_enrolment, List *all_courses) {
	ListNodePtr current = all_courses->head;

	printf("\nCurrent enrolments:\n");
	while (current != NULL) {

		printf("%s %i", current->data, list_contains(total_enrolment, current->data));
		current = current->next;

		if (current != NULL)
			printf("\n");
	}
	printf("\n");
}
//

// Option 1 code
// Takes a tree
// Gets input from user (a long), inserts student in tree
void add_student(BST *self) {

	long studentID = get_studentID();
	insert_bst(self, studentID);
}

// Option 2 code
// Takes a tree
// Gets input from user (a long), finds student and deletes from tree
void remove_student(BST *self) {

	long studentID = get_studentID();
	delete_bst(self, studentID);
}

// Option 3 code
// Takes a tree
// Gets input (studentID - a long, course name - string), enrols student in course
void enrol_student(BST *self) {

	long studentID = get_studentID();

	BSTNodePtr student = find_bst(self, studentID);;

	char course[100];
	get_courseID(course);
	
	insert_at_front(&student->courses, course);
}

// Option 4 code
// Takes a tree
// Gets input (studentID - a long, course name - a string), removes student from course
void unenrol_student(BST *self) {

	long studentID = get_studentID();

	BSTNodePtr student = find_bst(self, studentID);

	char course[100];
	get_courseID(course);

	delete_list(&student->courses, course);
}

// Option 5 code
// Takes a tree
// Creates a list of all courses, and prints it with number of enrolments for each course
void print_course_summary(BST *self) {
	List all_courses = new_list();
	List all_enrolments = new_list();
	make_all_courses_list(self->root, &all_courses);
	get_all_enrolments(self->root, &all_enrolments); // Could call remove_duplicates on this
	print_total_course_summary(&all_enrolments, &all_courses);  // destroy these lists after use
}

// Option 6 code
// Takes a tree
// Gets input (course name - string), and prints list of students enrolled in course
void print_course_enrolment(BST *self) {

	char course[100];
	get_courseID(course);
	
	printf("\nCurrent enrolment for %s:\n", course);
	search_print_in_order(self->root, course);
}

// Option 7 code
// Takes a tree
// Gets input (studentID - a string), and prints list of courses student enrolled in
void print_student_enrolment(BST *self) {

	long studentID = get_studentID();

	BSTNodePtr student = find_bst(self, studentID);
	List student_course_list = student->courses;
	printf("\nEnrolment for %ld:\n", studentID);
	print_list(&student_course_list);
}



/*		 MAIN		*/
void main() {

	// Creates a BST for future operations
	BST tree = new_bst();

	int quit = 0;

	while (!quit) {
		int option = -1;

		printf("\nSelect an option:\n1:Add a student \n2:Remove a student \n3:Enrol a student "
			"\n4:Un-enrol a student \n5:Print summary of courses \n6:Print course enrolment"
			" \n7:Print current enrolment for student \n0:Quit\n");

		scanf("%d", &option);

		switch (option) {
		case 0:
			printf("\nQuitting...\n");
			quit = 1;
			// Write function to free all memory

			// delete_list and delete_bst functions free already
			break;

		case 1:
			printf("\nAdd student selected\n");
			add_student(&tree);
			break;

		case 2:
			printf("\nRemove student selected\n");
			remove_student(&tree);
			break;

		case 3:
			printf("\nEnrol student selected\n");
			enrol_student(&tree);
			break;

		case 4:
			printf("\nUn-enrol student selected\n");
			unenrol_student(&tree);
			break;

		case 5:
			printf("\nPrint summary of courses selected\n");
			print_course_summary(&tree);
			break;

		case 6:
			printf("\nPrint enrolment for course selected\n");
			print_course_enrolment(&tree);
			break;

		case 7:
			printf("\nPrint current enrolment for student\n");
			print_student_enrolment(&tree);
			break;
		}
	} 
}