#include "glutFunctions.h"


void init(const char* filename)
{
    std::cout << "Hello" << std::endl;

    // Initialize global variables

    // a. Initialize current and last rotation

    last_rotation.setIdentity();
    current_rotation.setIdentity();

    // b. information for renderer

    x_view_angle = 0;
    y_view_angle = 0;

    bool is_pressed = false;
    bool wireframe_mode = false;

    // Parse file and store data into global variables
    parse(filename);
    
    // Tell OpenGL to use Gouraud shading
    glShadeModel(GL_SMOOTH);

    // Tell OpenGL to perform backface culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Tell OpenGL to perform depth buffering
    glEnable(GL_DEPTH_TEST);

    // Perform normal normalization for lighting
    glEnable(GL_NORMALIZE);

    // Enable vertex array and normal array
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Construct perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(scene_camera.left_param, scene_camera.right_param,
              scene_camera.bottom_param, scene_camera.top_param,
              scene_camera.near_param, scene_camera.far_param);

    glMatrixMode(GL_MODELVIEW);

    init_lights();
}

void init_lights(){
    glEnable(GL_LIGHTING);

    int num_lights = lights.size();
    for(int i=0; i<num_lights; ++i){
        int light_id = GL_LIGHT0 + i;
        glEnable(light_id);

        glLightfv(light_id, GL_AMBIENT, lights[i].color);
        glLightfv(light_id, GL_DIFFUSE, lights[i].color);
        glLightfv(light_id, GL_SPECULAR, lights[i].color);

        glLightf(light_id, GL_QUADRATIC_ATTENUATION, lights[i].attenuation_k);
    }
}

void set_lights()
{
    int num_lights = lights.size();
    
    for(int i = 0; i < num_lights; ++i)
    {
        int light_id = GL_LIGHT0 + i;
        
        glLightfv(light_id, GL_POSITION, lights[i].position);
    }
}

void draw_objects()
{
    int num_objects = objects.size();
    
    for(int i = 0; i < num_objects; ++i)
    {
        glPushMatrix();
        {
            int num_transform_sets = objects[i].transform_sets.size();
            // We perform our actions in reverse because OpenGL post multiply their matrices
            for(int j = num_transform_sets-1; j >= 0; --j)
            {
                bool tmp = false;
                if(objects[i].transform_sets[j].type=="t")
                {
                    glTranslatef(objects[i].transform_sets[j].translation[0],
                                 objects[i].transform_sets[j].translation[1],
                                 objects[i].transform_sets[j].translation[2]);
                    tmp = true;
                }
                else if(objects[i].transform_sets[j].type=="r")
                {
                    glRotatef(objects[i].transform_sets[j].rotation_angle,
                              objects[i].transform_sets[j].rotation[0],
                              objects[i].transform_sets[j].rotation[1],
                              objects[i].transform_sets[j].rotation[2]);
                    tmp = true;
                }
                else if(objects[i].transform_sets[j].type=="s")
                {
                    glScalef(objects[i].transform_sets[j].scaling[0],
                             objects[i].transform_sets[j].scaling[1],
                             objects[i].transform_sets[j].scaling[2]);
                    tmp = true;
                }

                if(!tmp)
                {
                    std::cout << "Error in transform sets" << std::endl;
                    exit(1);
                }
            }
            
            glMaterialfv(GL_FRONT, GL_AMBIENT, objects[i].ambient_reflect);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, objects[i].diffuse_reflect);
            glMaterialfv(GL_FRONT, GL_SPECULAR, objects[i].specular_reflect);
            glMaterialf(GL_FRONT, GL_SHININESS, objects[i].shininess);
            
            
            glVertexPointer(3, GL_FLOAT, 0, &objects[i].vertex_buffer[0]);
            glNormalPointer(GL_FLOAT, 0, &objects[i].normal_buffer[0]);
            
            int buffer_size = objects[i].vertex_buffer.size();

            if(!wireframe_mode)
                glDrawArrays(GL_TRIANGLES, 0, buffer_size);
            else
                for(int j = 0; j < buffer_size; j += 3)
                    glDrawArrays(GL_LINE_LOOP, j, 3);
        }
        glPopMatrix();
    }
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Code to set up scree, camera etc
    glLoadIdentity();

    glRotatef(y_view_angle, 1, 0, 0);
    glRotatef(x_view_angle, 0, 1, 0);

    glRotatef(-scene_camera.cam_orientation_angle,
               scene_camera.cam_orientation_axis[0], 
               scene_camera.cam_orientation_axis[1], 
               scene_camera.cam_orientation_axis[2]);

    glTranslatef(-scene_camera.cam_position[0], 
                  -scene_camera.cam_position[1], 
                  -scene_camera.cam_position[2]);


    //glMultMatrixf(Get_current_rotation().data());
    glMultMatrixf(Get_current_rotation().getMatrix().data());

    // code to set up lights and then draw
    set_lights();
    draw_objects();

     glutSwapBuffers();
}

