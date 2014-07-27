#ifndef MATERIAL_H
#define MATERIAL_H

#include<object/object.h>

class Material
{
public:
	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const TraceParams::SceneParam &param
			) const = 0;
};

#endif // MATERIAL_H
