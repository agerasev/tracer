#ifndef SPHERE_H
#define SPHERE_H

#include<cmath>
#include<vector>

#include"object.h"

#include"../distrib/reflection.h"

class Sphere : public Object
{
private:
	double radius;
	// temporary
	vec3 *point;
	double *entry;
	Material material;

public:

	Sphere(const vec3 &pos, double rad, const Color &c) : Object(pos)
	{
		radius = rad;
		point = new vec3();
		entry = new double();
		material.ambient = c;
		material.diffuse = Color(0.9,0,0);
		material.shininess = 0.0;
		material.emision = Color(0,0,0);
		material.specular = 0.2;
	}
	virtual ~Sphere() {
		delete point;
		delete entry;
	}

	virtual double size() const
	{
		return radius;
	}
	virtual bool collide(const Ray &ray, vec3 &pnt) const
	{
		double closest = (position - ray.start)*ray.direction;
		if(closest < 0.0) {
			return false;
		}
		double dist2 = sqr(position - (ray.direction*closest + ray.start));
		if(dist2 > radius*radius) {
			return false;
		}
		*entry = closest - sqrt(radius*radius - dist2);
		if(*entry < 0.0) {
			return false;
		}
		pnt = *point = ray.start + ray.direction**entry;
		return true;
	}
	virtual Color trace(const Ray &ray, std::vector<Ray> &buffer, int quality) const
	{
		vec3 normal = (*point - position)/radius;
		vec3 refldir = ray.direction - (2.0*normal*ray.direction)*normal;

		//diffuse
		if(material.shininess > 0.001) {
			buffer.push_back(Ray(*point, refldir, ray.color*material.diffuse*material.shininess));
		}
		//ambient
		if(material.shininess < 0.999) {
			Reflection reflection(normal,refldir,material.specular);
			for(int i = 0; i < 1<<quality; ++i) {
				vec3 v = reflection.get();
				buffer.push_back(Ray(*point,v,ray.color*material.ambient*(1.0 - material.shininess)/(1<<quality)));
			}
		}

		return ray.color*material.emision;
	}
};

#endif // SPHERE_H
