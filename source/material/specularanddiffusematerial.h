#ifndef SPECULARANDDIFFUSEMATERIAL_H
#define SPECULARANDDIFFUSEMATERIAL_H

#include"material.h"
#include"specularmaterial.h"
#include"diffusematerial.h"

class SpecularAndDiffuseMaterial : public SpecularMaterial, public DiffuseMaterial
{
private:
	double factor;
public:
	SpecularAndDiffuseMaterial(vec4 spec_color, vec4 diff_color, double spec_factor)
		:
		  SpecularMaterial(spec_color),
		  DiffuseMaterial(diff_color),
		  factor(spec_factor)
	{

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
		out.push_back(
					Ray(
						state.point,
						SpecularMaterial::getReflection(ray.direction, state.normal, rand),
						factor*(SpecularMaterial::getColor() & ray.color)
						)
					);

		for(int i = 0; i < param.rays_density - 1; ++i)
		{
			out.push_back(
						Ray(
							state.point,
							DiffuseMaterial::getReflection(ray.direction, state.normal, rand),
							(1.0 - factor)/(param.rays_density - 1)*(DiffuseMaterial::getColor() & ray.color))
						);
		}

		return nullvec4;
	}
};

#endif // SPECULARANDDIFFUSEMATERIAL_H
