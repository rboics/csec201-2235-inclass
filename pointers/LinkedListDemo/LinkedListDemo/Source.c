#include <stdio.h>
#include <stdlib.h> // For memory management functions
#include "LinkedList.h"


int main(void) {
	struct LinkedList L;

	initialize(&L);
	addItem(&L, 10);
	addItem(&L, 20);
	addItem(&L, 30);
	printList(&L);
	deleteItem(&L, 30);
	printList(&L);

}