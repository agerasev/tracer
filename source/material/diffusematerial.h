#ifndef DIFFUSEMATERIAL_H
#define DIFFUSEMATERIAL_H

#include<4u/rand/sphericrand.hpp>

#include"material.h"

#include<iostream>

class DiffuseMaterial : public virtual Material
{
private:
	vec4 color;

public:
	DiffuseMaterial(const vec4 &c)
		: Material(), color(c)
	{

	}

	virtual vec3 getReflection(
			const vec3 &d,
			const vec3 &n,
			ContRand &rand
			) const
	{
		return SemiSphericCosineRand::wrap(rand,n);
	}

	vec4 getColor() const
	{
		return color;
	}

	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
            ContRand &rand
			) const
	{
        for(const std::pair<vec3,double> &pair : fdir)
        {
			if(pair.first*state.normal > 0)
			{
                out.push_back(
                            Ray(
                                state.point,
                                pair.first,
								2*(state.normal*pair.first)*(getColor() & ray.color)*pair.second,
								true
								)
							);
            }
		}

        for(int i = 0; i < param.rays_density; ++i)
		{
			vec3 dir = getReflection(ray.direction,state.normal,rand);
			out.push_back(
						Ray(
							state.point,
							dir,
							(getColor() & ray.color)/param.rays_density
                            )
						);
		}

		return nullvec4;
	}
};

#endif // DIFFUSEMATERIAL_H
