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
	int x,y;
} POINT, *PPOINT;

typedef struct{
	POINT p0;
	POINT p1;
} LINE, *PLINE;

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




int main(void)
{
    int i;
    graphic_initialize();
    for (i = 1; i <= 128; i++)
    {
        graphic_pixel_set(i, 10);
    }
    for (i = 0; i <= 64; i++)
    {
        graphic_pixel_set(10, i);
    }
    delay_mili(500);
    
    for (i = 1; i <= 128; i++)
    {
        graphic_pixel_clear(i, 10);
    }
    for (i = 0; i <= 64; i++)
    {
        graphic_pixel_clear(10, i);
    }

	LINE lines[] = {
		{40, 10, 100, 10},
		{40, 10, 100, 20},
		{40, 10, 100, 30},
		{40, 10, 100, 40},
		{40, 10, 100, 50},
		{40, 10, 100, 60},
		{40, 10, 90, 60},
		{40, 10, 80, 60},
		{40, 10, 70, 60},
		{40, 10, 60, 60},
		{40, 10, 50, 60},
		{40, 10, 40, 60}


	};

	while (1)
	{
		for (int i = 0; i < (sizeof(lines)/ sizeof(LINE)); i++)
		{
			draw_line(&lines[i]);
			delay_mili(500);
		}
		graphic_clear_screen();
	}

	//draw_line_coords(1, 1,50, 50);

	return 0;
}