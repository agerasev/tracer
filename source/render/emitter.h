#ifndef EMITTER_H
#define EMITTER_H

#include<vector>

#include"params.h"
#include"ray.h"
#include"attractor.h"

#include<4u/la/vec.hpp>
#include<4u/rand/contrand.hpp>

class Emitter : public Attractor
{
public:
	/* Emites rays from emitter to given point */
	/*
	virtual void emit(
			const vec3 &point,
			std::function<void(const Ray &)> &add,
			const SceneParams &params,
			ContRand &rand
			) const = 0;
	*/
	/* Illuminates given object */
	/*
	virtual void illuminate(
			const Attractor *obj,
			std::function<void(const Ray &)> &add,
			const SceneParams &params,
			ContRand &rand
			) const = 0;
	*/
};

#endif // EMITTER_H
