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
#define STK_CTRL ((volatile unsigned int *)(0xE000E010))  
#define STK_LOAD ((volatile unsigned int *)(0xE000E014))  
#define STK_VAL ((volatile unsigned int *)(0xE000E018))
//Macro för port D (vi skriver PORT_D då vi använder adressen)
#define PORT_D 0x40020C00

//Gör en macro för pekarn som pekar på värdet i registerna
#define GPIO_MODER ((volatile unsigned int *)PORT_D)

//Mikrokontrollerns GPIO_PUPDR register 
#define GPIO_PUPDR ((volatile unsigned int *)PORT_D + 0x0C)

//Mikrokontrollerns speed GPIO_OSPEEDR register 
#define GPIO_OSPEEDR ((volatile unsigned int *)PORT_D +0x08)

//Mikrokontrollerns input register GPIO_ODR denna är kolomnen för key 
#define GPIO_ODR_HIGH ((volatile unsigned char *)PORT_D +0x15) 

//Mikrokontrollerns input register GPIO_IDR denna är raden för key 
#define GPIO_IDR_HIGH ((volatile unsigned char *)PORT_D +0x11) 

#define GPIO_ODR_LOW ((volatile unsigned char *)PORT_D +0x14) 

#define GPIO_OTYPER ((volatile unsigned short *)(PORT_D + 0x4)) 				/* never return */
}

__attribute__((naked))
void graphic_initalize(void){
	__asm volatile (".HWORD	0xDFF0\n");
	__asm volatile ("BX	LR\n");
	
}


__attribute__((naked))
void graphic_pixel_set(int x, int y){
	__asm volatile (".HWORD	0xDFF2\n");
	__asm volatile ("BX	LR\n");
	
}

__attribute__((naked))
void graphic_clear_screen(void){
	__asm volatile (".HWORD	0xDFF1\n");
	__asm volatile ("BX	LR\n");
	
}

__attribute__((naked))
void graphic_pixel_clear(int x, int y){
	__asm volatile (".HWORD	0xDFF3\n");
	__asm volatile ("BX	LR\n");
	
}

/* keyboard____________________________________________________________________________________________________________________________*/

void app_init(void){
	/* accessing the values using the pointers */
*((unsigned long *) 0x40023830) = 0x18; // starta klockor port D och E
*GPIO_MODER = 0x55005555; //Gör D 8-15 till en inport och 0-7 till utport  
*GPIO_PUPDR = 0x00AA0000; // sätter 10 (pull-down ger 1 då kretsen är sluten) på varje 8-15 pin floating på 0-7
*GPIO_OSPEEDR = 0x55555555;  // port D medium speed	
*GPIO_ODR_HIGH = 0;
*GPIO_ODR_LOW = 0;
*GPIO_OTYPER = 0x0000000;
}

int kbdGetCol(void){
	unsigned char c; 
	c = *GPIO_IDR_HIGH; //rad värdet placeras i c 
	if(c & 0x8) return 4;
	if(c & 0x4) return 3;
	if(c & 0x2) return 2;
	if(c & 0x1) return 1;
	return 0; 
		
}




// Hjälp rution för att sätta output registret till den kolumn vi tittar på. Om ett värde ges i GPIO_IDR så vet vi vilken rad och kolumn.
void kdbActivate(unsigned int row) { //hjälp rutin (MULTIPLEX SAKER FATTAR EJ)
	switch(row){
		case 1: *GPIO_ODR_HIGH = 0x10; 
			break; 
		case 2: *GPIO_ODR_HIGH = 0x20; 
			break;
		case 3: *GPIO_ODR_HIGH = 0x40; 
			break;
		case 4: *GPIO_ODR_HIGH = 0x80; 
			break;
		default: *GPIO_ODR_HIGH = 0x0;
			break;
	}
}



char keyb(void){
	char keys[] = {1,2,3,0xA,4,5,6,0xB,7,8,9,0x39,0xE,0,0xF6,0xD}; 
	int row;
	int col;
	for(row = 1; row <= 4; row++){ //väljer en rad att se på
		kdbActivate(row);			//Ger ström till den raden vi har valt 
		if( col = kbdGetCol()){		
			return ((4*row-1)+(col-1));
		}
		
	}
	kdbActivate(0);
	return 0xFF;
}



void delay_250ns( void ){
	*STK_CTRL = 0;
	*STK_LOAD = ( (168/4) -1 );
	*STK_VAL = 0;
	*STK_CTRL = 5;
	while( (*STK_CTRL & 0x10000 )== 0 );
	*STK_CTRL = 0;
}

void delay_mili(unsigned int ms)
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





/*Struct____________________________________________________________________________________________________________________________*/

typedef struct{
	char x,y;
} POINT, *PPOINT;

typedef struct{
	 POINT p0;
	 POINT p1;
}LINE, *PLINE;


