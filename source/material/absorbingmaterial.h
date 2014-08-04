#ifndef ABSORBINGMATERIAL_H
#define ABSORBINGMATERIAL_H

#include"material.h"

class AbsorbingMaterial : public Material
{
public:
	virtual vec4 trace(
			const Ray &ray,
            std::vector<Ray> &out,
			const Object::IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
            ContRand &rand
			) const
	{
		return vec4(0,0,0,1);
	}
};

#endif // ABSORBINGMATERIAL_H
