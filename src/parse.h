#ifndef _PARSE_H_
#define _PARSE_H_

#include <sstream>
#include <fstream>
#include "variables.h"
#include "quaternion.h"
#include "utilities.h"

Object load_object(std::string name, const char* filename);
void parse(const char* filename);

#endif