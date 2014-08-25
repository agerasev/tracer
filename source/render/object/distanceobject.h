#ifndef DISTANCEOBJECT_H
#define DISTANCEOBJECT_H

#include"object.h"

class DistanceObject : public virtual Object
{
private:
	const double EPS;
	const double STEP;
	const int DEPTH;
	const double GRAD_EPS;
public:
	DistanceObject(
			const vec3 &pos,
			double eps = 1e-8,
			double step = 0.1,
			int depth = 0x200,
			double grad_eps = 1e-8
			)
		:
		  Object(pos),
		  EPS(eps),
		  STEP(step),
		  DEPTH(depth),
		  GRAD_EPS(grad_eps)
	{

	}

	/* Method used to find closest intersection point
	 * without secondary raycasting */
	virtual bool intersect(
			const Ray &ray,
			IntersectState &state,
			const TraceParams::SceneParam &param
			) const
	{
		//return false;
		vec3 pos = ray.start;
		vec3 dir = ray.direction;
		double dist = 0.0;
		bool hit = false;
		/* Performs distance-aided ray marching */
		for(int i = 0; i < DEPTH; ++i)
		{
			dist = getDistance(pos);
			if(dist < EPS && getDistance(pos + GRAD_EPS*dir) - dist < 0.0)
			{
				hit = true;
				break;
			}
			pos += STEP*dist*dir;
		}

		if(hit)
		{
			/* Computes the gradient for normal */
			vec3 n = norm(vec3(
							  (getDistance(pos + vec3(GRAD_EPS,0,0)) - getDistance(pos)),
							  (getDistance(pos + vec3(0,GRAD_EPS,0)) - getDistance(pos)),
							  (getDistance(pos + vec3(0,0,GRAD_EPS)) - getDistance(pos))
							  )/GRAD_EPS);

			state.point = pos;
			state.normal = n;
			return true;
		}
		return false;
	}

	virtual double getDistance(const vec3 &pos) const = 0;
};

#endif // DISTANCEOBJECT_H
