#ifndef SPECTATOR_H
#define SPECTATOR_H

#include<cmath>
#include<vector>

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>
#include<4u/rand/contrand.hpp>

#include<render/params.h>
#include<render/ray.h>

/* Class starting raytracing */
class Spectator
{
public:
	/* Produces beam emitting from lens to scene */
	virtual Ray cast(
			const vec2 &pixel,
			const SceneParams &params,
			ContRand &rand
			) const = 0;
};

#endif // SPECTATOR_H
