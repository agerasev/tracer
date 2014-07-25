#ifndef SPHERE_H
#define SPHERE_H

#include<cmath>
#include<vector>

#include<tracer/object.h>

class Sphere : public Object
{
private:
	double radius;

public:
	class SphereIntersectState : public IntersectState
	{
	public:
		vec3 point;
		double entry;
	};

	Sphere(const vec3 &pos, double rad) : Object(pos)
	{
		radius = rad;
	}
	virtual ~Sphere() {

	}

	virtual double getSize() const
	{
		return radius;
	}

	virtual bool intersect(const Ray &ray, vec3 &point, const TraceParams::SceneParam &param, IntersectState *&state) const
	{
		double closest = (getPosition() - ray.start)*ray.direction;
		if(closest < 0.0) {
			return false;
		}
		double dist2 = sqr(getPosition() - (ray.direction*closest + ray.start));
		if(dist2 > radius*radius) {
			return false;
		}
		double entry = closest - sqrt(radius*radius - dist2);
		if(entry < 0.0) {
			return false;
		}

		SphereIntersectState *local_state = new SphereIntersectState();

		local_state->entry = entry;
		point = local_state->point = ray.start + ray.direction*entry;
		state = local_state;

		return true;
	}

	virtual std::vector<Ray> trace(const Ray &ray, vec4 &ret, const TraceParams::SceneParam &param, IntersectState *&state) const
	{
		SphereIntersectState *restored_state = static_cast<SphereIntersectState*>(state);

		vec3 normal = (restored_state->point - getPosition())/radius;
		vec3 refldir = ray.direction - (2.0*normal*ray.direction)*normal;

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

		std::vector<Ray> beam;
		beam.push_back(Ray(restored_state->point,refldir));

		ret = nullvec4;
	}

	virtual void forget(IntersectState *&state) const
	{
		delete state;
		state = nullptr;
	}
};

#endif // SPHERE_H
