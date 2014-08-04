#ifndef SPECTATOR_H
#define SPECTATOR_H

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>
#include<4u/rand/rand.hpp>

#include<object/object.h>
#include<tracer/ray.h>

#include<cmath>

/* Class starting raytracing */
class Spectator
{
public:
	/* Produces beam emitting from lens to scene */
	virtual void trace(
			const vec2 &pix,
			std::vector<Ray> &out,
			const TraceParams::SpectatorParam &params,
			ContRand &rand
			) const = 0;
};

#endif // SPECTATOR_H
