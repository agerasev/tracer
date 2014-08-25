#ifndef MATERIAL_H
#define MATERIAL_H

#include<vector>

#include"ray.h"
#include"params.h"

#include<4u/rand/contrand.hpp>

class Material
{
public:

	/* Returns glow color and adds secondary rays */
	virtual Color trace(
			const Ray &ray,
			const vec3 &point,
			const vec3 &normal,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand,
			double weight = 1.0
			) const = 0;

	/* Casts secondary ray to given direction */
	virtual void cast(
			const Ray &ray,
			const vec3 &point,
			const vec3 &normal,
			const vec3 &dir,
			double prob,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand,
			double weight = 1.0
			) const = 0;

	/* Returns kind of interaction as bitfield */
	virtual unsigned int getInteractionKind() const = 0;
};

#endif // MATERIAL_H
