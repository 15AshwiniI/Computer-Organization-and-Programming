#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Here we are going to write some functions to support a list that stores
 * person data (name, age)
 */
struct person {
	char *name;
	int age;
};

/* Example functions given to you. If you want to truly grasp these concepts,
 * try writing your own structs and functions as well!
 */

// Create a new person
struct person *create_person(const char *name, int age) {
	struct person *p = (struct person*) malloc(sizeof(struct person));
	p->name = malloc(strlen(name) + 1);
	strcpy(p->name, name);
	p->age = age;
	return p;
}

static int print_count;
static char *last_printed;

// Print a person
void print_person(void *data) {
	struct person *p = (struct person*) data;
	++print_count;
	last_printed = p->name;
	printf("%s, %d\n", p->name, p->age);
}

// Copy a person
void *copy_person(const void *data) {
	struct person *p = (struct person*) data;
	return create_person(p->name, p->age);
}

// Free a person
void free_person(void *data) {
	// This is safe because we should only be passing in person struct pointers
	struct person *p = (struct person*) data;
	// free any malloc'd pointers contained in the person struct (just name)
	free(p->name);
	// Now free the struct itself; this takes care of non-malloc'd data, like age.
	free(p);
}

// Compare people by age
int person_age_comp(const void *data1, const void *data2) {
	struct person *p1 = (struct person*) data1;
	struct person *p2 = (struct person*) data2;
	return p1->age - p2->age;
}

// Compare people by name
int person_name_comp(const void *data1, const void *data2) {
	struct person *p1 = (struct person*) data1;
	struct person *p2 = (struct person*) data2;
	return strcmp(p1->name, p2->name);
}

// Tell if a person is age 50
int is_age_50(const void *data) {
	struct person *p = (struct person*) data;
	return p->age == 50;
}

// Tell if a person is 23 or older
int is_age_23_or_greater(const void *data) {
	struct person *p = (struct person*) data;
	return p->age >= 23;
}

/* This main function does a little testing. Like all good CS Majors, you should
 * test your code here. There is no substitute for testing and you should be
 * sure to test for all edge cases, like calling empty_list on an empty list.
 */
