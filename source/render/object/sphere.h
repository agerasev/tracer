#ifndef SPHERE_H
#define SPHERE_H

#include<cmath>
#include<vector>

#include<4u/util/const.hpp>
#include<4u/util/op.hpp>

#include<render/object.h>
#include<render/attractor.h>
#include<render/emitter.h>
#include<render/material.h>

class Sphere : public Emitter
{
private:
	vec3 position;
	double radius;

public:
	Sphere(const vec3 &pos, double rad) :
		position(pos),
		radius(rad)
	{

	}
	virtual ~Sphere() {

	}

	double getRadius() const
	{
		return radius;
	}

	virtual vec3 getPosition() const
	{
		return position;
	}

	virtual double getSize() const
	{
		return radius;
	}

	virtual bool intersect(
			const Ray &ray,
			Intersection &state,
			const SceneParams &,
			ContRand &
			) const
	{
		vec3 start = ray.start, direction = ray.direction;

		double closest = (getPosition() - start)*direction;
		/*
		if(closest < 0.0) {
			return false;
		}
		*/
		double dist2 = sqr(getPosition() - (direction*closest + start));
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

		state.distance = entry;
		state.point = start + direction*entry;
		state.normal = (state.point - getPosition())/radius;

		return true;
	}

	virtual void attract(
			const vec3 &point,
			std::function<void(const vec3 &, double)> add,
			const SceneParams &params,
			ContRand &rand
			) const
	{
		const int density = params.emitting_rays;
		vec3 dist = getPosition() - point;
		vec3 nrm = -norm(dist);
		double cosa = sqrt(1.0 - sqr(getRadius())/sqr(dist));
		double prob = 0.5*(1.0 - cosa*cosa);
		vec3 bx, by;
		if(sqr(by = nrm^vec3(0,0,1)) > 1e-12)
		{
			by = norm(by);
			bx = norm(by^dist);
		}
		else
		{
			bx = vec3(1,0,0);
			by = vec3(0,1,0);
		}
		double h = getRadius()*cosa;

		for(int i = 0; i < density; ++i)
		{
			vec2 zeta = DiskRand::wrap(rand);
			add(
				norm(h*(zeta.x()*bx + zeta.y()*by) + (1.0 - sqr(getRadius())/sqr(dist))*dist),
				prob/density
			   );
		}
	}

	/* Emites rays from emitter to given point */
	/*
	virtual void cast(
			const vec3 &point,
			std::function<void(const Ray &)> &add,
			const SceneParams &params,
			ContRand &rand
			) const
	{
		const int density = params.emitting_rays;
		vec3 dist = getPosition() - point;
		vec3 nrm = -norm(dist);
		double cosa = sqrt(1.0 - sqr(getRadius())/sqr(dist));
		double prob = 0.5*(1.0 - cosa);
		vec3 bx, by;
		if(sqr(by = nrm^vec3(0,0,1)) > 1e-12)
		{
			by = norm(by);
			bx = norm(by^dist);
		}
		else
		{
			bx = vec3(1,0,0);
			by = vec3(0,1,0);
		}
		double h = getRadius()*cosa;

		for(int i = 0; i < density; ++i)
		{
			vec2 zeta = DiskRand::wrap(rand);
			vec3 dir = h*(zeta.x()*bx + zeta.y()*by) - (sqr(getRadius())/sqr(dist))*dist;
			add(
				Ray(
					getPosition(),
					-norm(h*(zeta.x()*bx + zeta.y()*by) + (1.0 - sqr(getRadius())/sqr(dist))*dist),
					prob/density,
					this
					)
				);
		}
	}
	*/

	/* Illuminates given object */
	/*
	virtual void illuminate(
			const Object *obj,
			std::function<void(const Ray &)> &add,
			const SceneParams &params,
			ContRand &rand
			) const
	{

	}
	*/
};

#endif // SPHERE_H
