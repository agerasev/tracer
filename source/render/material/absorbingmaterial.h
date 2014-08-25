#ifndef ABSORBINGMATERIAL_H
#define ABSORBINGMATERIAL_H

#include<render/material.h>

class AbsorbingMaterial : public Material
{
public:
	/* Returns glow color and adds secondary rays */
	virtual Color trace(
			const Ray &,
			const vec3 &,
			const vec3 &,
			std::function<void(Ray &&)> ,
			const SceneParams &,
			ContRand &rand,
			double
			) const
	{
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
		return 0;
	}
};

#endif // ABSORBINGMATERIAL_H
