#ifndef DIFFUSEMATERIAL_H
#define DIFFUSEMATERIAL_H

#include<4u/rand/sphericrand.hpp>

#include<render/material.h>
#include<render/ray.h>

#include<iostream>

class DiffuseMaterial : public Material
{
private:
	Color color;

public:
	DiffuseMaterial(const Color &c)
		: Material(), color(c)
	{

	}

	virtual vec3 getReflection(
			const vec3 &,
			const vec3 &n,
			ContRand &rand
			) const
	{
		return SemiSphericCosineRand::wrap(rand,n);
	}

	Color getColor() const
	{
		return color;
	}

	/* Returns glow color and adds secondary rays */
	virtual Color trace(
			const Ray &ray,
			const vec3 &point,
			const vec3 &normal,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand,
			double weight = 1.0
			) const
	{
		if(ray.mask & Ray::DIFFUSE)
		{
			for(int i = 0; i < params.diffuse_rays; ++i)
			{
				vec3 dir = getReflection(ray.direction,normal,rand);
				add(
					Ray(
						point,
						dir,
						(getColor()*ray.color)/params.diffuse_rays*weight,
						ray.mask,
						Ray::DIFFUSE
						)
					);
			}
		}
		return BLACK;
	}

	virtual void cast(
			const Ray &ray,
			const vec3 &point,
			const vec3 &normal,
			const vec3 &dir,
			double prob,
			std::function<void(Ray &&)> add,
			const SceneParams &,
			ContRand &,
			double weight = 1.0
			) const
	{
		if(ray.mask & Ray::DIFFUSE)
		{
			double cos_theta = dir*normal;
			if(cos_theta > 0.0)
			{
				add(Ray(
						point,
						dir,
						2.0*(getColor()*ray.color)*cos_theta*prob*weight,
						ray.mask,
						Ray::DIFFUSE | Ray::CAST
						));
			}
		}
	}

	/* Returns kind of interaction as bitfield */
	virtual unsigned int getInteractionKind() const
	{
		return Ray::DIFFUSE;
	}
};

#endif // DIFFUSEMATERIAL_H
