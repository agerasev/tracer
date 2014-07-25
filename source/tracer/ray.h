#ifndef RAY_H
#define RAY_H

#include<4u/la/vec.hpp>

class Ray {
public:
	vec3 start;
	vec3 direction; //must be normalized
	vec4 color;

	Ray(const vec3 &s, const vec3 &d, const vec4 &c = vec4(1,1,1,1)) :
		start(s), direction(d), color(c) {}
};

#endif // RAY_H
