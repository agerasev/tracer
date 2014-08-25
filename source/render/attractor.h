#ifndef ATTRACTOR_H
#define ATTRACTOR_H

#include<functional>

#include"params.h"
#include"ray.h"
#include"object.h"

#include<4u/la/vec.hpp>
#include<4u/rand/contrand.hpp>

class Attractor : public Object
{
public:
	/* Adds direction from given point to itself */
	virtual void attract(
			const vec3 &point,
			std::function<void(const vec3 &, double)> add,
			const SceneParams &params,
			ContRand &rand
			) const = 0;
};

#endif // ATTRACTOR_H
