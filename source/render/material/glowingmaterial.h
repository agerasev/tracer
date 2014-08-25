#ifndef GLOWINGMATERIAL_H
#define GLOWINGMATERIAL_H

#include<render/material.h>

class GlowingMaterial : public Material
{
private:
	Color glow;

public:
	GlowingMaterial(const Color &g)
		: glow(g)
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
		if(Ray::GLOW & ray.mask)
		{
			return glow;
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
		return Ray::GLOW;
	}
};

#endif // GLOWINGMATERIAL_H
