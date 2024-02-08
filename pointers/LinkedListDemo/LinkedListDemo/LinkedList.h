#pragma once
#include <stdio.h>  // For system-wide includes
#include "node.h"	// For includes in your project

struct LinkedList {
	int size;
	struct node* head;
};

//Function prototypes for functions in LinkedList.c
void initialize(struct LinkedList* L); //Done
void addItem(struct LinkedList* L, int dataToAdd); //Done
void printList(struct LinkedList* L); //Done
void deleteItem(struct LinkedList* L, int dataToDelete); //Done
int searchList(struct LinkedList * L, int data);
void updateData(struct LinkedList* L, int oldData, int newData);
void insert(struct LinkedList* L, int previousData, int nextData, int newData);