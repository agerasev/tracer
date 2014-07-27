#ifndef OBJECT_H
#define OBJECT_H

#include<vector>

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>
#include<tracer/ray.h>
#include<tracer/traceparams.h>

#include"object.h"

class Object
{
private:
	vec3 position;

public:
	class IntersectState
	{
	public:
		vec3 point;
		vec3 normal;
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
	virtual bool intersect(const Ray &ray, IntersectState &state, const TraceParams::SceneParam &param) const = 0;

	/* Causes next reytracing iterations after intersection point was founded.
	 * Produces secondary rays and returns emitting light */
	virtual vec4 trace(const Ray &ray, std::vector<Ray> &out, const IntersectState &state, const TraceParams::SceneParam &param) const = 0;
};

#endif // OBJECT_H
