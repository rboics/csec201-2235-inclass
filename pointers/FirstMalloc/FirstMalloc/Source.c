#include <stdio.h>
#include <stdlib.h> //Malloc is defined here

int main(void) {
	int x = 5;
	int y = 6;
	int z = 7;
	
	int* a = (int*)malloc(4);
	int* b = (int*)malloc(sizeof(int));
	int* c = (int*)malloc(sizeof(char) * 4);

	printf("Stack\n%p\n%p\n%p\n\n\n", &x, &y, &z);

	printf("????\n%p\n%p\n%p\n\n\n", &a, &b, &c);

	printf("Heap\n%p\n%p\n%p\n", a, b, c);


}