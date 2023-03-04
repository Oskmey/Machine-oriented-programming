
#include "Delay.h"
#include "SYSTICK.h"

void delay_250ns( void ){
	systick.CTRL = 7;
	systick.LOAD = ( (168/4) -1 );
	systick.VAL = 0;
	systick.CTRL = 5;
	while( (systick.CTRL & 0x10000 )== 0 );
	systick.CTRL = 0;
}

void delay_milli(unsigned int ms)
{
	while(ms>0){
		int i = 50;
		while(i>0){
			delay_250ns();
			i = i-1;
		}
	ms--;
	}
}

void delay_micro(unsigned int us){
	while( us > 0 ){
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay_250ns();
		us--;
	}
}

void setup_ms_delay(void)
{
	systick.CTRL &= ~7;//Gör det såhär om vi ska använda andra bits
	systick.LOAD = 16800 - 1;
	systick.VAL = 0;
	systick.CTRL |= 7;
}