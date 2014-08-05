#ifndef TRIANGLE_H
#define TRIANGLE_H

#include"object.h"

#include<material/material.h>

class Triangle : public Object
{
private:
	vec3 vertex[3];
	vec3 normal;
	Material *material;
public:
	Triangle(const vec3 v[3], Material *m)
	{
		vertex[0] = v[0];
		vertex[1] = v[1];
		vertex[2] = v[2];
		normal = norm((v[1] - v[0])^(v[2] - v[0]));
		material = m;
	}

	virtual bool intersect(
			const Ray &ray,
			IntersectState &state,
			const TraceParams::SceneParam &param
			) const
	{
		vec3 in = ray.start + ray.direction*(((vertex[0] - ray.start)*normal)/(ray.direction*normal));
		state.point = in;
		state.normal = normal;
		if(
				((in - vertex[0])^(vertex[1] - vertex[0]))*n > 0 &&
				((in - vertex[1])^(vertex[2] - vertex[1]))*n > 0 &&
				((in - vertex[2])^(vertex[0] - vertex[2]))*n > 0
				)
		{
			return true;
		}
		return false;
	}

	virtual vec3 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const IntersectState &state,
			const TraceParams::SceneParam &param,
			ContRand &rand) const
	{
		if(ray.flag & Ray::DIFFUSE)
		{
			return material->trace(ray,out,state,fdir,param,rand);
		}
		return nullvec4;
	}
};

#endif // TRIANGLE_H
