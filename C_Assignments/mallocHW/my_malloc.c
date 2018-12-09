/*
 * CS 2110 Fall 2016
 * Author: Ashwini Iyer
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this for my_sbrk */
#include "my_sbrk.h"
/* we need this for the metadata_t struct definition */
#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you may receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG 
#define DEBUG_PRINT(x) printf(x)
#else
#define DEBUG_PRINT(x)
#endif

/* Our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist;

void* my_malloc(size_t size) {
	//metadata + size + canary, this is the size the user needs
	int sizeRequest = sizeof(metadata_t) + size + sizeof(int);
	//if this size is is too big set ERRNO
	if (sizeRequest > SBRK_SIZE) {
		ERRNO = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	}
	//iterate through free list and see if there is an appropriate block
	//boolean to mark if free block was found, currently false
	int blockFound = 0;
	//start at beginning of freelist, so this is the current free block
	metadata_t* currentBlock = freelist;
	//to be found, the available free block
	metadata_t* availableBlock = NULL;
	//freelist is a linked list -> iterate through the list, find the smallest largest
	while(currentBlock != NULL && freelist != NULL) {
		if (currentBlock->block_size >= sizeRequest) {
			//keep track of if it was found
			if (blockFound == 0) {
				//need to initialize, this is the first usable block
				availableBlock = currentBlock;
				blockFound = 1; //found is now true, there may still be smaller ones so keep looking
			} else {
				//not the first time around, need to check if this block is smaller, replace if smaller.
				if (availableBlock->block_size > currentBlock->block_size) {
					availableBlock = currentBlock;
				}
			}
		}
		currentBlock = currentBlock->next;
	}
	//if we did not find an appropriate free block
	if (blockFound == 0) {
		availableBlock = my_sbrk(SBRK_SIZE);
		//used these when traversing
		metadata_t* currentBlock2 = freelist;
		metadata_t* currentBlock2Prev = NULL;
		//if my_sbrk is a failure, set error code -> return null
		if (availableBlock == NULL) {
			ERRNO = OUT_OF_MEMORY;
			return NULL;
		}
		//update aspects of availableBlock
		availableBlock->next = NULL;
		availableBlock->block_size = SBRK_SIZE;
		availableBlock->request_size = 0;
		availableBlock->canary = 0;
		if (freelist == NULL) {
			//initialize freelist
			freelist = availableBlock;
		} else {
			int returnNeeded = 0;
			while (currentBlock2 != NULL && returnNeeded == 0) {
				if ((uintptr_t)currentBlock2 < (uintptr_t)availableBlock) {
					currentBlock2Prev = currentBlock2;
					currentBlock2 = currentBlock2->next;
				} else {
					if (currentBlock2Prev == NULL) {
						availableBlock->next = currentBlock2;
						currentBlock2Prev = availableBlock;
						freelist = availableBlock;
					} else {
						availableBlock->next = currentBlock2Prev->next;
						currentBlock2Prev->next = availableBlock;
					}
					currentBlock2 = currentBlock2->next;
					returnNeeded = 1; 
				}
			}
			if (returnNeeded == 0){
				currentBlock2Prev->next = availableBlock;
				returnNeeded = 1;
			}
		}
		currentBlock2 = availableBlock;
	}
	currentBlock = availableBlock;

	//cant be split if it leaves too little behind, check if it can be split
	int canLeave = sizeof(metadata_t)+sizeof(int)+1;
	if (availableBlock->block_size - sizeRequest >= canLeave) {
		//can split
		currentBlock->block_size = currentBlock->block_size - sizeRequest;
		availableBlock = (metadata_t*) ((char*)currentBlock + currentBlock->block_size);
		availableBlock->block_size = sizeRequest;
	} else {
		//remove whole block, it cannot be split
		metadata_t* prevAvail = freelist;
		if (currentBlock == freelist) {
			freelist = freelist->next;
		}
		else{
			while(prevAvail->next != currentBlock) {
				prevAvail = prevAvail->next;
			}
			if (prevAvail != NULL) {
				prevAvail->next = currentBlock->next;
			}
		}
	}
	//prepare availableBlock
	availableBlock->request_size=size;
	availableBlock->block_size=sizeRequest;
	availableBlock->next = NULL;

	//set up canarys -> one in metadata and the other after the block
	int* canaryAfter = (int*) ((char*)(availableBlock) + size + sizeof(metadata_t));
    *canaryAfter = ((((int)availableBlock->block_size) << 16) | ((int)availableBlock->request_size))
            ^ (int)(uintptr_t)availableBlock;
    availableBlock->canary = ((((int)availableBlock->block_size) << 16) | ((int)availableBlock->request_size))
            ^ (int)(uintptr_t)availableBlock;    
	ERRNO = NO_ERROR;
	void* answer = (void*) (((char*) (availableBlock)) + sizeof(metadata_t));
    return answer;
}

void* my_realloc(void* ptr, size_t new_size) {
	/* change the size of the memory block pointed to by ptr to the size of size and return a pointer
	to the beginning of the allocated memory. If ptr is NULL, I my_malloc(size) otherwise 
	I either free ptr or copy over to the new size using memcpy */
	void* newBlock = NULL;
	if (ptr == NULL) {
		newBlock = my_malloc(new_size);
	} else {
		if (new_size == 0 && ptr != NULL) {
			my_free(ptr);
		} else {
			newBlock = my_malloc(new_size);
			memcpy(ptr,newBlock,new_size);
		}
	}
	ERRNO = NO_ERROR;
	return newBlock;
}

