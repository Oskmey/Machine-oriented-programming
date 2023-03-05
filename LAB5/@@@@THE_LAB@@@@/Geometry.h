#pragma once




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

void draw_object(POBJECT o);
void clear_object(POBJECT o);
void move_paddelobject (POBJECT o);
void set_object_speed(POBJECT o, int speedx, int speedy);
void move_ballobject (POBJECT o);
int cross_points(POINT point, POINT upper_left, POINT bottom_right);
int pixel_overlap(POBJECT o1, POBJECT o2);



/* sprites____________________________________________________________________________________________________________________________*/
static  GEOMETRY paddle_geometry = {
	29,
	4,4,
	{
		{0,0},{1,0},{2,0},{3,0},{4,0},{0,8},{1,8},{2,8},{3,8},{4,8},{2,3},{2,4},{2,5},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},
		{4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7}
	}
};

static GEOMETRY ball_geometry = {
	12,
	5,9,
	{
		{0,1},{0,2},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,1},{3,2}
	}
};



static OBJECT paddle1 = {
	&paddle_geometry,
	0,0,
	122,32,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};


static OBJECT paddle2 = {
	&paddle_geometry,
	0,0,
	2,32,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};

static OBJECT ball = {
	&ball_geometry,
	4,1,
	10,32,
	draw_object,
	clear_object,
	move_ballobject,
	set_object_speed
};

