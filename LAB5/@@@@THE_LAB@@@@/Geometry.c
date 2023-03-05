
#include "Geometry.h"
void draw_object(POBJECT o)
{
	PGEOMETRY geo = o->geo;
	POINT *point_list = geo->px;
	int pixels = geo->numpoints;
	int x = o->posx;
	if( x > 50000){ //Codlite tycker om att ge skit stora värden!!! randomly så stacken går sönder?
		o -> posx = 2;
		o -> posy = 64-9;
	}
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

int cross_points(POINT point, POINT upper_left, POINT bottom_right)
{
    if (point.x <= bottom_right.x && point.x >= upper_left.x){
        if (point.y <= bottom_right.y && point.y >= upper_left.y){
            return 1;
        }
    }

    return 0;
}

int pixel_overlap(POBJECT o1, POBJECT o2)
{
    POINT o1_upper_left = { o1->posx, o1->posy};
    POINT o1_bottom_right = { o1->posx + o1->geo->sizex, o1->posy + o1->geo->sizey}; // Ser mellan två cross points. behövde se på en video
	
	POINT o1_bottom_left = { o1->posx, o1->posy + o1->geo->sizey};
    POINT o1_upper_right = { o1->posx + o1->geo->sizex, o1->posy};
	
    POINT o2_upper_left = { o2->posx, o2->posy};
    POINT o2_upper_right = { o2->posx + o2->geo->sizex, o2->posy};
    POINT o2_bottom_left = { o2->posx, o2->posy + o2->geo->sizey};
    POINT o2_bottom_right = { o2->posx + o2->geo->sizex, o2->posy + o2->geo->sizey};

    if (cross_points(o2_upper_left, o1_upper_left, o1_bottom_right)){
        return 1;
    }

    if (cross_points(o2_upper_right, o1_upper_left, o1_bottom_right)){
        return 1;
    }

    if (cross_points(o2_bottom_left, o1_upper_left, o1_bottom_right)){
        return 1;
    }

    if (cross_points(o2_bottom_right, o1_upper_left, o1_bottom_right)){
        return 1;
    }
	//KILL ME
	if (cross_points(o2_bottom_right, o1_upper_left, o1_bottom_right)){
        return 1;
    }

    return 0;
}