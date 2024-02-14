#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

void printHash(struct hash * h) {
	printf("%hhu %hhu %hhu\n", h->a, h->b, h->c);
}

struct hash* classHash(char data[], int len) {
	struct hash* h = (struct hash*)malloc(sizeof(struct hash));
	h->a = (unsigned char)5;
	h->b = (unsigned char)78;
	h->c = (unsigned char)12;

	unsigned char newA, newB, newC, oldA, oldB, oldC;

	for (int i = 0; i < len; i++) {
		oldA = h->a;
		oldB = h->b;
		oldC = h->c;

		newA = oldC ^ (unsigned char)data[i];
		newB = oldA << 3;
		newC = oldB & oldC;

		h->a = newA;
		h->b = newB;
		h->c = newC;

	}

	return h;
}