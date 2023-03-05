
#pragma once
#include "Objects.h"

void draw_object(POBJECT o);
void clear_object(POBJECT o);
void move_paddelobject (POBJECT o);
void set_object_speed(POBJECT o, int speedx, int speedy);
void move_ballobject (POBJECT o);
int pixel_overlap(POBJECT o1, POBJECT o2);

static OBJECT paddle1 = {
	&paddle_geometry,
	0,0,
	2,28,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};


static OBJECT paddle2 = {
	&paddle_geometry,
	0,0,
	122,28,
	draw_object,
	clear_object,
	move_paddelobject,
	set_object_speed,
};



static OBJECT ball = {
	&ball_geometry,
	4,1,
	62,30,
	draw_object,
	clear_object,
	move_ballobject,
	set_object_speed
};



