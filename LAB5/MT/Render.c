
#include "Render.h"


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
}

int pixel_overlap(POBJECT o1, POBJECT o2) {
	int offset1x = o1 -> posx;
	int offset1y = o1 -> posy;
	int offset2x = o2->posx;
	int offset2y = o2->posy;
	int sizexo1 = o1 -> geo-> sizex + offset1x;
	int sizeyo1 = o1 -> geo-> sizey + offset1y;
	int sizexo2 = o2 -> geo-> sizex + offset2x;
	int sizeyo2 = o2 -> geo-> sizey + offset2y;
	if( (sizexo1 >= offset2x) && ( offset1y <= sizeyo2) 
  /*for (int i = 0; i < o1->geo->numpoints; i++) {
    for (int j = 0; j < o2-> geo->numpoints; j++)
      if ((offset1x + o1->geo->px[i].x == offset2x + o2->geo->px[j].x) &&
        (offset1y + o1->geo->px[i].y == offset2y + o2->geo->px[j].y)) return 1;
  }
  return 0;
}*/


//______Things____________________________________________________________________________________________

OBJECT paddle1 = {
	&paddle_geometry,
	0,0,
	122,32,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};


OBJECT paddle2 = {
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