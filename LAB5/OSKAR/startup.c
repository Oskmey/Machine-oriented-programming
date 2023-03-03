/*
 * 	startup.c
 *
 */
#include "Displaydriver.h"
#include "KeyboardDriver.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "Objects.h"
#include "Delay.h"


__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

volatile char Port_Keyboard1;
volatile char Port_Keyboard2;


char set_port_HL(char port[]){
	if(port == "D_LOW"){
		return 0;
	}
	if(port == "D_HIGH"){
		return 1;
	}
}
void app_init(void){
	Port_Keyboard1 = set_port_HL("D_LOW");
	Port_Keyboard2 = set_port_HL("D_HIGH");
}

void main(void){
	app_init();
	}