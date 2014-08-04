#ifndef MATERIAL_H
#define MATERIAL_H

#include<object/object.h>

#include<4u/rand/rand.hpp>

class Material
{
public:
	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
            ContRand &rand
			) const = 0;
};

#endif // MATERIAL_H
