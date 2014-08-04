#ifndef QUAD_H
#define QUAD_H

#include"object.h"

#include<material/material.h>

class Quad : public Object
{
private:
	vec3 vertex[4];
	vec3 normal;
	Material *material;
public:
	Quad(const vec3 v[4], Material *m)
		: Object((v[0] + v[1] + v[2] + v[3])/4.0)
	{
		vertex[0] = v[0];
		vertex[1] = v[1];
		vertex[2] = v[2];
		vertex[3] = v[3];
		normal = norm((v[1] - v[0])^(v[2] - v[0]));
		material = m;
	}

	/*
	virtual void getSize() const
	{
		return vertex[0] +
	}
	*/

	virtual bool intersect(
			const Ray &ray,
			IntersectState &state,
			const TraceParams::SceneParam &param
			) const
	{
		if(normal*ray.direction >= 0)
		{
			return false;
		}

		double k = ((vertex[0] - ray.start)*normal)/(ray.direction*normal);

		vec3 in = ray.start + ray.direction*k;
		state.point = in;
		state.normal = normal;
		if(
				((in - vertex[0])^(vertex[1] - vertex[0]))*normal < 0 &&
				((in - vertex[1])^(vertex[2] - vertex[1]))*normal < 0 &&
				((in - vertex[2])^(vertex[3] - vertex[2]))*normal < 0 &&
				((in - vertex[3])^(vertex[0] - vertex[3]))*normal < 0
				)
		{
			return true;
		}
		return false;
	}

	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand) const
	{
		return material->trace(ray,out,state,fdir,param,rand);
	}
};

#endif // QUAD_H
