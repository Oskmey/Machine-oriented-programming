#pragma once
extern char SCORE1;
extern char SCORE2;
char GOAL;

typedef struct{
	char x,y;
} POINT, *PPOINT;

typedef struct{
	 POINT p0;
	 POINT p1;
}LINE, *PLINE;


#define MAX_POINTS 64 //ÄNDRA KANSE DETTA ****************************
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

static GEOMETRY line_geometry = {
	64,
	0,64,
	{
		{62, 1}, {62, 2}, {62, 3}, {62, 4}, {62, 5}, {62, 6}, {62, 7}, {62, 8}, {62, 9}, {62, 10},
		{62, 11}, {62, 12}, {62, 13}, {62, 14}, {62, 15}, {62, 16}, {62, 17}, {62, 18}, {62, 19}, {62, 20},
		{62, 21}, {62, 22}, {62, 23}, {62, 24}, {62, 25}, {62, 26}, {62, 27}, {62, 28}, {62, 29}, {62, 30},
		{62, 31}, {62, 32}, {62, 33}, {62, 34}, {62, 35}, {62, 36}, {62, 37}, {62, 38}, {62, 39}, {62, 40},
		{62, 41}, {62, 42}, {62, 43}, {62, 44}, {62, 45}, {62, 46}, {62, 47}, {62, 48}, {62, 49}, {62, 50},
		{62, 51}, {62, 52}, {62, 53}, {62, 54}, {62, 55}, {62, 56}, {62, 57}, {62, 58}, {62, 59}, {62, 60},
		{62, 61}, {62, 62}, {62, 63}, {62, 64},
	}
};

static OBJECT line = {
	&line_geometry,
	0,0,
	0,0,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};

static OBJECT paddle1 = {
	&paddle_geometry,
	0,0,
	112,32,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};


static OBJECT paddle2 = {
	&paddle_geometry,
	0,0,
	12,32,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};

static OBJECT ball = {
	&ball_geometry,
	4,1,
	64,32,
	draw_object,
	clear_object,
	move_ballobject,
	set_object_speed
};
