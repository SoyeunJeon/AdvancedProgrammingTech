/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

List *initList() {
	List * list = malloc(sizeof(*list));
	if (list != NULL) {
		list->head = NULL;
		list->size=0;
	}
	return list;
}

Boolean addToList(List * list, Stock * data) 
{
	Node * previousNode, * currentNode;

    Node * newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        return FALSE;
    }

    newNode->data = malloc(sizeof(*newNode->data));
    if (newNode->data == NULL) {
    	free(newNode);
    	return FALSE;
    }

    *newNode->data = *data;
    newNode->next = NULL;

    previousNode = NULL;
    currentNode = list->head;
    while (currentNode != NULL) {
    	if (strcmp(data->name, currentNode->data->name)<0) {
    		break;
    	}
    	previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (list->head == NULL) {
    	list->head = newNode;
    } else if (previousNode == NULL) {
    	newNode->next = list->head;
    	list->head = newNode;
    } else {
    	previousNode->next = newNode;
    	newNode->next = currentNode;
    }
    list->size++;

    return TRUE;
}

Boolean removeFromList(List * list, char * id) {
	Node * previousNode, * currentNode;
	previousNode = NULL;
	currentNode = list->head;
	while(currentNode != NULL) {
		if (strcmp(id, currentNode->data->id)==0) {
			break;
		}
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	if (currentNode== NULL) {
		return FALSE;
	}
	else if (previousNode == NULL) {
		list->head = currentNode->next;
	} else {
		previousNode->next = currentNode->next;
	} 
	list->size--;

	free(currentNode->data);
	free(currentNode);

	return TRUE;
}

List * freeList(List * list) {
	Node * node = list->head;
	while (node != NULL) {
		Node * temp = node;
		node = node->next;

		free(temp->data);
		free(temp);
	}

	free(list);

	return NULL;
}

int calculateLongestName(VmSystem * system) {
	int temp = 0;
	char *tempName;
	Node * node = system->itemList->head;

	/* find the stock that has longest name */
	while (node != NULL) {
		tempName = node->data->name;
		if (strlen(tempName) > temp) {
			temp = strlen(tempName);
		}
		node = node->next;
	}
	return temp;
}

int generateId (VmSystem * system) {
	Node * node = system->itemList->head;
	int id = system->itemList->size;
	char newId[ID_LEN];
	int increaseId = 1;
	/* temp of new id is size + 1 */
	sprintf(newId, "I%04u", system -> itemList -> size + increaseId);
	/* if new generated id is already exist, increment the id + 1 and search again */
	while (node != NULL) {
		if (strcmp(newId, node->data->id)==0) {
			increaseId++;
			sprintf(newId, "I%04u", system -> itemList -> size + increaseId);
			node = system->itemList->head;
			continue;
		}
		node = node->next;
	}
	return id+increaseId;
}