void reshape(int width, int height)
{
    height = (height == 0) ? 1 : height;
    width = (width == 0) ? 1 : width;
    
    glViewport(0, 0, width, height);
    
    mouse_scale_x = (float) (scene_camera.right_param - scene_camera.left_param) / (float) width;
    mouse_scale_y = (float) (scene_camera.top_param - scene_camera.bottom_param) / (float) height;
    
    glutPostRedisplay();
}

void mouse_pressed(int button, int state, int x, int y)
{
    /* If the left-mouse button was clicked down, then...
     */
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        /* Store the mouse position in our global variables.
         */
        mouse_x = x;
        mouse_y = y;
        //std::cout << "x-coordinate " << mouse_x << std::endl;
        //std::cout << "y-coordinate " << mouse_y << std::endl;
        //std::cout << "width" << glutGet(GLUT_WINDOW_WIDTH) << std::endl;
        //std::cout << "height" << glutGet(GLUT_WINDOW_HEIGHT) << std::endl;
        
        /* Since the mouse is being pressed down, we set our 'is_pressed"
         * boolean indicator to true.
         */
        is_pressed = true;
    }
    /* If the left-mouse button was released up, then...
     */
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        /* Mouse is no longer being pressed, so set our indicator to false.
         */
        is_pressed = false;

        last_rotation = current_rotation * last_rotation;
        current_rotation.setIdentity();
    }
}

void mouse_moved(int x, int y)
{
    /* If the left-mouse button is being clicked down...
     */
    if(is_pressed)
    {
        /* You see in the 'mouse_pressed' function that when the left-mouse button
         * is first clicked down, we store the screen coordinates of where the
         * mouse was pressed down in 'mouse_x' and 'mouse_y'. When we move the
         * mouse, its screen coordinates change and are captured by the 'x' and
         * 'y' parameters to the 'mouse_moved' function. We want to compute a change
         * in our camera angle based on the distance that the mouse traveled.
         *
         * We have two distances traveled: a dx equal to 'x' - 'mouse_x' and a
         * dy equal to 'y' - 'mouse_y'. We need to compute the desired changes in
         * the horizontal (x) angle of the camera and the vertical (y) angle of
         * the camera.
         * 
         * Let's start with the horizontal angle change. We first need to convert
         * the dx traveled in screen coordinates to a dx traveled in camera space.
         * The conversion is done using our 'mouse_scale_x' variable, which we
         * set in our 'reshape' function. We then multiply by our 'x_view_step'
         * variable, which is an arbitrary value that determines how "fast" we
         * want the camera angle to change. Higher values for 'x_view_step' cause
         * the camera to move more when we drag the mouse. We had set 'x_view_step'
         * to 90 at the top of this file (where we declared all our variables).
         * 
         * We then add the horizontal change in camera angle to our 'x_view_angle'
         * variable, which keeps track of the cumulative horizontal change in our
         * camera angle. 'x_view_angle' is used in the camera rotations specified
         * in the 'display' function.
         */
        //x_view_angle += ((float) x - (float) mouse_x) * mouse_scale_x * x_view_step;
        
        /* We do basically the same process as above to compute the vertical change
         * in camera angle. The only real difference is that we want to keep the
         * camera angle changes realistic, and it is unrealistic for someone in
         * real life to be able to change their vertical "camera angle" more than
         * ~90 degrees (they would have to detach their head and spin it vertically
         * or something...). So we decide to restrict the cumulative vertical angle
         * change between -90 and 90 degrees.
         */
        //float temp_y_view_angle = y_view_angle +
        //                          ((float) y - (float) mouse_y) * mouse_scale_y * y_view_step;
        //y_view_angle = (temp_y_view_angle > 90 || temp_y_view_angle < -90) ?
        //               y_view_angle : temp_y_view_angle;
        
        /* We update our 'mouse_x' and 'mouse_y' variables so that if the user moves
         * the mouse again without releasing it, then the distance we compute on the
         * next call to the 'mouse_moved' function will be from this current mouse
         * position.
         */
        //mouse_x = x;
        //mouse_y = y;
        


        /* We update our 'mouse_x' and 'mouse_y' variables so that if the user moves
         * the mouse again without releasing it, then the distance we compute on the
         * next call to the 'mouse_moved' function will be from this current mouse
         * position.
         */

        /* Tell OpenGL that it needs to re-render our scene with the new camera
         * angles.
         */
        current_rotation = compute_rotation_quaternion(x, y);

        glutPostRedisplay();
    }
}

