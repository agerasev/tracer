#ifndef POINTSPECTATOR_H
#define POINTSPECTATOR_H

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>
#include<4u/rand/diskrand.hpp>

#include<render/ray.h>
#include<render/spectator.h>

#include<cmath>

class PointSpectator : public Spectator
{
private:
	vec3 position;
	mat3 orientation;
	double fov;		/* field of view */

public:
	PointSpectator(
			const vec3 &pos = nullvec3,
			const mat3 &ori = unimat3,
			double afov = 0.4
			) :
		position(pos),
		orientation(ori),
		fov(afov)
	{

	}

	virtual Ray cast(
			const vec2 &pix,
			const SceneParams &,
			ContRand &
			) const
	{
		/* plain lens, plain matrix */
		vec3 dir = norm(orientation*vec3(0,0,-1) + orientation*(fov*vec3(pix.x(),pix.y(),0)));

		return Ray(
					position,
					dir,
					Color(1,1,1),
					Ray::DIFFUSE | Ray::REFLECT | Ray::REFRACT | Ray::DEPRESS | Ray::EMIT | Ray::GLOW,
					0
					);
	}
};

#endif // POINTSPECTATOR_H
