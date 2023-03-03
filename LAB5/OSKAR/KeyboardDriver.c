#include "KeyboardDriver.h"
#include "GPIO.h"



int kbdGetCol(char HIGH){
	unsigned char c;
	if(HIGH) c = PORT_E.IDRHIGH;				
	else c = PORT_E.IDRHIGH;	
	if(c & 0x8) return 4;
	if(c & 0x4) return 3;
	if(c & 0x2) return 2;
	if(c & 0x1) return 1;
	return 0; 
		
	}


void kdbActivate(unsigned int row, char HIGH) { //hjälp rutin (MULTIPLEX SAKER FATTAR EJ)
	if(HIGH){
		switch(row){
		case 1: PORT_E.ODRHIGH = 0x10; 
			break; 
		case 2: PORT_E.ODRHIGH = 0x20; 
			break;
		case 3: PORT_E.ODRHIGH = 0x40; 
			break;
		case 4: PORT_E.ODRHIGH = 0x80; 
			break;
		default: PORT_E.ODRHIGH = 0x0;
			break;
		}
	}
	else {
		switch(row){
		case 1: PORT_E.IDRHIGH = 0x10; 
			break; 
		case 2: PORT_E.IDRHIGH = 0x20; 
			break;
		case 3: PORT_E.IDRHIGH = 0x40; 
			break;
		case 4: PORT_E.IDRHIGH = 0x80; 
			break;
		default: PORT_E.IDRHIGH = 0x0;
			break;
		}

	}
	
}
char keyb(char HIGH){
	char keys[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0x39,0xE,0,0xF6,0xD}; 
	int row;
	int col;
	for(row = 1; row <= 4; row++){ //väljer en rad att se på
		kdbActivate(row, HIGH);			//Ger ström till den raden vi har valt 
		if( col = kbdGetCol(HIGH)){		
			return ((4*row-1)+(col-1));
		}
	}
	kdbActivate(0,HIGH);
	return 0xFF;
}