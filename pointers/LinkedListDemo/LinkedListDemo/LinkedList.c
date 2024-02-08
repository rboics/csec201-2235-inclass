#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void initialize(struct LinkedList* L) {
	L->head = NULL;
	L->size = 0;
}

void addItem(struct LinkedList* L, int dataToAdd) {
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	newnode->next = L->head;
	newnode->data = dataToAdd;
	L->head = newnode;
	L->size++;
}

void printList(struct LinkedList* L) {
	struct node* temp = L->head;
	while (temp != NULL) {
		printf("%d\n", temp->data);
		temp = temp->next;
	}
}

void deleteItem(struct LinkedList* L, int dataToDelete) {
	if (L->head->data == dataToDelete) {
		struct node* temp = L->head;
		L->head = temp->next;
		L->size--;
		free(temp);
	}
	else {
		struct node* temp = L->head;
		while (temp->next != NULL) {
			if (temp->next->data == dataToDelete) {
				struct node* nodeToDelete = temp->next;
				//temp->next = temp->next->next;
				temp->next = nodeToDelete->next;
				free(nodeToDelete);
				L->size--;
				return;
			}
			temp = temp->next;
		}
	}

}

int searchList(struct LinkedList* L, int data) {
	struct node* temp = L->head;
	while (temp != NULL) {
		if (temp->data == data) return 1;
		temp = temp->next;
	}
	return 0;
}

//Change all instances of oldData to newData
void update(struct LinkedList* L, int oldData, int newData) {
	struct node* temp = L->head;
	while (temp != NULL) {
		if (temp->data == oldData) temp->data=newData;
		temp = temp->next;
	}
}

//Insert a new node containing newData
//between the first nodes containing previousData and nextData
void insert(struct LinkedList* L, int previousData, int nextData, int newData) {
	if (L->size < 2) return;
	
	struct node* temp = L->head;
	while (temp->next != NULL) {
		if (temp->data == previousData && temp->next->data == nextData) {
			struct node* newNode = (struct node*)malloc(sizeof(struct node));
			newNode->next = temp->next;
			temp->next = newNode;
			newNode->data = newData;
			L->size++;
			return;
		}
		temp = temp->next;
	}
	
}

