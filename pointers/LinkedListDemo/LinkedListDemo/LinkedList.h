#pragma once
#include <stdio.h>  // For system-wide includes
#include "node.h"	// For includes in your project

struct LinkedList {
	int size;
	struct node* head;
};

//Function prototypes for functions in LinkedList.c
void initialize(struct LinkedList* L);
void addItem(struct LinkedList* L, int dataToAdd);
void printList(struct LinkedList* L);
void deleteItem(struct LinkedList* L, int dataToDelete);
int size(struct LinkedList L);