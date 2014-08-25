#ifndef NEBULA_H
#define NEBULA_H

#include"ray.h"
#include"params.h"
#include"placeable.h"

#include<4u/la/vec.hpp>

class Nebula : public Placeable
{
public:
	struct Intersection
	{
		double begin, end;
		vec3 pbegin, pend;
	};

	Nebula(vec3 pos)
		: Placeable(pos)
	{

	}

	/* Finds intersection points */
	virtual bool intersect(
			const Ray &ray,
			Intersection &state
			) const = 0;

	/* Produces secondary rays after intersection was found */
	virtual void pass(
			Ray &ray,
			const Intersection &state,
			const SceneParams &param,
			ContRand &rand
			) const = 0;
};

#endif // NEBULA_H
