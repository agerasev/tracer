#ifndef SPECULARANDDIFFUSEMATERIAL_H
#define SPECULARANDDIFFUSEMATERIAL_H

#include"material.h"
#include"specularmaterial.h"
#include"diffusematerial.h"

class SpecularAndDiffuseMaterial : public SpecularMaterial, public DiffuseMaterial
{
private:
	double specularity;
public:
	SpecularAndDiffuseMaterial(double spec_factor, vec4 diff_color, vec4 spec_color = vec4(1,1,1,1))
		:
		  DiffuseMaterial(diff_color),
		  SpecularMaterial(spec_color),
		  specularity(spec_factor)
	{

	}
	virtual bool isAttractive() const
	{
		return true;
	}
	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand,
			double weight = 1.0
			) const
	{
		SpecularMaterial::trace(ray,out,state,fdir,param,rand,weight*specularity);
		DiffuseMaterial::trace(ray,out,state,fdir,param,rand,weight*(1.0 - specularity));
		return nullvec4;
	}
};

#endif // SPECULARANDDIFFUSEMATERIAL_H
