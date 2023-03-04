#include "KeyboardDriver.h"
#include "GPIO.h"



KB_PORT KB_LOW = {&PORT_D.IDRLOW, &PORT_D.ODRLOW};
KB_PORT KB_HIGH = {&PORT_D.IDRHIGH, &PORT_D.ODRHIGH};

int kbdGetCol(KB_PORT* port){
	unsigned char c; 
	c = *(port->IN); //rad värdet placeras i c. Syntax/10 on these pointers. -MT
	if(c & 0x8) return 4;
	if(c & 0x4) return 3;
	if(c & 0x2) return 2;
	if(c & 0x1) return 1;
	return 0; 
}

void kdbActivate(unsigned int row, KB_PORT* port) { //hjälp rutin (MULTIPLEX SAKER FATTAR EJ)
	switch(row){
		case 1: *(port->OUT) = 0x10; 
			break; 
		case 2: *(port->OUT) = 0x20; 
			break;
		case 3: *(port->OUT) = 0x40; 
			break;
		case 4: *(port->OUT) = 0x80; 
			break;
		default: *(port->OUT) = 0x0;
			break;
	}
}

char keyb(char target){
	KB_PORT* target_port;
	if (target)
	{
		target_port = &KB_HIGH;
	}
	else
	{
		target_port = &KB_LOW;
	}
	
	char keys[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0x39,0xE,0,0xF6,0xD}; 
	int row;
	int col;
	for(row = 1; row <= 4; row++){ //väljer en rad att se på
		kdbActivate(row, target_port);			//Ger ström till den raden vi har valt 
		if( col = kbdGetCol(target_port)){		
			return ((4*row-1)+(col-1));
		}
	}
	kdbActivate(0, target_port);
	return 0xFF;
}