#ifndef SPHERE_H
#define SPHERE_H

#include<cmath>
#include<vector>

#include<4u/util/const.hpp>
#include<4u/util/op.hpp>

#include<object/object.h>

#include<material/material.h>

class Sphere : public Object
{
private:
	double radius;
	const Material *material = nullptr;
public:
	Sphere(const vec3 &pos, double rad, const Material *mat) : Object(pos)
	{
		radius = rad;
		material = mat;
	}
	virtual ~Sphere() {

	}

	double getRadius() const
	{
		return radius;
	}

	/*
	virtual double getSize() const
	{
		return radius;
	}
	*/

	virtual bool isAttractive() const
	{
		return material->isAttractive();
	}

	virtual bool intersect(
			const Ray &ray,
			IntersectState &state,
			const TraceParams::SceneParam &param
			) const
	{
		double closest = (getPosition() - ray.start)*ray.direction;
		/*
		if(closest < 0.0) {
			return false;
		}
		*/
		double dist2 = sqr(getPosition() - (ray.direction*closest + ray.start));
		if(dist2 > sqr(radius)) {
			return false;
		}
		double entry;
		if(ray.flag & Ray::INSIDE)
		{
			entry = closest + sqrt(sqr(radius) - dist2);
		}
		else
		{
			entry = closest - sqrt(sqr(radius) - dist2);
		}
		if(entry < 0.0) {
			return false;
		}

		state.point = ray.start + ray.direction*entry;
		state.normal = (state.point - getPosition())/radius;

		return true;
	}

	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
            ContRand &rand
			) const
	{
		return material->trace(ray,out,state,fdir,param,rand);
	}
};

#endif // SPHERE_H
