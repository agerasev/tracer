#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include<functional>

#include"distanceobject.h"

class Functional : public DistanceObject
{
private:
	std::function<double(const vec3 &)> func;

public:
	Functional(const vec3 &p, double r, std::function<double(const vec3 &)> f) :
		DistanceObject(p,r,0.1,1e-4,1.0),
		func(f)
	{

	}

	virtual double getDistance(const vec3 &pos) const
	{
		return func(pos);
	}

	// Some functions
	static double sphere(const vec3 &pos) { return length(pos) - 1.0; }
	static double displacement(const vec3 &pos) { return sin(pos.x())*sin(pos.y())*sin(pos.z()); }
	static double torus(const vec3 &pos, double width = 0.25) {
		return length(vec2(length(vec2(pos.x(),pos.z())) - 1.0, pos.y())) - width;
	}
	static double smin(double a, double b, double k = 32)
	{
		return -log(exp( -k*a ) + exp( -k*b ))/k;
	}
};

#endif // FUNCTIONAL_H
