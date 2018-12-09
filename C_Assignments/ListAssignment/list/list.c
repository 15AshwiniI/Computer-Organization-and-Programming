/**
 * CS 2110 - Fall 2016 - Homework #10
 *
 * @author YOUR NAME HERE
 *
 * list.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct. Has a next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO */
/* Design consideration: Only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION, DO NOT PUT IT IN OTHER FILES */
typedef struct dnode
{
    struct dnode* next; /* Pointer to next node */
    void* data; /* User data */
} node;

/* Do not create any global variables here. Your list library should obviously
 * work for multiple concurrent lists */

// This function is declared as static since you should only be calling this
// function from inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    /// @todo Implement changing the return value!
    (void)data;
    return NULL;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head to NULL.
  *
  * @return an empty list
  */
list* create_list(void)
{
    /// @todo Implement changing the return value!
    (void)create_node;
    return NULL;
}

/** front
  *
  * Gets the data at the front of the list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the list or NULL.
  */
void *front(list *llist)
{
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember, the
    /// user should never deal with the list nodes.
    (void)llist;
    return NULL;
}

/** get
  *
  * Gets the data at the specified index in the list
  *
  * @param llist a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @return The data from the specified index in the list or NULL if index is
  *         out of range of the list.
  */
void *get(list *llist, int index)
{
    /// @todo Implement changing the return value!
    (void)llist;
    (void)index;
    return NULL;
}

/** add
  *
  * Add the element at the specified index in the list
  * You should be able to add up to exactly one past the length of the list.
  * For example, if you have no elements in the list,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the list,
  * you should be able to add to index 2 but no further.
  *
  * @param llist a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @return false if the index is out of bounds
  *         (do not add the data in this case)
  *         otherwise return true
  */
bool add(list *llist, int index, void *data)
{
    /// @todo Implement changing the return value!
    (void) llist;
    (void) index;
    (void) data;
    return NULL;
}

/** list_remove
  *
  * Removes the data from the specified index in the list
  *
  * @param llist a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @return The data from the specified index in the list or NULL if index is
  *         out of range of the list.
  */
void *list_remove(list *llist, int index)
{
    /// @todo Implement changing the return value!
    (void) llist;
    (void) index;
    return NULL;
}

/** push_front
  *
  * Adds the data to the front of the list.
  *
  * @param llist a pointer to the list structure.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list *llist, void *data)
{
    /// @todo Implement
    (void) llist;
    (void) data;
}

/** pop_front
  *
  * Removes the node at the front of the list, and returns its data to the user
  *
  * @param llist a pointer to the list.
  * @return The data in the first node, or NULL if the list is NULL or empty
  */
void *pop_front(list *llist)
{
    /// @todo Implement
    (void) llist;
    return NULL;
}

/** contains
  *
  * Traverses the list, trying to see if the list contains some data.
  * Since non-NULL values are considered true, this can be used like a boolean
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * eq_func says is equal. For instance, if you have a list of person structs:
  *   (Andrew, 26), (Nick, 24), (Collin, 23), (Marie, 23)
  * And you want to return any person whose age is 22, you could create a new
  * person struct (<NULL>, 24) with an eq_func that returns age == 24 and pass
  * that into this function as "data". contains() would then return (Nick, 24)
  *
  * If there are multiple pieces of data in the list which are equal to the
  * "data" parameter, return any one of them.
  *
  * @param llist a pointer to the list structure
  * @param data The data, to see if it exists in the list
  * @param eq_func A function written by the user that will tell if two pieces
  *                of data are equal. Returns 0 if equal, something else
  *                otherwise. Imagine subtracting two numbers.
  * @return The data contained in the list, or NULL if it doesn't exist
  */
void *contains(list *llist, void *data, list_eq eq_func) {
    /// @todo Implement
    (void) llist;
    (void) data;
    (void) eq_func;
    return NULL;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the list structure to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *                  data that's being used in this list, allocating space for
  *                  every part of that data on the heap. This is some function
  *                  you must write yourself for testing, tailored specifically
  *                  to whatever context you're using the list for in your test
  * @return The list structure created by copying the old one, or NULL if the
  *         structure passed in is NULL.
  */
list* copy_list(list *llist, list_copy copy_func)
{
    /// @todo implement
    (void)llist;
    (void) copy_func;
    return NULL;
}

/** size
  *
  * Gets the size of the list
  *
  * @param llist a pointer to the list structure
  * @return The size of the list
  */
int size(list *llist)
{
    ///@note simply return the size of the list. It's that easy!
    (void)llist;
    return 0;
}

/** split_list
  *
  * Splits a list into two lists based on a predicate function.
  * If the predicate function returns true then that element should
  * be removed from original list and be in a new list returned
  * by this function. If the predicate function doesn't return true
  * for any elements then the function should return an empty list.
  *
  * @param llist a pointer to the list structure
  * @param pred_func a pointer to a function that when it returns true, it
  *                  should remove the element from the original list and
  *                  add it to the returned list.
  * @return a new list consiting of only the elements in the original list
  *                 that the pred_func returned a true value for.
  */
list *split_list(list *llist, list_pred pred_func)
{
    /// @todo create a new list to return
    /// @todo use pred_func on the data to determine which elements to remove
    /// @todo remove elements from the current list
    /// @todo add the removed elements to the new list
    (void) llist;
    (void) pred_func;
    return NULL;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list structure
  * @return 1 if the list is indeed empty, or 0 otherwise.
  */
int is_empty(list *llist)
{
    /// @note an empty list should have a size of zero and head points to NULL.
    (void) llist;
    return 0;
}

/** empty_list
  *
  * Empties the list. After this is called, the list should be empty.
  * This does not free the list struct itself, just all nodes and data within.
  *
  * @param llist a pointer to the list structure
  * @param free_func function used to free the nodes' data.
  */
void empty_list(list *llist, list_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes, not the list structure itself.
    /// @note do not free the list structure itself.
    (void) llist;
    (void) free_func;
}

/** traverse
  *
  * Traverses the list, calling a function on each node's data.
  *
  * @param llist a pointer to the list structure
  * @param do_func a function that does something to each node's data.
  */
void traverse(list *llist, list_op do_func)
{
    /// @todo Implement
    (void) llist;
    (void) do_func;
}