void key_pressed(unsigned char key, int x, int y)
{
    /* If 'q' is pressed, quit the program.
     */
    if(key == 'q')
    {
        exit(0);
    }
    /* If 't' is pressed, toggle our 'wireframe_mode' boolean to make OpenGL
     * render our cubes as surfaces of wireframes.
     */
    else if(key == 't')
    {
        wireframe_mode = !wireframe_mode;
        /* Tell OpenGL that it needs to re-render our scene with the cubes
         * now as wireframes (or surfaces if they were wireframes before).
         */
        glutPostRedisplay();
    }
    else
    {
        /* These might look a bit complicated, but all we are really doing is
         * using our current change in the horizontal camera angle (ie. the
         * value of 'x_view_angle') to compute the correct changes in our x and
         * z coordinates in camera space as we move forward, backward, to the left,
         * or to the right.
         *
         * 'step_size' is an arbitrary value to determine how "big" our steps
         * are.
         *
         * We make the x and z coordinate changes to the camera position, since
         * moving forward, backward, etc is basically just shifting our view
         * of the scene.
         */
        
        float x_view_rad = deg2rad(x_view_angle);
        
        /* 'w' for step forward
         */
        if(key == 'w')
        {
            scene_camera.cam_position[0] += step_size * sin(x_view_rad);
            scene_camera.cam_position[2] -= step_size * cos(x_view_rad);
            glutPostRedisplay();
        }
        /* 'a' for step left
         */
        else if(key == 'a')
        {
            scene_camera.cam_position[0] -= step_size * cos(x_view_rad);
            scene_camera.cam_position[2] -= step_size * sin(x_view_rad);
            glutPostRedisplay();
        }
        /* 's' for step backward
         */
        else if(key == 's')
        {
            scene_camera.cam_position[0] -= step_size * sin(x_view_rad);
            scene_camera.cam_position[2] += step_size * cos(x_view_rad);
            glutPostRedisplay();
        }
        /* 'd' for step right
         */
        else if(key == 'd')
        {
            scene_camera.cam_position[0] += step_size * cos(x_view_rad);
            scene_camera.cam_position[2] += step_size * sin(x_view_rad);
            glutPostRedisplay();
        }
    }
}

quaternion Get_current_rotation()
{
    return current_rotation * last_rotation;
}

quaternion compute_rotation_quaternion(int x_current, int y_current)
{
    float xndc, yndc, zndc, xcndc, ycndc, zcndc, tmp;

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    // Convert coordinates to NDC
    xndc =  2. * ((float)mouse_x / (float)width) - 1;
    yndc = -2. * ((float)mouse_y / (float)height) + 1;
    tmp = xndc * xndc + yndc * yndc;
    zndc = (tmp <= 1) ? sqrt(1-tmp) : 0;


    xcndc =  2. * ((float)x_current / (float)width) - 1;
    ycndc = -2. * ((float)y_current / (float)height) + 1;
    tmp = xcndc * xcndc + ycndc * ycndc;
    zcndc = (tmp <= 1) ? sqrt(1-tmp) : 0;

    Eigen::Vector3f pndc, pcndc;
    pndc << xndc, yndc, zndc;
    pcndc << xcndc, ycndc, zcndc;

    // Compute theta

    float theta;
    theta = acos(std::min((float)1., pndc.dot(pcndc) / (pndc.norm() * pcndc.norm())));

    // Construct u vector
    Eigen::Vector3f u;
    u = pndc.cross(pcndc);
    u = u/u.norm();
    
    return quaternion(cos(theta/2), u*sin(theta/2));
}