int main(void) {

	printf("\nTEST CASE 1\nAn empty list should have size 0:\n");
	list *d1 = create_list();
	printf("Size: %d\n", size(d1));
	assert(!size(d1));
	assert(!d1->head);
	assert(is_empty(d1));

	printf("\nTEST CASE 2\nAfter adding one element, size should be 1:\n");
	push_front(d1, create_person("Andrew", 26));
	printf("Size: %d\n", size(d1));
	assert(size(d1) == 1);
	assert(!is_empty(d1));

	printf("\nTEST CASE 3\nTraversal should print the one element:\n");
	print_count = 0;
	last_printed = NULL;
	traverse(d1, print_person);
	assert(!strcmp(last_printed, "Andrew") && print_count == 1);

	printf("\nTEST CASE 4\nThe one element should be the front:\n");
	print_count = 0;
	last_printed = NULL;
	print_person(front(d1));
	assert(!strcmp(last_printed, "Andrew") && print_count == 1);


	printf("\nTEST CASE 5\nAndrew should be contained in the list:\n");
	struct person *andrew = create_person("Andrew", 50);
	printf("Andrew %s in list\n", contains(d1, andrew, person_name_comp) ?
			"is" : "isn\'t");
	struct person *ptemp = (struct person*) contains(d1, andrew, person_name_comp);
	assert(ptemp->age == 26);

	printf("\nTEST CASE 6\nCollin should not be contained in the list:\n");
	struct person *collin = create_person("Collin", 23);
	printf("Collin %s in list\n", contains(d1, collin, person_name_comp) ?
			"is" : "isn\'t");
	assert(!contains(d1, collin, person_name_comp));

	printf("\nTEST CASE 7\nPop Andrew from the front...\n");
	ptemp = (struct person*) pop_front(d1);
	assert(!size(d1));
	assert(!person_name_comp(andrew, ptemp));
	printf("Success!\n");
	free_person(ptemp);

	printf("\nTEST CASE 8\nAdd Collin, pop from the back...\n");
	add(d1, 0, collin);
	assert(size(d1) == 1);
	ptemp = list_remove(d1, 0);
	assert(ptemp == collin);
        printf("size is %d\n", size(d1));
	assert(size(d1) == 0);
	printf("Success!\n");

	// Free these people because we are done using them
	free_person(andrew);
	free_person(collin);

	printf("\nTEST CASE 9\nThere should be 7 elements in this list:\n");
	list *d2 = create_list();
	push_front(d2, create_person("Nick", 23));
	push_front(d2, create_person("Henry", 21));
	push_front(d2, create_person("Marie", 22));
	push_front(d2, create_person("Clayton", 24));
	push_front(d2, create_person("Andrew", 25));
	push_front(d2, create_person("Brandon", 28));
	push_front(d2, create_person("Leahy", 66));
	printf("Size: %d\n", size(d2));
	assert(size(d2) == 7);

	printf("\nTEST CASE 10\nFront should be last element pushed to front (Leahy):\n");
	ptemp = (struct person*) front(d2);
	print_person(ptemp);
	struct person *leahy = create_person("Leahy", 67);
	assert(!person_name_comp(leahy, ptemp));
	assert(ptemp->age == 66);
	
	printf("\nTEST CASE 11\nLast element pushed (Nick):\n");
	ptemp = (struct person*) get(d2, 6);
	print_person(ptemp);
	struct person *nick = create_person("Nick", 23);
	assert(!person_name_comp(nick, ptemp));
	assert(ptemp->age == 23);

	printf("\nTEST CASE 12\nThe person at index 2 should be Andrew:\n");
	ptemp = (struct person*) get(d2, 2);
	print_person(ptemp);
	struct person *andrew1 = create_person("Andrew", 25);
	assert(!person_name_comp(andrew1, ptemp));
	assert(ptemp->age == 25);

	printf("\nTEST CASE 13\nThere should be someone age 24 in the list:\n");
	struct person *person24 = create_person("", 24);
	ptemp = (struct person*) contains(d2, person24, person_age_comp);
	print_person(ptemp);
	assert(!strcmp(ptemp->name, "Clayton"));

	printf("\nTEST CASE 14\nThere should be nobody age 30 in the list:\n");
	struct person *person30 = create_person("", 30);
	ptemp = (struct person*) contains(d2, person30, person_age_comp);
	if(ptemp) {
		printf("Found: ");
		print_person(ptemp);
	} else {
		printf("Success!\n");
	}
	assert(!ptemp);

	// Clean up temporary people
	free_person(leahy);
	free_person(nick);
	free_person(andrew1);
	free_person(person24);
	free_person(person30);

	printf("\nTEST CASE 15\nPopping front twice leaves a size 5 list:\n");
	assert(ptemp = (struct person*) pop_front(d2));
	free_person(ptemp);
	assert(ptemp = (struct person*) pop_front(d2));
	free_person(ptemp);
	printf("Size: %d\n", size(d2));
	assert(size(d2) == 5);

	printf("\nTEST CASE 16\nPrint the 5 elements from the list:\n");
	print_count = 0;
	last_printed = NULL;
	traverse(d2, print_person);
	assert(print_count == 5);
	assert(!strcmp(last_printed, "Nick"));

	printf("\nTEST CASE 17\nSplit list people age 50 (0 people):\n");
	list *split = split_list(d2, is_age_50);
	assert(split->size == 0);
        free(split);

	printf("\nTEST CASE 18\nRemoving people age 23 or greater (3 people):\n");

	printf("\nBefore Split List:\n");
	traverse(d2, print_person);
	split = split_list(d2, is_age_23_or_greater);

	printf("\nYounger than 23 List:\n");
	traverse(d2, print_person);
	assert(d2->size == 2);

	printf("\n23 or Older List:\n");
	traverse(split, print_person);
	assert(split->size == 3);

	printf("\nTEST CASE 19\nOnly two people should be left in the list:\n");
	print_count = 0;
	last_printed = NULL;
	traverse(d2, print_person);
	assert(print_count == 2);

	// Empty the list now that we're done with it
	empty_list(d2, free_person);
        empty_list(split, free_person);
	assert(!size(d2));

	printf("\nTEST CASE 20\nLet's try making a copy of a list of 4 people:\n");
	list *d3 = create_list();
	push_front(d3, create_person("Baijun", 20));
	push_front(d3, create_person("Brandi", 21));
	push_front(d3, create_person("Patrick", 19));
	push_front(d3, create_person("Shayan", 22));
	printf("Original:\n");
	traverse(d3, print_person);
	printf("Copy:\n");
	list *d4 = copy_list(d3, copy_person);
	print_count = 0;
	last_printed = NULL;
	traverse(d4, print_person);
	assert(print_count == 4);
	assert(!strcmp(last_printed, "Baijun"));

	printf("\nTEST CASE 21\nAfter emptying first list, second should persist:\n");
	empty_list(d3, free_person);
	print_count = 0;
	last_printed = NULL;
	traverse(d4, print_person);
	assert(print_count == 4);
	assert(!strcmp(last_printed, "Baijun"));
	empty_list(d4, free_person);
	assert(!size(d4));

	printf("\nTEST CASE 22\nPassing in null lists to functions should return 0...\n");
	assert(!copy_list(NULL, NULL));
	assert(!front(NULL));
	assert(!is_empty(NULL));
	assert(!size(NULL));
	assert(!contains(NULL, NULL, NULL));
	assert(!pop_front(NULL));
	printf("Success!\n");



	// TODO
	printf("\nMake sure to write more test cases as well in test.c! "
			"The ones given aren't comprehensive.\n"
			"Also test using valgrind. Half credit will be given to functions "
			"with memory leaks or memory errors.\n");



	// Clean up any malloc'd structures leftover to prevent memory leaks
	free(d1);
	free(d2);
	free(d3);
	free(d4);
        free(split);

	return 0;
}
