/// main.c

#include "debug.h"
#include "startup.h"



 #define clockBASE 0xE000E010
 #define clockCTRL (volatile unsigned int*) (clockBASE)
 #define clockLOAD (volatile unsigned int*) (clockBASE + 4)
 #define clockVAL (volatile unsigned int*) (clockBASE + 8)

  #define PORT_E 0x40021000

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





int main(void)
{
    int i;
    graphic_initialize();
    graphic_clear_screen();
    

	POLYPOINT pg8 = {20, 20, 0};
	POLYPOINT pg7 = {20, 55, &pg8};
	POLYPOINT pg6 = {70, 60, &pg7};
	POLYPOINT pg5 = {80, 35, &pg6};
	POLYPOINT pg4 = {100, 25, &pg5};
	POLYPOINT pg3 = {90, 10, &pg4};
	POLYPOINT pg2 = {40, 10, &pg3};
	POLYPOINT pg1 = {20, 20, &pg2};

	while(1)
	{
		draw_polygon(&pg1);
		delay_mili(500000);
		graphic_clear_screen();
		
	}


	//draw_line_coords(1, 1,50, 50);

	return 0;
}