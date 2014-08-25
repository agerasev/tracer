#ifndef OBJECT_H
#define OBJECT_H

#include<list>
#include<vector>
#include<utility>
#include<functional>

#include<4u/rand/contrand.hpp>
#include<4u/la/vec.hpp>

#include"params.h"
#include"ray.h"

class Object
{
public:
	class Intersection
	{
	public:
		double distance;
		vec3 point;
		vec3 normal;
	};

	/* Returns position of object */
	virtual vec3 getPosition() const = 0;

	/* Bounding radius of object is used
	 * to looking for intersections faster */
	virtual double getSize() const = 0;

	/* returns true if intersection has happened
	 * Sets intersection state used by next steps */
	virtual bool intersect(
			const Ray &ray,
			Intersection &state,
			const SceneParams &params,
			ContRand &rand
			) const = 0;

	/* Returns glow color and adds secondary rays */
	virtual Color trace(
			const Ray &ray,
			const Intersection &state,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand
			) const = 0;

	/* Casts secondary ray to given direction with given probability */
	virtual void cast(
			const Ray &ray,
			const Intersection &state,
			const vec3 &dir,
			double prob,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand
			) const = 0;

	/* Returns kind of interaction as bitfield */
	virtual unsigned int getInteractionKind(const Intersection &state) const = 0;
};

#endif // OBJECT_H
