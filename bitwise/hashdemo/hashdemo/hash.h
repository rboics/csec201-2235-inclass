#pragma once

//Our hashes are going to be three bytes long
struct hash {
	unsigned char a;
	unsigned char b;
	unsigned char c;
};

void printHash(struct hash * h);

struct hash* classHash(char data[], int len);
