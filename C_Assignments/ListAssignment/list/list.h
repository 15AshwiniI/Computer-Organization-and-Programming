/**
 * CS 2110 - Fall 2016 - Homework #10
 *
 * Do not modify this file!
 *
 * list.h
 */

#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

/**************************
 ** Datatype definitions **
 **************************/

/* Forward declaration
 * Don't know what a forward declaration is? 
 * Consult the fountain of knowledge:
 * http://en.wikipedia.org/wiki/Forward_declaration
 */
struct dnode;

/* Given to you for free, however you better know how to do this come time for
 * the final exam!
 * The list struct. Has a head pointer.
 */
typedef struct
{
  struct dnode* head; /* Head pointer either points to a node with data or NULL */
  int size; /* Size of the list */
} list;

/* Given to you for free, However you better know how to do this come time for
 * the final exam!
 * A function pointer type that points to a function that takes in a void* and
 * returns nothing, call it list_op
 */
typedef void (*list_op)(void*);

/* A function pointer type that points to a function that takes in a const void*
 * and returns an int, call it list_pred
 */
typedef int (*list_pred)(const void*);

/* A function pointer type that points to a function that takes in a void* and
 * returns a void*, call it list_copy
 */
typedef void* (*list_copy)(const void*);

/* A function pointer type that points to a function that takes in two void* and
 * returns an int, call it list_eq
 */
typedef int (*list_eq)(const void*, const void*);

/*********************************************
** Prototypes for list library functions.  **
**                                          **
** For more details on their functionality, **
** check list.c.                           **
**********************************************/

/* Creating */
list *create_list(void);
list *copy_list(list *llist, list_copy copy_func);

/* Adding */
void push_front(list *llist, void *data);
bool add(list *llist, int index, void *data);

/* Querying List */
void *front(list *llist);
void *get(list *llist, int index);
int is_empty(list *llist);
int size(list *llist);
void *contains(list *llist, void *data, list_eq eq_func);

/* Removing */
void *pop_front(list *llist);
void *list_remove(list *llist, int index);
list *split_list(list *llist, list_pred pred_func);
void empty_list(list *llist, list_op free_func);

/* Traversal */
void traverse(list *llist, list_op do_func);

#endif
