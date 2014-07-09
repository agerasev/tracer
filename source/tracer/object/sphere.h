#ifndef SPHERE_H
#define SPHERE_H

#include<cmath>

#include"object.h"

class Sphere : public Object {
public:
	double radius;
	Sphere(const vec3 &pos = vec3(0,0,0), double rad = 1.0) : Object(pos) {
		radius = rad;
	}
	virtual double size() const {
		return radius;
	}
	virtual bool trace(const Ray &ray, vec3 &pnt, Beam &beam) const {
		double closest = (position - ray.start)*ray.direction;
		if(closest < 0.0) {
			return false;
		}
		double dist2 = sqr(position - (ray.direction*closest + ray.start));
		if(dist2 > radius*radius) {
			return false;
		}
		double entry = closest - sqrt(radius*radius - dist2);
		if(entry < 0.0) {
			return false;
		}
		pnt = ray.start + ray.direction*entry;
		beam = SingleRay(pnt,ray.direction + (2.0*(pnt - position)*ray.direction/radius)*ray.direction, ray.color);
		return true;
	}
};

#endif // SPHERE_H
