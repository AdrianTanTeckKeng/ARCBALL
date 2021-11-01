# ARCBALL

<img src="animation/moving_bunny.gif?raw=true"/>

A program written for a class in C++ that implements the **ARCBALL**[1] mechanism for manipulating and rotating a scene with a mouse. The methods work by mapping a click-and-drag motion of the mouse on the screen to a rotation about the surface of a sphere of radius 1 inscribed into the viewing cube in normalized device coordinates.

More specifically, when we click our mouse at point h<sub>&theta;</sub>(x) = &theta;<sub>o</sub> x + &theta;<sub>1</sub>x


<img src="images/arcball.png?raw=true"/>

Scene files were provided for the class, which contains information on setting up the camera, on light sources, on the objects to be loaded, the linear transformations to set up the scene and the materials properties needed for shading.

The graphics pipeline were implemented using **OpenGL 3.0** and the display, using **GLUT**. Rotations are represented by a quaternions class.
___

### To-do list:

[1] OpenGL 3.0 with GLUT is very clunky. It will be nice to implement this using Vulkan instead.
___

### References

[1] [ARCBALL: a user infertace for specifying three-dimensional orientation using a mouse](https://dl.acm.org/doi/10.5555/155294.155312)


