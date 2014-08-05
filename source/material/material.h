#ifndef MATERIAL_H
#define MATERIAL_H

#include<object/object.h>

#include<4u/rand/rand.hpp>

class Material
{
public:
	virtual bool isAttractive() const = 0;
	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand,
			double weight = 1.0
			) const = 0;
};

#endif // MATERIAL_H
