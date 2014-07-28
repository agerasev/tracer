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

	virtual vec3 getReflection(const vec3 &d, const vec3 &n) const
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
			const TraceParams::SceneParam &param

			) const
	{
		out.push_back( Ray(state.point, getReflection(ray.direction, state.normal), getColor() & ray.color) );
		return nullvec4;
	}
};

#endif // SPECULARMATERIAL_H