#define MAX_POINTS 30
typedef struct{  //Definierar objektet i from av x och y kordinater.
	int numpoints;
	int sizex;
	int sizey;
	POINT px[MAX_POINTS]; //Lista med alla punkter som skapar objektet
}GEOMETRY, *PGEOMETRY;

typedef struct{
	PGEOMETRY geo; // "Bilden"  
	int dirx, diry; // rörelseriktning
	int posx, posy;
	void (* draw)(struct tObj *); //Funktionspekare alltså där vi gör pass by reference 
	void (* clear)(struct tObj *);
	void (* move)(struct tObj *);
	void (* set_speed)(struct tObj *, int,int);
}OBJECT, *POBJECT;

/* Pong_logic____________________________________________________________________________________________________________________________*/


void draw_object(POBJECT o)
{
	PGEOMETRY geo = o->geo;
	POINT *point_list = geo->px;
	int pixels = geo->numpoints;
	int x = o->posx;
	int y = o->posy;
	for(int i = 0; i < pixels; i++){
		POINT pixel = point_list[i];
		int new_x = x + pixel.x;
		int new_y = y + pixel.y;
		graphic_pixel_set(new_x, new_y);
	}
}

void clear_object(POBJECT o)
{
	PGEOMETRY geo = o->geo;
	POINT *point_list = geo->px;
	int pixels = geo->numpoints;
	int x = o->posx;
	int y = o->posy;
	for(int i = 0; i < pixels; i++){
		POINT pixel = point_list[i];
		int new_x = x + pixel.x;
		int new_y = y + pixel.y;
		graphic_pixel_clear(new_x, new_y);
	}
}


void move_paddelobject (POBJECT o){
	int dx = o -> dirx;
	int dy = o -> diry;
	int x = o -> posx;
	int y = o -> posy;
	clear_object(o);
	o -> posx = x + (o->dirx);
	o -> posy = y + (o->diry);
	if(o->posy < 1){
		o->diry = 0;
		o->posy = 1;
	}
	if(o->posy > (64-9)){
		o->diry = 0;
		o->posy = 64-9;
	}
	
	draw_object(o);
}

void set_object_speed(POBJECT o, int speedx, int speedy){
	int c = speedy;
	o->dirx = speedx;
	o->diry = speedy;
}




void move_ballobject (POBJECT o){
	int x = o->posx;
	int y = o->posy;
	clear_object(o);
	o -> posx = x + (o->dirx);
	o -> posy = y + (o->diry);
	int c= 65 - (o -> geo -> sizex);
	if(o->posx < 1){
		o->dirx = (- o->dirx);
	}
	
	if(o->posy < 1){
		o->diry = (- o->diry);
	}
	if(o->posy > 60){
		o->diry = (- o->diry);
	}
	draw_object(o);
}

int pixel_overlap(POBJECT o1, POBJECT o2) {
  int offset1x = o1->posx;
  int offset1y = o1->posy;
  int offset2x = o2->posx;
  int offset2y = o2->posy;
  for (int i = 0; i < o1->geo->numpoints; i++) {
    for (int j = 0; j < o2-> geo->numpoints; j++)
      if ((offset1x + o1->geo->px[i].x == offset2x + o2->geo->px[j].x) &&
        (offset1y + o1->geo->px[i].y == offset2y + o2->geo->px[j].y)) return 1;
  }
  return 0;
}

/* sprites____________________________________________________________________________________________________________________________*/
GEOMETRY paddle_geometry = {
	29,
	4,4,
	{
		{0,0},{1,0},{2,0},{3,0},{4,0},{0,8},{1,8},{2,8},{3,8},{4,8},{2,3},{2,4},{2,5},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},
		{4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7}
	}
};

GEOMETRY ball_geometry = {
	12,
	5,9,
	{
		{0,1},{0,2},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,1},{3,2}
	}
};



/*Objects____________________________________________________________________________________________________________________________*/
OBJECT paddle = {
	&paddle_geometry,
	0,0,
	122,32,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};


OBJECT ball = {
	&ball_geometry,
	4,1,
	10,32,
	draw_object,
	clear_object,
	move_ballobject,
	set_object_speed
};




/*program____________________________________________________________________________________________________________________________*/

void main(void){
	char c;
	POBJECT p = &paddle;
	POBJECT b = &ball;
	app_init();
	graphic_initalize();
	graphic_clear_screen();
	while(1){
		p -> move(p);
		if(pixel_overlap(p, b)){
			b -> dirx = (- b -> dirx);
			b -> diry =	(b -> diry);
		}
		b -> move(b);
		delay_mili(20);
		c = keyb();
		switch(c){
			case 4:		p->set_speed(p, 0, -3); //upp
				break;
			case 12:	p->set_speed(p, 0, 3); //ner
				break;
			case 255:	p->set_speed(p, 0, 0); 	//stanna
				break;
			case 6:		b->posx = 10; b->posy = 32; //reset
				graphic_clear_screen();				
				break;

		}
	}
	
		
}
	



