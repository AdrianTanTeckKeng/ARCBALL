#include "quaternion.h"

quaternion::quaternion()
{
    s=0; 
    u<<0,0,0;
}

quaternion::quaternion(float _real, Eigen::Vector3f _imag)
{
    s = _real;
    u = _imag;
}



float quaternion::norm(){
    return sqrt(s*s + u.dot(u));
}

void quaternion::setIdentity(){
    s = 1.;
    u[0] = 0;
    u[1] = 0;
    u[2] = 0;
}

Eigen::Matrix4f quaternion::getMatrix()
{
    Eigen::Matrix4f matrix;
    matrix << 1 - 2*u[1]*u[1] - 2*u[2]*u[2], 2*(u[0]*u[1] - u[2]*s), 2*(u[0]*u[2] + u[1]*s), 0,
    2*(u[0]*u[1] + u[2]*s), 1 - 2*u[0]*u[0] -2 *u[2]*u[2], 2*(u[1]*u[2] - u[0]*s), 0,
    2*(u[0] * u[2] - u[1] * s), 2*(u[1] * u[2] + u[0] * s), 1 - 2*u[0]*u[0] - 2*u[1]*u[1], 0,
    0, 0, 0, 1;
    return matrix;
}

