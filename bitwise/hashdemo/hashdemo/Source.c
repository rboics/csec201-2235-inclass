#include <stdio.h>
#include "hash.h"
#include <string.h>

int main(void) {
	char str1[50];
	struct hash* strHash;
	
	while(1){
		printf("Enter a string to hash: ");
		scanf("%s", str1);
		strHash = classHash(str1, strlen(str1));
		printHash(strHash);
	}

}