#ifndef __COLOR_UTIL_H
#define __COLOR_UTIL_H

#include <math.h>
#include <cmath>

#define PI 3.14159

typedef unsigned char COLOR_COMPONENT;
typedef unsigned int  COLOR;

struct VEC3
{
	float r, g, b;

	VEC3() : r(), g(), b() {}
	VEC3(float r, float b, float g) : r(r), g(g), b(b) {}
};

/* Function prototypes */
COLOR	createColor(bool enable, const COLOR_COMPONENT* r, const COLOR_COMPONENT* g, const COLOR_COMPONENT* b);
float	dot(VEC3* a, VEC3* b);
void	normalize(VEC3* v);

#endif