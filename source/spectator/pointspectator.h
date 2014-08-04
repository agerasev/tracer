#ifndef POINTSPECTATOR_H
#define POINTSPECTATOR_H

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>
#include<4u/rand/diskrand.hpp>

#include<object/object.h>
#include<tracer/ray.h>

#include"spectator.h"

#include<cmath>

class PointSpectator : public Spectator
{
public:
	vec3 position;
	mat3 orientation;

	double fov;		/* field of view */
	double focus;	/* distance to focal plane */
	double radius;	/* lens radius */

	PointSpectator(
			const vec3 &pos = nullvec3,
			const mat3 &ori = unimat3,
			double afov = 0.4,
			double foc = 4.0,
			double rad = 0.2
			) :
		position(pos),
		orientation(ori),
		fov(afov),
		focus(foc),
		radius(rad)
	{

	}

	virtual void trace(
			const vec2 &pix,
			std::vector<Ray> &out,
			const TraceParams::SpectatorParam &params,
			ContRand &rand
			) const
	{

		/* plain lens, plain matrix */
		vec3 dir = orientation*vec3(0,0,-1) + orientation*(fov*vec3(pix.x(),pix.y(),0));

		/* plain lens, spheric matrix */
		//vec3 dir = orientation*(vec3(sin(fov*x)*cos(fov*y),sin(fov*y),-cos(fov*x)*cos(fov*y)));

		/* TODO: add spheric lens, spheric matrix for spheric view */

		vec3 foc = dir*focus;

		for(int i = 0; i < params.rays_density; ++i)
		{
			vec2 ex2d = radius*DiskRand::wrap(rand);
			vec3 ex3d = orientation*(vec3(ex2d.x(),ex2d.y(),0));
			vec3 ldir = norm(foc - ex3d);
			out.push_back(Ray(position + ex3d, ldir, vec4(1,1,1,1)/params.rays_density, true));
		}
	}
};

#endif // POINTSPECTATOR_H
