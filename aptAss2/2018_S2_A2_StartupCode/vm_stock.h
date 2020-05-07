/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

/*initialise the list*/
List *initList();

/*create linked list*/
Boolean addToList(List * list, Stock * data);

/*remove a node in linked list*/
Boolean removeFromList(List * list, char * id);

/*free the list*/
List * freeList(List * list);

/* find the longest name item */
int calculateLongestName(VmSystem * system);

/* generate new id for new stock */
int generateId (VmSystem * system);

#endif
