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
//______________________________________________________________________________
#define PORT_E 0x40021000
#define SYSTICK 0xE000E010
//__PORT_E______________________________________________________________________
#define GPIO_MODER ((volatile unsigned int *)(PORT_E))
#define GPIO_ODRLOW ((volatile unsigned char *)(PORT_E + 0x14))
#define GPIO_ODRHIGH ((volatile unsigned char *)(PORT_E + 0x15))
//_____SYS_TICK__________________________________________________________________
#define SBC_VTOR (volatile unsigned int*) 0xE000ED08	
#define STK_CTRL (volatile unsigned int *) 0xE000E010
#define STK_LOAD (volatile unsigned int *) 0xE000E014
#define STK_VAL (volatile unsigned int *)0xE000E018


//_____GLOBAL__________________________________________________________________
static int systick_flag;
volatile int delay_count;



void delay_1mikro(void){
	*STK_CTRL = 0;
	*STK_LOAD = (168 - 1);
	*STK_VAL = 0;
	*STK_CTRL = 7;
}

void irq_systick_handler(void){
	*STK_CTRL = 0;
	delay_count--;
	int c = delay_count; 
	if(delay_count > 0){
		delay_1mikro();
	}
	else{
		systick_flag = 1;
	}
}


void sys_tick_config(void){
	*SBC_VTOR = 0x2001C000;
	*((void(**)(void)) 0x2001C03C) = irq_systick_handler;
	
	systick_flag = 0;
}


void init_app(){
	*((unsigned long *) 0x40023830) = 0x18;
	*GPIO_MODER = 0x5555555;
	sys_tick_config();
	*((unsigned long *)0x40023844) |= 0x4000; 	
	
}
	
void delay(unsigned int count){
	delay_count = count;
	delay_1mikro();
}


#ifdef SIMULATOR
#define DELAY_COUNT 100
#else
#define DELAY_COUNT 10000
#endif 

void main(void)
{
	init_app();
	unsigned char dio_ramp_value = 0;
	*GPIO_ODRLOW = 0;
	delay(DELAY_COUNT);
	*GPIO_ODRLOW = 0xFF;
	while(1){
		if(systick_flag){
			break;
		}
				if(dio_ramp_value < 255){
			*GPIO_ODRHIGH = dio_ramp_value;
			dio_ramp_value ++;
		}
		else(dio_ramp_value = 0);
		
	}
	*GPIO_ODRLOW = 0x0;
}

