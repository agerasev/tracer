#ifndef ANISOTROPICDIFFUSEMATERIAL_H
#define ANISOTROPICDIFFUSEMATERIAL_H

#include"diffusematerial.h"

class AnisotropicDiffuseMaterial : public DiffuseMaterial
{
private:
	double diffusion;

public:
	AnisotropicDiffuseMaterial(const Color &c, double d)
		: DiffuseMaterial(c), diffusion(d)
	{

	}

	vec3 direct(const vec3 &diffuse_direction, const vec3 &direction, const vec3 &normal) const
	{
		//setting divergence
		vec3 vr = (diffuse_direction*normal)/(direction*normal)*direction;
		vec3 vp = diffuse_direction - vr;
		vr = vr * diffusion;
		return norm(vp + vr);
	}

	vec3 indirect(const vec3 &diffuse_direction, const vec3 &direction, const vec3 &normal) const
	{
		//setting divergence
		vec3 vr = (diffuse_direction*normal)/(direction*normal)*direction;
		vec3 vp = diffuse_direction - vr;
		vr = vr * 1.0/diffusion;
		return norm(vp + vr);
	}

	virtual vec3 getReflection(const vec3 &d, const vec3 &n, ContRand &rand) const
	{
		return direct(DiffuseMaterial::getReflection(d,n,rand), d - (2.0*n*d)*n ,n);
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
			vec3 indir = indirect(
						dir,
						ray.direction - (2.0*normal*ray.direction)*normal,
						normal
						);
			double cos_theta = indir*normal;
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

#endif // ANISOTROPICDIFFUSEMATERIAL_H
