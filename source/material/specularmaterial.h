#ifndef SPECULARMATERIAL_H
#define SPECULARMATERIAL_H

#include"material.h"
#include<4u/la/vec.hpp>

class SpecularMaterial : public virtual Material
{
private:
	vec4 color;

public:
	SpecularMaterial(const vec4 &col = vec4(1,1,1,1))
		: color(col)
	{

	}

	virtual bool isAttractive() const
	{
		return false;
	}

	virtual vec3 getReflection(
			const vec3 &d,
			const vec3 &n,
			ContRand &rand
			) const
	{
		return d - (2.0*n*d)*n;
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
			ContRand &rand,
			double weight = 1.0
			) const
	{
		out.push_back(
					Ray(
						state.point,
						getReflection(ray.direction, state.normal, rand),
						weight*(getColor() & ray.color),
						ray.flag
						)
					);
		return nullvec4;
	}
};

#endif // SPECULARMATERIAL_H
