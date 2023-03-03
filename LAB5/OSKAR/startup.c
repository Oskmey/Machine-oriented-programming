/*
 * 	startup.c
 *
 */
#include "Displaydriver.h"
#include "KeyboardDriver.c"
#include "GPIO.h"
#include "SYSTICK.h"
#include "Objects.h"


__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}




void main(void)
{
	PORT_E.MODER = 0x55555555;
	PORT_E.ODRLOW =0xFF;
};

