/*
 * 	startup.c
 *
 */
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */

//Macro för port D (vi skriver PORT_D då vi använder adressen)
#define PORT_D 0x40020C00

//Gör en macro för pekarn som pekar på värdet i registerna
#define GPIO_MODER ((volatile unsigned int *)PORT_D)

//Mikrokontrollerns GPIO_PUPDR register 
#define GPIO_PUPDR ((volatile unsigned int *)PORT_D + 0x0C)

//Mikrokontrollerns speed GPIO_OSPEEDR register 
#define GPIO_OSPEEDR ((volatile unsigned int *)PORT_D +0x08)

//Mikrokontrollerns input register GPIO_ODR denna är kolomnen för key 
#define GPIO_ODR_HIGH ((volatile unsigned char *)PORT_D +0x15) 

//Mikrokontrollerns input register GPIO_IDR denna är raden för key 
#define GPIO_IDR_HIGH ((volatile unsigned char *)PORT_D +0x11) 

#define GPIO_ODR_LOW ((volatile unsigned char *)PORT_D +0x14) 

#define GPIO_OTYPER ((volatile unsigned short *)(PORT_D + 0x4))
}



void app_init(void){
	/* accessing the values using the pointers */
*((unsigned long *) 0x40023830) = 0x18; // starta klockor port D och E
*GPIO_MODER = 0x55005555; //Gör D 8-15 till en inport och 0-7 till utport  
*GPIO_PUPDR = 0x00AA0000; // sätter 10 (pull-down ger 1 då kretsen är sluten) på varje 8-15 pin floating på 0-7
*GPIO_OSPEEDR = 0x55555555;  // port D medium speed	
*GPIO_ODR_HIGH = 0;
*GPIO_ODR_LOW = 0;
*GPIO_OTYPER = 0x0000000;
}


int kbdGetCol(void){
	unsigned char c; 
	c = *GPIO_IDR_HIGH; //rad värdet placeras i c 
	if(c & 0x8) return 4;
	if(c & 0x4) return 3;
	if(c & 0x2) return 2;
	if(c & 0x1) return 1;
	return 0; 
		
}



void out7seg(unsigned char key){
	unsigned segtable[] = {0x06,0x5B,0x4F,0xF7,0x66,0x6D,0x7D,0xFF,0x07,0x7F,0x67,0xB9,0x40,0x3F,0xF6,0xBF}; //s.196 i facit
	if(key <= 0xF){
		*GPIO_ODR_LOW = segtable[key];
		return;
	}
	*GPIO_ODR_LOW = 0;
	return;
}


// Hjälp rution för att sätta output registret till den kolumn vi tittar på. Om ett värde ges i GPIO_IDR så vet vi vilken rad och kolumn.
void kdbActivate(unsigned int row) { //hjälp rutin (MULTIPLEX SAKER FATTAR EJ)
	switch(row){
		case 1: *GPIO_ODR_HIGH = 0x10; 
			break; 
		case 2: *GPIO_ODR_HIGH = 0x20; 
			break;
		case 3: *GPIO_ODR_HIGH = 0x40; 
			break;
		case 4: *GPIO_ODR_HIGH = 0x80; 
			break;
		default: *GPIO_ODR_HIGH = 0x0;
			break;
	}
}


char keyb(void){
	char keys[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0x39,0xE,0,0xF6,0xD}; 
	int row;
	int col;
	for(row = 1; row <= 4; row++){ //väljer en rad att se på
		kdbActivate(row);			//Ger ström till den raden vi har valt 
		if( col = kbdGetCol()){		
			return (4*(row-1)+(col-1));
		}
		
	}
	kdbActivate(0);
	return 0xFF;
}



void main(void){
	unsigned char c;
	app_init();
	while(1){
		c = keyb();
		out7seg(c);
	}
}

