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
__asm__ volatile(".L1: B .L1\n");	
#define PORT_E 0x40021000
#define SYSTICK 0xE000E010

#define GPIO_E_MODER ((volatile unsigned int *)(PORT_E))
#define GPIO_E_ODRLOW ((volatile unsigned char *)(PORT_E + 0x14))
#define GPIO_E_ODRHIGH ((volatile unsigned char *)(PORT_E + 0x15))
#define SBC_VTOR (volatile unsigned int*) 0xE000ED08	
#define STK_CTRL (volatile unsigned int *) 0xE000E010
#define STK_LOAD (volatile unsigned int *) 0xE000E014
#define STK_VAL (volatile unsigned int *)0xE000E018

#ifdef SIMULATOR 
#define DELAY_COUNT 100
#else 
#define DELAY_COUNT 10000
#endif
}


void app_init(void){
*GPIO_E_MODER = 0x5555555;
*SBC_VTOR = 0x2001C000;
setup_systick();

}



static volatile int delay_count;
static volatile int systick_flag;

void systick_irq_handler(void){
	*STK_CTRL = 0;
	int c = delay_count;
	delay_count = delay_count - 1;
	if (delay_count > 0){
		delay_1mikro();
	}
	else systick_flag = 1;
	
}

void setup_systick(void){
	*((void(**)(void)) 0x2001C03C) = systick_irq_handler;
	systick_flag = 0; 
	
}


void delay (unsigned int count){
	if( count == 0 ) return;
	delay_count = count;
	delay_1mikro();
	systick_flag = 0;
}

void delay_1mikro(){
	*STK_CTRL = 0;
	*STK_LOAD = ( 168 - 1 );
	*STK_VAL = 0;
	*STK_CTRL = 7;
}


void main(void)
{
	unsigned char dio_ramp_value = 0;
	app_init();
	*GPIO_E_ODRLOW = 0;
	delay(DELAY_COUNT);
	*GPIO_E_ODRLOW = 0xFF;
	while(1){
		if(systick_flag){
			break;
		}
		if(dio_ramp_value < 255){
			*GPIO_E_ODRHIGH = dio_ramp_value;
			dio_ramp_value ++;
		}
		else(dio_ramp_value = 0);
	
	}
	
	*GPIO_E_ODRLOW = 0;
	
}

