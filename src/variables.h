#ifndef _GLOBAL_VARIABLES_H
#define _GLOBAL_VARIABLES_H

#include "quaternion.h"
#include  "utilities.h"

extern std::vector<Object> objects;
extern std::vector<Point_Light> lights;
extern Camera scene_camera;

extern quaternion last_rotation;
extern quaternion current_rotation;

extern int mouse_x, mouse_y;
extern float mouse_scale_x, mouse_scale_y;

extern const float step_size;
extern const float x_view_step, y_view_step;
extern float x_view_angle, y_view_angle;

extern bool is_pressed;
extern bool wireframe_mode;



#endif