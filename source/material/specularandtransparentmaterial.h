#ifndef SPECULARANDTRANSPARENTMATERIAL_H
#define SPECULARANDTRANSPARENTMATERIAL_H

#include"specularmaterial.h"
#include"transparentmaterial.h"

class SpecularAndTransparentMaterial : public SpecularMaterial, public TransparentMaterial
{
private:
	double specularity;
public:
	SpecularAndTransparentMaterial(double spec, double n, const vec4 &tr_col = vec4(1,1,1,1), const vec4 &sp_col = vec4(1,1,1,1))
		: TransparentMaterial(n,tr_col), SpecularMaterial(sp_col), specularity(spec)
	{

	}

	virtual bool isAttractive() const
	{
		return false;
	}

	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const std::vector< std::pair<vec3, double> > &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand,
			double weight = 1.0
			) const
	{
		unsigned size = out.size();
		double w = weight;
		TransparentMaterial::trace(ray,out,state,fdir,param,rand,weight*(1.0 - specularity));
		if(size != out.size())
		{
			w *= specularity;
		}
		// else - total internal reflection
		SpecularMaterial::trace(ray,out,state,fdir,param,rand,w);
		return nullvec4;
	}
};

#endif // SPECULARANDTRANSPARENTMATERIAL_H
