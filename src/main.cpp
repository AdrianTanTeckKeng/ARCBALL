#include "quaternion.h"
#include "utilities.h"
#include "variables.h"
#include "glutFunctions.h"
#define _USE_MATH_DEFINES

using namespace std;


// 1. Declare all global variables here

int mouse_x, mouse_y;
float mouse_scale_x, mouse_scale_y;

const float step_size = 0.2;
const float x_view_step = 90.0;
const float y_view_step = 90.0;

float x_view_angle, y_view_angle;

bool is_pressed;
bool wireframe_mode;

std::vector<Object> objects;
std::vector<Point_Light> lights;
Camera scene_camera;
quaternion last_rotation;
quaternion current_rotation;




int main(int argc, const char* argv[]){
    if(argc != 4){
        std::cout << "Wrong number of input!" << std::endl;
        exit(1);
    }

    // Storing inputs
    int xres = atoi(argv[2]);
    int yres = atoi(argv[3]);

    // Fake parameters to initialize GLUT
    char fakeParam[] = "fake";
    char *fakeargv[] = { fakeParam, NULL };
    int fakeargc = 1;
    glutInit(&fakeargc, fakeargv);
    
    // Specify to OpenGL we will be using a double buffer
    // One buffer will be a RGB pixel buffer and the other a depth buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Creating a program window of size xres by yres
    glutInitWindowSize(xres, yres);

    // Setting coordinates of top-left corner of the screen as (0, 0)
    glutInitWindowPosition(0, 0);

    // Naming the program window "Test"
    glutCreateWindow("Test");

    // Call init function to initialize values
    init(argv[1]);

    /* Specify to OpenGL our display function.
     */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse_pressed);
    glutMotionFunc(mouse_moved);
    glutKeyboardFunc(key_pressed);

    glutMainLoop();

    return 0;
}