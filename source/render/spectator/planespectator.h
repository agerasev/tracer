#ifndef PLANESPECTATOR_H
#define PLANESPECTATOR_H

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>
#include<4u/rand/diskrand.hpp>

#include<render/ray.h>
#include<render/spectator.h>

#include<cmath>

class PlaneSpectator : public Spectator /* + public Attractor */
{
private:
	vec3 position;
	mat3 orientation;

	double fov;		/* field of view */
	double focus;	/* distance to focal plane */
	double radius;	/* lens radius */

public:
	PlaneSpectator(
			const vec3 &pos = nullvec3,
			const mat3 &ori = unimat3,
			double afov = 0.4,
			double foc = 1.0,
			double rad = 0.0
			) :
		position(pos),
		orientation(ori),
		fov(afov),
		focus(foc),
		radius(rad)
	{

	}

	virtual Ray cast(
			const vec2 &pix,
			const SceneParams &,
			ContRand &rand
			) const
	{
		/* plain lens, plain matrix */
		vec3 dir = orientation*vec3(0,0,-1) + orientation*(fov*vec3(pix.x(),pix.y(),0));

		/* plain lens, spheric matrix */
		//vec3 dir = orientation*(vec3(sin(fov*x)*cos(fov*y),sin(fov*y),-cos(fov*x)*cos(fov*y)));

		/* TODO: add spheric lens, spheric matrix for spheric view */

		vec3 foc = dir*focus;

		vec2 ex2d = radius*DiskRand::wrap(rand);
		vec3 ex3d = orientation*(vec3(ex2d.x(),ex2d.y(),0));
		vec3 ldir = norm(foc - ex3d);

		return Ray(
					position + ex3d,
					ldir,
					Color(1,1,1),
					Ray::DIFFUSE | Ray::REFLECT | Ray::REFRACT | Ray::DEPRESS | Ray::EMIT | Ray::GLOW,
					0
					);
	}
};

#endif // PLANESPECTATOR_H
