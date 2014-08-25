#ifndef PLANE_H
#define PLANE_H

#include<utility>

#include<4u/la/vec.hpp>
#include<4u/rand/contrand.hpp>

#include<render/object.h>
#include<render/params.h>

class Plane : public Object
{
private:
	vec3 position;
	vec3 normal;

public:
	Plane(vec3 p, vec3 n)
		: position(p), normal(n)
	{

	}

	virtual vec3 getPosition() const
	{
		return position;
	}

	virtual double getSize() const
	{
		return INFINITY;
	}

	vec3 getNormal() const
	{
		return normal;
	}

	/* returns true if intersection has happened
	 * Sets intersection state used by next steps */
	virtual bool intersect(
			const Ray &ray,
			Intersection &state,
			const SceneParams &,
			ContRand &
			) const
	{
		double side = normal*ray.direction;
		if(ray.flag & Ray::INSIDE)
		{
			if(side < 0.0)
			{
				return false;
			}
		}
		else
		{
			if(side > 0.0)
			{
				return false;
			}
		}

		double k = ((getPosition() - ray.start)*normal)/(ray.direction*normal);

		if(k <= 0.0)
		{
			return false;
		}

		vec3 in = ray.start + ray.direction*k;
		state.point = in;
		state.normal = normal;

		return true;
	}

};

#endif // PLANE_H
