#ifndef RAY_H
#define RAY_H

#include<4u/la/vec.hpp>
#include"color.h"

class Ray
{
public:
	static const unsigned int

	DIFFUSE	= 1<<0,
	REFLECT	= 1<<1,
	REFRACT	= 1<<2,
	DEPRESS	= 1<<3,
	EMIT	= 1<<4,
	GLOW	= 1<<5,

	CAST	= 1<<7,
	INSIDE	= 1<<8;

	vec3 start;
	vec3 direction;
	Color color;
	unsigned int mask;
	unsigned int flag;

	Ray(const vec3 &s, const vec3 &d, const Color &c, unsigned int m, unsigned int f)
		: start(s), direction(d), color(c), mask(m), flag(f)
	{

	}
};

#endif // RAY_H
