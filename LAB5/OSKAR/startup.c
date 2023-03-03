/*
 * 	startup.c
 *
 */
#include "Displaydriver.h".
#include "GPIO.h"
#include "SYSTICK.h"
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

#define PORT_E (*((volatile GPIO*) 0x40021000)) // PORT_E address becomes an GPIO pointer 
#define PORT_D (*((volatile GPIO*) 0x40020C00))



void main(void)
{
	PORT_E.MODER = 0x55555555;
	PORT_E.ODRLOW =0xFF;
};

