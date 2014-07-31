#ifndef DIFFUSEMATERIAL_H
#define DIFFUSEMATERIAL_H

#include<4u/rand/sphericrand.hpp>

#include"material.h"

class DiffuseMaterial : public virtual Material
{
private:
	SemiSphericRand *rand;
	vec4 color;

public:
	DiffuseMaterial(const vec4 &c, SemiSphericRand *r)
		: Material(), rand(r), color(c)
	{

	}

	virtual vec3 getReflection(const vec3 &d, const vec3 &n) const
	{
		return rand->get(n);
	}

	vec4 getColor() const
	{
		return color;
	}

	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const TraceParams::SceneParam &param
			) const
	{


		for(int i = 0; i < param.rays_density; ++i)
		{
			out.push_back(
						Ray(
							state.point,
							getReflection(ray.direction,state.normal),
							(getColor() & ray.color)/param.rays_density)
						);
		}

		return nullvec4;
	}
};

#endif // DIFFUSEMATERIAL_H
