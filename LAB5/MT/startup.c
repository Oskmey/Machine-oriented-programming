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

POBJECT p = &paddl1;
POBJECT q = &paddle2;
POBJECT b = &ball;


typedef struct{
	char left_score;
	char right_score;

}SCORE;

typedef struct{
	char x;
	char y;
}KB_DIR;


SCORE score = {0, 0};
int DELAY_COUNT = DELAY_COUNT_DEFAULT;

draw_objects(){
	draw_object(p);
	draw_object(q);
	draw_object(b);
}

KB_DIR* translate_KB(char input)
{
	KB_DIR output;
	switch(input)
	{
		case 1:
		output = {0, -3};
		break;
		
		case 9:
		output = {0, 3};
		break;
		
		case 5:
		//Reset?
		break;
		
		default: 
		output = {0, 0};
		break;
	}
	
	return &output;
}

void update_paddle_speed(void)
{
	KB_DIR* dir = translate_KB(keyb(0));
	p->set_object_speed(p, KB_DIR->x, KB_DIR->y);
	KB_DIR* dir = translate_KB(keyb(1));
	q->set_object_speed(q, KB_DIR->x, KB_DIR->y);
}


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
		draw_objects();
		int sys_val = systick.VAL;//Tar hur länge det tog att rita
		sys_val &= -(255<<24);//Blankar ut de högsta värdena just in case
		setup_ms_delay();
		systick.VAL += sys_val;//För alltså over delayen från hur lange det var att rita till nästa omgång for that smooth 60 FPS experience
	}
}


void init_GPIO(void){
	PORT_D.MODER = 0x55005500; //Gör D 8-15 till en inport och 0-7 till utport;
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
	update_paddle_speed();
	graphic_initalize();
	graphic_clear_screen();
	init_app();
	while(1){
		
		p -> move(p);
		q -> move(q);
	}
};