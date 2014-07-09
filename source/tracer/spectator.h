#ifndef SPECTATOR_H
#define SPECTATOR_H

#include"../util/vec.hpp"
#include"../util/mat.hpp"

#include"object.h"
#include"ray.h"
#include"beam.h"

#include<cmath>

class Spectator
{
public:
	vec3 position;
	mat3 orientation;

	double fov;

	Spectator(const vec3 &pos = vec3(0,0,0), const mat3 &ori = mat3(1), double afov = 0.4) :
		position(pos), orientation(ori), fov(afov) {}

	Ray trace(double x, double y) {
		vec3 dir = orientation*vec3(0,0,-1) + orientation*(fov*vec3(x,y,0));
		//vec3 dir = orientation*(vec3(sin(fov*x)*cos(fov*y),sin(fov*y),-cos(fov*x)*cos(fov*y)));
		dir = dir/sqrt(dir*dir);
		return Ray(position,dir);
	}
};

#endif // SPECTATOR_H