void* my_calloc(size_t nmemb, size_t size) {
	/*allocate a region of memory of nmemb num elements of size provided and then zero it out*/
	void* mallocdVal = my_malloc(nmemb*size);
	//if it returns null, return null
	if (mallocdVal == NULL) {
		return NULL;
	}
	//zero out whole block, size that we created -> nmemb*size
	memset(mallocdVal, 0, nmemb*size);
	ERRNO = NO_ERROR;
    return mallocdVal;
}

void my_free(void* ptr) {
	/*Implements deallocation. ptr is the pointer to the block the user was working with, not the metadata, 
	calculate the proper address of the block to be freed, check both canaries, check the one in 
	the metadata first, then merge or add*/

	/*get metadata*/
	metadata_t* metadata = (metadata_t*) ((char*)(ptr) - sizeof(metadata_t));

	/*check canaries, check the metatdata one first*/
	unsigned int correctCanary = ((((int)metadata->block_size) << 16) | ((int)metadata->request_size))
            ^ (int)(uintptr_t)metadata;
    if(metadata->canary != correctCanary) {
    	ERRNO = CANARY_CORRUPTED;
    	return;
    }
    int* canaryAfter = (int*) ((char*)(ptr) + (metadata->request_size));
    if (*canaryAfter != correctCanary) {
    	ERRNO = CANARY_CORRUPTED;
    	return;
    }

    /*iterate and check for merges*/
    metadata_t* currentBlock = freelist;
    metadata_t* prevBlock = NULL;
    int blockFound = 0;
    while(currentBlock != NULL) {
    	/*Check if current is free and is to the left and if so merge to the right, and vice versa. 
    	I know its free if its size goes all the way up to my block*/
    	// right side = my block's real size + its address
    	// left side = its address + real size = my block's address
    	if (metadata == ((metadata_t*)((char*)(currentBlock) + currentBlock->block_size))) {
    		currentBlock->block_size = currentBlock->block_size + metadata->block_size;
    		if(metadata == freelist) {
    			freelist = metadata;
    		}
    		metadata = currentBlock;
    		blockFound = 1;
    	}
    	if (currentBlock == (metadata_t*)((char*)(metadata) + metadata->block_size)) {
    		if (currentBlock == freelist) {
    			freelist = metadata;
    		} else {
    			prevBlock->next = metadata;
    		}
    		metadata->request_size = 0;
    		metadata->block_size = metadata->block_size+currentBlock->block_size;
    		metadata->next = currentBlock->next;
    		currentBlock = metadata;
    		blockFound = 1;
    	}
    	prevBlock = currentBlock;
    	currentBlock = currentBlock->next;
    }
    //There is the case where there was no merge, in that case we have to put it at the end.
    if (blockFound == 0) {
    	if (prevBlock == NULL) {
    		freelist = metadata;
    		freelist->next = NULL;
    		freelist->request_size = 0;
    	} else {
    		prevBlock->next = metadata;
    		metadata->next = NULL;
    		metadata->request_size = 0;
    	}
    }
    ERRNO = NO_ERROR;
}