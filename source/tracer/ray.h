#ifndef RAY_H
#define RAY_H

#include"../util/vec.hpp"
#include"../util/color.hpp"

class Ray {
public:
	vec3 start;
	vec3 direction; //must be normalized
	Color color;

	Ray(const vec3 &s, const vec3 &d, const Color &c = Color(1,1,1)) :
		start(s), direction(d), color(c) {}
};

#endif // RAY_H
