#pragma once
//____Struct______________________________________________________________________________________________________________________________
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

typedef struct polygonpoint{
	char x,y;
	struct polygonpoint* next;
}POLYPOINT, *PPOLYPOINT;

//____Sprites______________________________________________________________________________________________________________________________

static GEOMETRY paddle_geometry = {
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