
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