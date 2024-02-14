#include <stdio.h>

int main(void) {
	int val = 8;
	unsigned char val2 = (unsigned char)250;
	unsigned char val3 = (unsigned char)13;
	unsigned char val4 = (unsigned char)27;

	printf("val: %hhu\n", val2);
	printf("Left shift 2: %hhu\n", val2 << 2);
	printf("Right shift 2: %hhu\n", val2 >> 2);

	// bitwise 'and' is &
    
	printf("%hhu & %hhu = %hhu\n", val3, val4, val3 & val4);

	// bitwise 'or' is |

	printf("%hhu | %hhu = %hhu\n", val3, val4, val3 | val4);

	// bitwise 'xor' is ^

	printf("%hhu ^ %hhu = %hhu\n", val3, val4, val3 ^ val4);

	return 0;
}