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

#define GPIO_OTYPER ((volatile unsigned short *)(PORT_D + 0x4))

#define clockBASE 0xE000E010
 #define clockCTRL (volatile unsigned int*) (clockBASE)
 #define clockLOAD (volatile unsigned int*) (clockBASE + 4)
 #define clockVAL (volatile unsigned int*) (clockBASE + 8)

  #define PORT_E 0x40021000
#define MAX_POINTS 30

__attribute__((naked))
void graphic_initialize(void)
{
    __asm volatile (" .HWORD 0xDFF0\n");
    __asm volatile (" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_set(int x, int y)
{
    __asm volatile (" .HWORD 0xDFF2\n");
    __asm volatile (" BX LR\n");
}

__attribute__((naked))
void graphic_clear_screen(void)
{
    __asm volatile (" .HWORD 0xDFF1\n");
    __asm volatile (" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_clear(int x, int y)
{
    __asm volatile (".HWORD 0xDFF3\n");
    __asm volatile ("BX LR\n");
}




void kb_init(void){
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



void out7seg(unsigned char key){
	unsigned segtable[] = {0x06,0x5B,0x4F,0xF7,0x66,0x6D,0x7D,0xFF,0x07,0x7F,0x67,0xB9,0x40,0x3F,0xF6,0xBF}; //s.196 i facit
	if(key <= 0xF){
		*GPIO_ODR_LOW = segtable[key];
		return;
	}
	*GPIO_ODR_LOW = 0;
	return;
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
			return (4*(row-1)+(col-1));
		}
		
	}
	kdbActivate(0);
	return 0xFF;
}





int abs(int in)
{
	if (in < 0 )
	{
		in *= -1;
	}

	return in;
}

void delay_250ns()
{
	*clockCTRL = 0;
	*clockLOAD = ( (168/4) -1 );
	*clockVAL = 0;
	*clockCTRL = 5;
	while( (*clockCTRL & 0x10000 )== 0 );
	*clockCTRL = 0;
}

void delay_mikro(int time)
{
	int micro_second = 168;
	*clockCTRL = 0;
	*clockLOAD = ( (micro_second * time) -1 );
	*clockVAL = 0;
	*clockCTRL = 5;
	while( (*clockCTRL & 0x10000 )== 0 );
	*clockCTRL = 0;
}

void delay_mili(int time)
{
	int mili_second = 168 * 1000;
	#ifdef SIMULATOR
	mili_second = mili_second/ 10;
	mili_second++;
	#endif
	*clockCTRL = 0;
	*clockLOAD = ( (mili_second * time) -1 );
	*clockVAL = 0;
	*clockCTRL = 5;
	while( (*clockCTRL & 0x10000 )== 0 );
	*clockCTRL = 0;
} 
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

typedef struct{
	char x,y;
} POINT, *PPOINT;

typedef struct{
	POINT p0;
	POINT p1;
} LINE, *PLINE;

typedef struct{
	POINT start;
	POINT size;
} RECT, *PRECT;

typedef struct polygonPoint{
	char x,y;
	struct polygonPoint *next;
}POLYPOINT, *PPOLYPOINT;

typedef struct{
	char numPoints;
	char sizeX, sizeY;
	POINT px[ MAX_POINTS ];
} GEOMETRY, *PGEOMETRY;

typedef struct tObj{
	PGEOMETRY geo;
	int dirX, dirY;
	int posX, posY;
	void (* draw) (struct tObj *);
	void (* clear) (struct tObj *);
	void (* move) (struct tObj *);
	void (* set_speed) (struct tObj *, int, int);
} OBJECT, *POBJECT;

void draw_line_coords(int x0, int y0, int x1, int y1)
{
	int steep;
	if (abs(y1-y0) >abs(x1-x0))
	{
		steep = 1;
	}
	else
	{
		steep = 0;
	}

	if (steep)
	{
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}

	int deltax = (x1-x0);
	int delaty = abs(y1- y0);

	int error = 0;

	int y = y0;

	int ystep;

	if (y0<y1)
	{
		ystep = 1;
	}
	else
	{
		ystep = -1;
	}

	for (int x = x0; x <= x1; x++)
	{
		if (steep)
		{
			graphic_pixel_set(y, x);
		}
		else 
		{
			graphic_pixel_set(x, y);
		}

		error += delaty;

		if ((2 * error) >= deltax)
		{
			y+=ystep;
			error -= deltax;
		}
	}
} 

void draw_line(LINE* line)
{
	int x0 = line->p0.x;
	int y0 = line->p0.y;
	int x1 = line->p1.x;
	int y1 = line->p1.y;
	draw_line_coords(x0, y0, x1, y1);
}

void draw_polygon(POLYPOINT* ppoint)
{
	POINT p0 = {ppoint->x, ppoint->y};
	POLYPOINT* ptr = ppoint->next;

	while(ptr != 0)
	{
		POINT p1 = {ptr->x, ptr->y};
		LINE line = {p0, p1};
		draw_line(&line);
		p0 = p1;
		ptr = ptr->next;
	}
}

void draw_ball(OBJECT* obj)
{
	GEOMETRY geo = *obj->geo;
	POINT pos = {obj->posX, obj->posY};

	for (int i = 0; i < (sizeof(geo.px) / sizeof(POINT)); i++)
	{
		POINT point = geo.px[i];
		graphic_pixel_set(pos.x + point.x, pos.y + point.y);
	}

}

void clear_ball(OBJECT* obj)
{
	GEOMETRY geo = *obj->geo;
	POINT pos = {obj->posX, obj->posY};

	for (int i = 0; i < (sizeof(geo.px) / sizeof(POINT)); i++)
	{
		POINT point = geo.px[i];
		graphic_pixel_clear(pos.x + point.x, pos.y + point.y);
	}

}

void move_ball(OBJECT* obj)
{
	obj->clear(obj);

	
	obj->posX += obj->dirX;
	obj->posY += obj->dirY;

	if ((obj->posX < 1))
	{
		obj->dirX *= -1;
	}

	if ((obj->posY < 1) || (obj->posY > (64 - obj->geo->sizeY)))
	{
		obj->dirY *= -1;
	}
	obj->draw(obj);
}

void move_paddle(OBJECT* obj)
{
	obj->clear(obj);

	
	obj->posX += obj->dirX;
	obj->posY += obj->dirY;

	if ((obj->posX < 1) || (obj->posX > (128 - obj->geo->sizeX)))
	{
		obj->dirX *= -1;
	}
	
	if ((obj->posY > (64 - obj->geo->sizeY)))
	{
		obj->posY = (64 - obj->geo->sizeY);
	}

	if ((obj->posY < 1))
	{
		obj->posY = 1;
	}
	obj->draw(obj);
}

void set_ball_speed(OBJECT* obj, int x, int y)
{
	obj->dirX = x;
	obj->dirY = y;
}

int pixel_overlap(POBJECT o1, POBJECT o2) {
  int offset1x = o1->posX;
  int offset1y = o1->posY;
  int offset2x = o2->posX;
  int offset2y = o2->posY;
  for (int i = 0; i < o1->geo->numPoints; i++) {
    for (int j = 0; j < o2-> geo->numPoints; j++)
      if ((offset1x + o1->geo->px[i].x == offset2x + o2->geo->px[j].x) &&
        (offset1y + o1->geo->px[i].y == offset2y + o2->geo->px[j].y)) return 1;
  }
  return 0;
}


void main(void)
{
    
    graphic_initialize();
    graphic_clear_screen();
	kb_init();
    
	char c;
	GEOMETRY ball_geometry = {12, 4, 4,
	{{0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {1,3},
	{2,0}, {2,1}, {2,2}, {2,3}, {3,1}, {3,2}
	}
	};
	
	GEOMETRY paddle_geometry = {27, 5, 9,
	{{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},
	{1,0}, {1,8},
	{2,0}, {2,8}, {2,3}, {2,4}, {2,5}, 
	{3,0}, {3,8},
	{4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},{4,8}
	}
	};
	
	OBJECT ball = {&ball_geometry, 1, 1, 64, 32, &draw_ball, &clear_ball,
	&move_ball, &set_ball_speed};
	
	OBJECT paddle = {&paddle_geometry, 0, 0, 110, 32, &draw_ball, &clear_ball,
	&move_paddle, &set_ball_speed};
	
	while(1)
	{
		ball.move(&ball);
		paddle.move(&paddle);
		if (pixel_overlap(&ball, &paddle))
		{
			ball.dirX *= -1;	
		}
		
		delay_mili(1);
		c = keyb();
		
		switch(c)
		{
				case 1:
				paddle.set_speed(&paddle, 0, -3);
				break;
				
				case 9:
				paddle.set_speed(&paddle, 0, 3);
				break;
				
				case 5:
				graphic_clear_screen();
				ball.posX = 64;
				ball.posY = 32;
				paddle.posX = 110;
				paddle.posY = 32;
				break;
				
				default: 
				paddle.set_speed(&paddle, 0, 0);
				break;
		}
		
	}


	//draw_line_coords(1, 1,50, 50);

	return 0;
}