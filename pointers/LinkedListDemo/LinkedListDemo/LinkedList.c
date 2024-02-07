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

int size(struct LinkedList L) {

}




