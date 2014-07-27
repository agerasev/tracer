#ifndef SPECULARMATERIAL_H
#define SPECULARMATERIAL_H

#include"material.h"
#include<4u/la/vec.hpp>

class SpecularMaterial : public Material
{
private:
	vec4 color;

public:
	SpecularMaterial(const vec4 &col = vec4(1,1,1,1))
		: color(col)
	{

	}

	virtual vec4 trace(

			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const TraceParams::SceneParam &param

			) const
	{
		vec3 refldir = ray.direction - (2.0*state.normal*ray.direction)*state.normal;

		/* Move distribution computation to materials */
		/*
		for(int i = 0; i < 1<<param.rays_density; ++i) {
			vec3 v = reflection.cont();

			// ambient
			// buffer.push_back(Ray(*point, v, ray.color*material.ambient/(1<<quality)));

			// diffuse
			// v = reflection.direct(v);
			// buffer.push_back(Ray(*point, v, ray.color/(1<<param.rays_density)));
		}
		*/

		out.push_back( Ray(state.point, refldir, color & ray.color) );

		return nullvec4;
	}
};

#endif // SPECULARMATERIAL_H
