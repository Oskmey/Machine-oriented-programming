/*
 * 	startup.c
 *
 */
#include "KeyboardDriver.h"
#include "GPIO.h"
#include "GraphicDriver.h"
#include "Geometry.h"
#include "Delay.h"
#include "SYSTICK.h"
#include "AsciiDisplayDriver.h"
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

static volatile char Keyboard1;
static volatile char Keyboard2;

int DELAY_COUNT = 0;

POBJECT p = &paddle1;
POBJECT q = &paddle2;
POBJECT b = &ball; 
POBJECT l = &line;

#define SBC_VTOR (volatile unsigned int*) 0xE000ED08
#define FPS 60
#define DELAY_COUNT_DEFAULT (500/FPS)
#define MICRO_SEC 168


void set_port_keyboards(char POS[]){
	//Set high or low here
	if(POS == "HIGH"){
		Keyboard1 = 1;
		Keyboard2 = 0;
	}
	else{
		Keyboard1 = 0;
		Keyboard2 = 1;
	}
}

char update_paddle(char Keyboard){
	char c = keyb(Keyboard);
}





void move_paddles(void){
		p->move(p);
		q->move(q);
}

void collision_check(void){
	if(pixel_overlap(p,b)){
			b -> dirx = (- b -> dirx);
			b -> diry =	(b -> diry);
		}
	if(pixel_overlap(q,b)){
			b -> dirx = (- b -> dirx);
			b -> diry =	(b -> diry);
		}
	b->move(b);
	
	if(GOAL){
		graphic_clear_screen();
		ascii_text_generator(SCORE1, SCORE2);
		p->posx = 122;
		p->posy = 32;
		q->posx= 2;
		q->posy = 32;
		b->posx = 64;
		b ->posy =32;
		GOAL = 0;
	}
	
}

void render_frame(void){
	systick.CTRL = 0; 
	systick.VAL= 0;
	systick.CTRL |= 5;
	collision_check();
	move_paddles();
	draw_object(l);
	setup_ms_delay();
}


/*void render_frame(void){
	int delay_count = DELAY_COUNT;
	systick.CTRL = 0;
	systick.VAL = 0;
	if (DELAY_COUNT){
		DELAY_COUNT--;
		setup_ms_delay();
	}
	else{
		DELAY_COUNT = DELAY_COUNT_DEFAULT;
		systick.CTRL |= 5;//Startar klockan för att få hur länge det tar att dra saker, men stänger av interrupt
		draw_objects();
		int sys_val = systick.VAL;//Tar hur länge det tog att rita
		sys_val &= -(255<<24);//Blankar ut de högsta värdena just in case
		setup_ms_delay();
		systick.VAL += sys_val;//För alltså over delayen från hur lange det var att rita till nästa omgång for that smooth 60 FPS experience
	}
} */


void translate_key(char c,POBJECT p ){
			switch(c){
			case 4:		p->set_speed(p, 0, -3); //upp
				break;
			case 12:	p->set_speed(p, 0, 3); //ner
				break;
			case 255:	p->set_speed(p, 0, 0); 	//stanna
				break;
			case 6:		b->posx = 10; b->posy = 32; //reset		
				break;

		}
}





void init_keyboard(void){
	PORT_D.MODER = 0x55005500;
	PORT_D.PUPDR = 0x00AA00AA;
	PORT_D.OSPEEDR = 0x55555555;
	PORT_D.OTYPER = 0x0000000;
	PORT_E.MODER = 0x55555555;
	set_port_keyboards("HIGH");
}

void init_app(void){
	init_keyboard();
	*SBC_VTOR = 0x2001C000;
	*((void(**)(void)) 0x2001C03C) = render_frame;
}

void main(void){
	char c;
	char k;	
	graphic_initalize();
	graphic_clear_screen();
	init_app();
	ascii_init();
	ascii_gotoxy(1,1);
	ascii_text_generator(SCORE1,SCORE2);
	setup_ms_delay();
	while(1){
		c = update_paddle(Keyboard1);
		k = update_paddle(Keyboard2);
		translate_key(c,p);
		translate_key(k,q);
	}
}







/*	char *s;
	char test1[] = "TOP TEXT";
	char test2[] = "BOTTOM TEXT :-)";
	ascii_init();
	ascii_gotoxy(1,1);
	s = test1;
	while (*s){
		ascii_write_char (*s++);
		}
	ascii_gotoxy(1,2);
	s = test2;
	
	while (*s){
		ascii_write_char (*s++);
		}
		return 0;*/


/*	while(1){
	char c = keyb(Keyboard1);
	char k = keyb(Keyboard2);
	PORT_E.ODRLOW = k;
	PORT_E.ODRLOW = c;
	 */