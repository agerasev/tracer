#ifndef DISTANCEOBJECT_H
#define DISTANCEOBJECT_H

#include<functional>

#include"sphere.h"

class DistanceObject : public Sphere
{
private:
	static const int STEPS_NUMBER = 0x10000;
	static constexpr const double EPSILON = 1e-8;
	static const int FRACTIONS = 0x8;

	std::function<double(const vec3 &)> func;

	const double STEP_FACTOR;
	const double MIN_STEP;
	const double MAX_STEP;

public:
	DistanceObject(
			const vec3 &pos,
			double rad,
			double sf = 0.1,
			double min = 1e-4,
			double max = 1.0
			)
		:
		  Sphere(pos,rad),
		  STEP_FACTOR(sf),
		  MIN_STEP(min),
		  MAX_STEP(max)
	{

	}

	virtual bool intersect(
			const Ray &ray,
			Intersection &state,
			const SceneParams &params,
			ContRand &rand
			) const
	{
		/* Ray marching must start from outer sphere */
		if(
				Sphere::intersect(ray,state,params,rand) ||
				sqr((state.point = ray.start) - getPosition()) <= sqr(getRadius()))
		{
			vec3 crd = getPosition();

			vec3 pos = state.point;
			vec3 dir = ray.direction;
			bool hit = false;

			double dist = getDistance(pos - crd);

			/* Performs distance-aided ray marching */
			for(int i = 0; i < STEPS_NUMBER; ++i)
			{
				/* Clamps step size to range */
				double step = STEP_FACTOR*dist;
				if(step < MIN_STEP)
				{
					step = MIN_STEP;
				}
				else if(step > MAX_STEP)
				{
					step = MAX_STEP;
				}

				vec3 lpos = pos + step*dir;

				if(sqr(lpos - crd) > sqr(getRadius()))
				{
					break;
				}

				double ldist = getDistance(lpos - crd);

				if(ldist < 0.0)
				{
					/* Performs binary approximation */
					vec3 begin = pos, end = lpos, center = 0.5*(pos + lpos);
					for(int j = 0; j < FRACTIONS; ++j)
					{
						if(getDistance(center - crd) < 0.0)
						{
							end = center;
						}
						else
						{
							begin = center;
						}
						center = 0.5*(begin + end);
					}
					pos = center;

					hit = true;
					break;
				}

				pos = lpos;
				dist = ldist;
			}

			if(hit)
			{
				/* Computes the gradient for normal */
				vec3 n = norm(vec3(
								  (getDistance(pos + vec3(EPSILON,0,0) - crd) - getDistance(pos - crd)),
								  (getDistance(pos + vec3(0,EPSILON,0) - crd) - getDistance(pos - crd)),
								  (getDistance(pos + vec3(0,0,EPSILON) - crd) - getDistance(pos - crd))
								  ));

				state.distance = (pos - ray.start)*ray.direction;
				state.point = pos;
				state.normal = n;
				return true;
			}
		}
		return false;
	}

	virtual double getDistance(const vec3 &pos) const = 0;
};

#endif // DISTANCEOBJECT_H
