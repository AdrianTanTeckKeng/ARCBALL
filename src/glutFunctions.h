#ifndef _GLUTFUNCTIONS_H_
#define _GLUTFUNCTIONS_H_

#include "utilities.h"
#include "quaternion.h"
#include "parse.h"

void init(const char* filename);
void init_lights();
void display();
void reshape(int width, int height);
void mouse_pressed(int button, int state, int x, int y);
void mouse_moved(int x, int y);
void key_pressed(unsigned char key, int x, int y);
quaternion compute_rotation_quaternion(int x, int y);
quaternion Get_current_rotation();

#endif