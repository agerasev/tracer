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
	SpecularAndDiffuseMaterial(vec4 spec_color, vec4 diff_color, SemiSphericRand *diff_rand, double spec_factor)
		:
		  SpecularMaterial(spec_color),
		  DiffuseMaterial(diff_color,diff_rand),
		  factor(spec_factor)
	{

	}
	virtual vec4 trace(const Ray &ray, std::vector<Ray> &out, const Object::IntersectState &state, const TraceParams::SceneParam &param) const
	{
		out.push_back(
					Ray(
						state.point,
						SpecularMaterial::getReflection(ray.direction, state.normal),
						factor*(SpecularMaterial::getColor() & ray.color)
						)
					);

		for(int i = 0; i < param.rays_density - 1; ++i)
		{
			out.push_back(
						Ray(
							state.point,
							DiffuseMaterial::getReflection(ray.direction, state.normal),
							(1.0 - factor)/(param.rays_density - 1)*(DiffuseMaterial::getColor() & ray.color))
						);
		}

		return nullvec4;
	}
};

#endif // SPECULARANDDIFFUSEMATERIAL_H
