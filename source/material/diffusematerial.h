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
		return SemiSphericRandStatic::wrap(rand,n);
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
		double prob = 1.0;

        for(const std::pair<vec3,double> &pair : fdir)
        {
			if(pair.first*state.normal > 0)
			{
                out.push_back(
                            Ray(
                                state.point,
                                pair.first,
								2*(pair.first*state.normal)*(getColor() & ray.color)*pair.second
								)
                            );
				prob -= pair.second;
            }
		}

        for(int i = 0; i < param.rays_density; ++i)
		{
			vec3 dir = getReflection(ray.direction,state.normal,rand);
			out.push_back(
						Ray(
							state.point,
							dir,
							2*(dir*state.normal)*prob*(getColor() & ray.color)/param.rays_density
                            )
						);
		}

		return nullvec4;
	}
};

#endif // DIFFUSEMATERIAL_H
