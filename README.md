# ARCBALL

<img src="animation/moving_bunny.gif?raw=true"/>

A program written for a class in C++ that implements the **ARCBALL**[1] mechanism for manipulating and rotating a scene with a mouse. The graphics pipeline were implemented using **OpenGL 3.0** and the display, using **GLUT**. 

ARCBALL works by mapping a click-and-drag motion of the mouse on the screen to a rotation about the surface of a sphere of radius 1 inscribed into the viewing cube in normalized device coordinates(NDC).

<img src="images/arcball.png?raw=true"/>

More specifically, when we click our mouse at point p=(p<sub>x</sub>, p<sub>y</sub>) and move the mouse to another point p'=(p'<sub>x</sub>, p'<sub>y</sub>), the program maps the two points to NDC coordinates (x,y,z) and (x',y',z'), and computes an angle angle &theta; and rotation vector u to rotate the object. 

Scene files were provided for the class, which contains information on setting up the camera, on light sources, on the objects to be loaded, the linear transformations to set up the scene and the materials properties needed for shading. Rotations are represented by a quaternions class.Rendering can be toggled between Gouraud shading and wireframe mode. 

The program has the following functionalities:
<br>
[w,a,s,d] - to navigate up, left, down and right.
<br>
[t] - to toggle between Gouraud shading and wireframe rendering.
<br>
[q] - exiting
___

### To-do list:

- OpenGL 3.0 with GLUT is very clunky. It will be nice to implement this using Vulkan instead.
___

### References

[1] [ARCBALL: a user infertace for specifying three-dimensional orientation using a mouse](https://dl.acm.org/doi/10.5555/155294.155312)


