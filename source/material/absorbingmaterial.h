#ifndef ABSORBINGMATERIAL_H
#define ABSORBINGMATERIAL_H

#include"material.h"

class AbsorbingMaterial : public Material
{
public:
	virtual bool isAttractive() const
	{
		return false;
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
		return vec4(0,0,0,1);
	}
};

#endif // ABSORBINGMATERIAL_H
