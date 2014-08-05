#ifndef RAY_H
#define RAY_H

#include<4u/la/vec.hpp>

class Ray {
public:

	/* Flags */
	static const unsigned int
	DIFFUSE		= (1<<0),	/* for diffuse lighting */
	EMITTED		= (1<<1),	/* for direct emitter lighting */
	INSIDE		= (1<<2);	/* for ray tracing inside object */

	vec3 start;
	vec3 direction; //must be normalized
	vec4 color;
	unsigned int flag;

	Ray(const vec3 &s, const vec3 &d, const vec4 &c = vec4(1,1,1,1), unsigned int fl = DIFFUSE | EMITTED) :
		start(s), direction(d), color(c), flag(fl) {}
};

#endif // RAY_H
