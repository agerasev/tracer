#ifndef PLANE_H
#define PLANE_H

#include"object.h"

#include<4u/util/const.hpp>

#include<material/material.h>

class Plane : public Object
{
private:
	vec3 point;
	vec3 normal;
	Material *material;
public:
	Quad(const p, vec3 n, Material *m)
		: Object(p), point(p), normal(n)
	{
		material = m;
	}

	/*
	virtual void getSize() const
	{
		return vertex[0] +
	}
	*/

	virtual bool isAttractive() const
	{
		return material->isAttractive();
	}

	bool getIntersection(const vec3 &b, const vec3 &d, vec3 &in)
	{
		if(normal*d >= 0.0)
		{
			return false;
		}

		double k = (((point + EPS*normal) - b)*normal)/(d*normal);

		if(k <= 0.0)
		{
			return false;
		}

		vec3 in = ray.start + ray.direction*k;
	}
	vec3 getNormal()
	{
		return normal;
	}

	virtual bool intersect(
			const Ray &ray,
			IntersectState &state,
			const TraceParams::SceneParam &param
			) const
	{
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

#endif // PLANE_H
