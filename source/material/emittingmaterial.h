#ifndef EMITTINGMATERIAL_H
#define EMITTINGMATERIAL_H

#include"material.h"

class EmittingMaterial : public virtual Material
{
private:
	vec4 glow;

public:
	EmittingMaterial(const vec4 &g)
		: glow(g)
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
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand,
			double weight = 1.0
			) const
	{
		if(ray.flag & Ray::EMITTED)
		{
			return glow & ray.color;
		}
		return nullvec4;
	}
};

#endif // EMITTINGMATERIAL_H
