
#include "Render.h"


/* Pong_logic____________________________________________________________________________________________________________________________*/

void draw_object(POBJECT o){
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

void clear_object(POBJECT o){
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
	if ( (offset1x < offset2x +4) && (offset2x < offset1x + 5)){
		if((offset1y < offset2y + 4) && (offset2y < offset1y + 9)) {
			o2->set_object_speed(o2, -(o2->dirx), (o2->diry));
}
	}
}


//______Things____________________________________________________________________________________________

