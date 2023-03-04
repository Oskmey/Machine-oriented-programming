
#pragma once
#include "Objects.h"

void draw_object(POBJECT o);
void clear_object(POBJECT o);
void move_paddelobject (POBJECT o);
void set_object_speed(POBJECT o, int speedx, int speedy);
void move_ballobject (POBJECT o);
int pixel_overlap(POBJECT o1, POBJECT o2);





