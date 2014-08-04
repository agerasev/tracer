#ifndef EMITTER_H
#define EMITTER_H

#include<utility>

#include<4u/la/vec.hpp>
#include<4u/rand/contrand.hpp>

class Emitter
{
public:
	/* Returns vector directed to emitter from given point
	 * and sets the solid angle of himself viewed from this point */
	virtual void attract(
			const vec3 &point,
            std::vector<std::pair<vec3,double>> &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand
			) const = 0;
};

#endif // EMITTER_H
