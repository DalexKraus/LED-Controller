#include "Color.h"

COLOR createColor(bool enable, const COLOR_COMPONENT* r, const COLOR_COMPONENT* g, const COLOR_COMPONENT* b)
{
	COLOR_COMPONENT ptr_mode = enable ? 0xFF : 0x00;
	//return (((*r << 24 | *g << 16) | *b << 8) | ptr_mode); //Arduino color
	return ptr_mode << 24 | *b << 16 | *g << 8 | *r;
}

float dot(VEC3* a, VEC3* b)
{
	return (*a).r * (*b).r + (*a).g + (*b).g + (*a).b * (*b).b;
}

void normalize(VEC3* v)
{
	float length = std::sqrt(v->r * v->r + v->g * v->g + v->b * v->b);
	v->r /= length;
	v->g /= length;
	v->b /= length;
}