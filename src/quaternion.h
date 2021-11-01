#ifndef _QUATERNIONS_H
#define _QUATERNIONS_H

#include <Eigen/Dense>
#include <math.h>

class quaternion{
public:
    float s;
    Eigen::Vector3f u;
public:

    // Constructor
    quaternion();
    quaternion(float _real, Eigen::Vector3f _imag);

    // methods to get norm
    float norm();
    void setIdentity();
    Eigen::Matrix4f getMatrix();
};


inline quaternion operator*(const quaternion& q1, const quaternion& q2) {
    return quaternion(q1.s * q2.s - q1.u.dot(q2.u), q1.s*q2.u + q2.s*q1.u + q1.u.cross(q2.u));
}

inline quaternion operator*(float t, const quaternion& q) {
    return quaternion(t * q.s, t * q.u);
}

inline quaternion operator*(const quaternion& q, float t) {
    return t * q;
}



#endif