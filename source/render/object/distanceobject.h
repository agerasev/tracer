#ifndef DISTANCEOBJECT_H
#define DISTANCEOBJECT_H

#include<functional>

#include"sphere.h"

class DistanceObject : public Sphere
{
private:
	static const int MAX_STEPS = 0x1000;

	std::function<double(const vec3 &)> func;

	const int fractions;
	const double step_factor;
	const double min_step;
	const double max_step;
	const double grad_epsilon;

public:
	DistanceObject(
			const vec3 &pos,
			double rad,
			std::function<double(const vec3 &)> f,
			int fract = 0x8,
			double sf = 0.1,
			double min = 1e-4,
			double max = 1.0,
			double grad_eps = 1e-8
			)
		:
		  Sphere(pos,rad),
		  func(f),
		  fractions(fract),
		  step_factor(sf),
		  min_step(min),
		  max_step(max),
		  grad_epsilon(grad_eps)
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

			double dist = func(pos - crd);

			/* Performs distance-aided ray marching */
			for(int i = 0; i < MAX_STEPS; ++i)
			{
				/* Clamps step size to range */
				double step = step_factor*dist;
				if(step < min_step)
				{
					step = min_step;
				}
				else if(step > max_step)
				{
					step = max_step;
				}

				vec3 lpos = pos + step*dir;

				if(sqr(lpos - crd) > sqr(getRadius()))
				{
					break;
				}

				double ldist = func(lpos - crd);

				if(ldist < 0.0)
				{
					/* Performs binary approximation */
					vec3 begin = pos, end = lpos, center = 0.5*(pos + lpos);
					for(int j = 0; j < fractions; ++j)
					{
						if(func(center - crd) < 0.0)
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
								  (func(pos + vec3(grad_epsilon,0,0) - crd) - func(pos - crd)),
								  (func(pos + vec3(0,grad_epsilon,0) - crd) - func(pos - crd)),
								  (func(pos + vec3(0,0,grad_epsilon) - crd) - func(pos - crd))
								  ));

				state.distance = (pos - ray.start)*ray.direction;
				state.point = pos;
				state.normal = n;
				return true;
			}
		}
		return false;
	}
};

namespace functional
{

inline double sphere(const vec3 &pos) { return length(pos) - 1.0; }
inline double displacement(const vec3 &pos) { return sin(pos.x())*sin(pos.y())*sin(pos.z()); }
inline double torus(const vec3 &pos, double width = 0.25) {
	return length(vec2(length(vec2(pos.x(),pos.z())) - 1.0, pos.y())) - width;
}

}

#endif // DISTANCEOBJECT_H
