#ifndef SPECULARMATERIAL_H
#define SPECULARMATERIAL_H

#include<render/material.h>
#include<4u/la/vec.hpp>

class SpecularMaterial : public Material
{
private:
	Color color;

public:
	SpecularMaterial(const Color &col = Color(1,1,1))
		: color(col)
	{

	}

	virtual vec3 getReflection(
			const vec3 &d,
			const vec3 &n,
			ContRand &
			) const
	{
		return d - (2.0*n*d)*n;
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
			const SceneParams &,
			ContRand &rand,
			double weight = 1.0
			) const
	{
		if(ray.mask & Ray::REFLECT)
		{
			add(
				Ray(
					point,
					getReflection(ray.direction, normal, rand),
					weight*(getColor()*ray.color),
					ray.mask,
					Ray::REFLECT
					)
				);
		}
		return Color(0,0,0);
	}

	virtual void cast(
			const Ray &,
			const vec3 &,
			const vec3 &,
			const vec3 &,
			double,
			std::function<void(Ray &&)>,
			const SceneParams &,
			ContRand &,
			double
			) const
	{

	}

	/* Returns kind of interaction as bitfield */
	virtual unsigned int getInteractionKind() const
	{
		return Ray::REFLECT;
	}
};

#endif // SPECULARMATERIAL_H
