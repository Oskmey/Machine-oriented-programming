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
}

#define GPIO_MODER ((volatile unsigned int *)(0x40021000))
#define GPIO_ODRLOW ((volatile unsigned char *)(0x40021014))
#define GPIO_ODRHIGH ((volatile unsigned char *)(0x40021015))

/* GPIO interface */
#define PORT_E (*((volatile GPIO*) 0x40021000)) // PORT_E address becomes an GPIO pointer 
typedef volatile struct{     
	unsigned int MODER;         //In-out
	unsigned short OTYPER;	   //Push-open
	unsigned int :0;   //next address 
	unsigned int OSPEEDR;	   
	unsigned int PUPDR;
	union {				//Address of the input registers 
		unsigned short IDR;		//All of IDR
		struct{
			unsigned char IDRLOW;
			unsigned char IDRHIGH;
			unsigned short reserved; 
		};
	};
	union {				//Address of the output registers 
		unsigned short ODR;		//All of ODR
		struct{
			unsigned char ODRLOW;	
			unsigned char ODRHIGH;
			unsigned short reserved2;
		};
	};
	unsigned int BSRR;
	unsigned int LCKR :17; //only uses 17 bits 
	unsigned int :0;		
	unsigned int AFRL;
	unsigned int AFRH;
	
}GPIO;

void main(void)
{
	PORT_E.MODER = 0x55555555;
	PORT_E.ODRLOW = 0x00;
	PORT_E.ODRLOW = 0xFF;
	PORT_E.ODRHIGH = 0xFF;
	
}

