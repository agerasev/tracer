#ifndef EMITTINGMATERIAL_H
#define EMITTINGMATERIAL_H

#include<render/material.h>

class EmittingMaterial : public Material
{
private:
	Color color;

public:
	EmittingMaterial(const Color &c) :
		color(c)
	{

	}

	virtual Color trace(
			const Ray &ray,
			const vec3 &,
			const vec3 &,
			std::function<void(Ray &&)>,
			const SceneParams &,
			ContRand &,
			double
			) const
	{
		if(Ray::EMIT & ray.mask)
		{
			return color;
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

	virtual unsigned int getInteractionKind() const
	{
		return Ray::EMIT;
	}
};

#endif // EMITTINGMATERIAL_H
