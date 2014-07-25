#ifndef OBJECT_H
#define OBJECT_H

#include<vector>

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>
#include"ray.h"

#include"object.h"
#include"ray.h"
#include"traceparams.h"

class Object
{
private:
	vec3 position;

public:
	/* Class for storing data computed at inersection
	 * stage and what is necessary for tracing stage */
	class IntersectState
	{
	public:

	};

	Object(vec3 pos)
		: position(pos)
	{

	}

	vec3 getPosition() const
	{
		return position;
	}

	/* Bounding radius of object is used
	 * to searching for intersections faster */
	virtual double getSize() const = 0;

	/* Method used to find closest intersection point
	 * without secondary raycasting */
	virtual bool intersect(const Ray &ray, vec3 &point, const TraceParams::SceneParam &param, IntersectState *&state) const = 0;

	/* Makes object forget about dumped state */
	virtual void forget(IntersectState *&state) const = 0;

	/* Causes next reytracing iterations after intersection point was founded.
	 * Produces secondary rays and returns emitting light */
	virtual std::vector<Ray> trace(const Ray &ray, vec4 &ret, const TraceParams::SceneParam &param, IntersectState *&state) const = 0;
};

#endif // OBJECT_H
