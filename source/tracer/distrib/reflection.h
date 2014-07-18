#ifndef REFLECTION_H
#define REFLECTION_H

#include<cmath>

#include"../ray.h"
#include"../../util/random.h"
#include"../../util/vec.hpp"

#include"../material.h"

class Reflection
{
private:
    vec3 normal;
	vec3 reflection;
	double spec;

    vec3 nx, ny;

public:
	Reflection(const vec3 &n, const vec3 &r, double s) :
		normal(n), reflection(r), spec(s)
    {
        // generating basis for <normal,*> kernel
        if(vec3(0,0,1)*normal < 0.6 && vec3(0,0,1)*normal > -0.6)
        {
            nx = vec3(0,0,1);
        }
        else
        {
            nx = vec3(1,0,0);
		}
        ny = norm(nx^normal);
        nx = ny^normal;
	}
	vec3 cont() const
    {
        // getting continuous distribution
		double phi = Random::get(2*PI);
		double theta = acos(1.0 - Random::get());
        vec3 v = (nx*cos(phi) + ny*sin(phi))*sin(theta) + normal*cos(theta);

		return v;
	}
	vec3 direct(vec3 v) const
	{
		//setting divergence
		vec3 vr = (v*normal)/(reflection*normal)*reflection;
		vec3 vp = v - vr;
		vp = vp * (1.0 - spec);
		v = norm(vp + vr);

		return v;
	}
};

#endif // REFLECTION_H
