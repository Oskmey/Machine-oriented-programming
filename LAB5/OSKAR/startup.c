/*
 * 	startup.c
 *
 */
#include "Displaydriver.h"
#include "KeyboardDriver.h"
#include "Delay.h"
#include "Render.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include "SCB.h"


__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

#define FPS 60
#define DELAY_COUNT_DEFAULT (1/FPS)*1000000
#define MICRO_SEC 168

typedef struct{
	char left_score;
	char right_score;

}SCORE;


SCORE score = {0, 0};
int DELAY_COUNT = DELAY_COUNT_DEFAULT;


void render_frame(void)
{
	systick.CTRL &= -(7);
	systick.VAL = 0;
	
	if (DELAY_COUNT){
		DELAY_COUNT--;
		setup_ms_delay();
	}
	else{
		systick.CTRL |= 5;//Startar klockan för att få hur länge det tar att dra saker, men stänger av interrupt
		//Draw stuff here
		int sys_val = systick.VAL;//Tar hur länge det tog att rita
		sys_val &= -(255<<24);//Blankar ut de högsta värdena just in case
		setup_ms_delay();
		systick.VAL += sys_val;//För alltså over delayen från hur lange det var att rita till nästa omgång for that smooth 60 FPS experience
	}
}


void init_GPIO(void){
	PORT_D.MODER = 0x55005555; //Gör D 8-15 till en inport och 0-7 till utport;
	PORT_D.PUPDR= 0x00AA0000; // sätter 10 (pull-down ger 1 då kretsen är sluten) på varje 8-15 pin floating på 0-7
	PORT_D.OSPEEDR = 0x55555555;  // port D medium speed	
	*((unsigned long *) 0x40023830) = 0x18; // starta klockor port D och E
}

void init_SCB(void)
{
	SCB_VTOR = 0x2001C000;//Kan igentligen byta om på adressen, ska nog göra det generiskt imorn.
	SCB_ADRESSES.AFSR = &render_frame;
}



void init_app(void)//Kasta in vad mer behövs för att starta här
{
	
	init_GPIO();
	init_SCB();
}




void main(void)
{
	init_app();
	
};