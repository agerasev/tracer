#ifndef TRANSPARENTMATERIAL_H
#define TRANSPARENTMATERIAL_H

#include<cmath>

#include<render/material.h>

#include<4u/util/op.hpp>
#include<4u/util/const.hpp>

class TransparentMaterial : public virtual Material
{
private:
	Color color;
	double factor;

public:
	TransparentMaterial(double n, const Color &col = Color(1,1,1))
		: color(col), factor(n)
	{

	}

	/* Returns glow color and adds secondary rays */
	virtual Color trace(
			const Ray &ray,
			const vec3 &point,
			const vec3 &normal,
			std::function<void(Ray &&)> add,
			const SceneParams &,
			ContRand &,
			double weight = 1.0
			) const
	{
		if(ray.mask & Ray::REFRACT)
		{
			double cosa = ray.direction*normal;
			vec3 fp = ray.direction - cosa*normal;
			vec3 rp;
			if(cosa > 0.0)
			{
				rp = fp*factor;
			}
			else
			{
				rp = fp/factor;
			}
			if(sqr(rp) < 1.0)
			{
				vec3 dir = rp + normal*sgn(cosa)*sqrt(1.0 - sqr(rp));
				add(
							Ray(
								point,
								dir,
								weight*(color * ray.color),
								ray.mask,
								(!(ray.flag & Ray::INSIDE))*Ray::INSIDE | Ray::REFRACT
								)
							);
			}
		}
		return BLACK;
	}

	/* Casts secondary ray to given direction */
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
		return Ray::REFRACT;
	}
};

#endif // TRANSPARENTMATERIAL_H
