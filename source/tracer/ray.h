#ifndef RAY_H
#define RAY_H

#include<4u/la/vec.hpp>

class Ray {
public:
	vec3 start;
	vec3 direction; //must be normalized
	vec4 color;
	bool emitted;

	Ray(const vec3 &s, const vec3 &d, const vec4 &c = vec4(1,1,1,1), bool em = false) :
		start(s), direction(d), color(c), emitted(em) {}
};

#endif // RAY_H
