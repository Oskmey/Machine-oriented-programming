#pragma once

typedef struct PORT{
	unsigned char* IN;
	unsigned char* OUT;
}KB_PORT;

int kbdGetCol(KB_PORT* port);
void kdbActivate(unsigned int row, KB_PORT* port);
char keyb(char target);