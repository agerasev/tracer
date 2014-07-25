#ifndef SPECTATOR_H
#define SPECTATOR_H

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>

#include"object.h"
#include"ray.h"

#include<cmath>

/* Class starting raytracing */
class Spectator
{
public:
	vec3 position;
	mat3 orientation;

	double fov;

	Spectator(const vec3 &pos = nullvec3, const mat3 &ori = unimat3, double afov = 0.4) :
		position(pos), orientation(ori), fov(afov) {}

	/* Produces beam emitting from lens to scene */
	std::vector<Ray> beam(const vec2 &pix, const TraceParams::SpectatorParam &params) {

		/* plain lens, plain matrix */
		vec3 dir = orientation*vec3(0,0,-1) + orientation*(fov*vec3(pix.x(),pix.y(),0));

		/* plain lens, spheric matrix */
		//vec3 dir = orientation*(vec3(sin(fov*x)*cos(fov*y),sin(fov*y),-cos(fov*x)*cos(fov*y)));

		/* TODO: add spheric lens, spheric matrix for spheric view
		 * Inherit from this class, make it abstract */

		dir = dir/sqrt(dir*dir);

		/* Now there is only one ray, but it needs to be
		 * many rays for depth effect */
		std::vector<Ray> beam;
		beam.push_back(Ray(position,dir));

		return beam;
	}
};

#endif // SPECTATOR_H
