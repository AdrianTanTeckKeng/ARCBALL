#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <memory>
#include <math.h>
#include <algorithm>

// we declare all utility data structures and functions here


// 1. Data structures

struct Triple
{
    float x;
    float y;
    float z;
};

// Point light contains position, color and its attenuation factors
struct Point_Light
{
    float position[4];
    float color[3];
    float attenuation_k;
};

struct Transforms
{
    float translation[3];
    float rotation[3];
    float scaling[3];
    float rotation_angle;
    std::string type;
};

struct Object{
    std::vector<Triple> vertex_buffer;
    std::vector<Triple> normal_buffer;
    std::vector<Transforms> transform_sets;

    std::string name;
    float ambient_reflect[3];
    float diffuse_reflect[3];
    float specular_reflect[3];

    float shininess;
};

struct Camera{
    float cam_position[3];
    float cam_orientation_axis[3];
    float cam_orientation_angle;

    float near_param, far_param, left_param, right_param, top_param, bottom_param;
};

// 2. Helper functions

inline float deg2rad(float angle)
{
    return angle * M_PI / 180.0;
}

inline float rad2deg(float rad){
    return rad / M_PI * 180.0;
}

inline std::vector<std::string> split(const std::string str, const std::string regex_str)
{   // a yet more concise form!
    return { std::sregex_token_iterator(str.begin(), str.end(), std::regex(regex_str), -1), std::sregex_token_iterator() };
}

#endif