#ifndef ANISOTROPICDIFFUSEMATERIAL_H
#define ANISOTROPICDIFFUSEMATERIAL_H

#include"diffusematerial.h"

class AnisotropicDiffuseMaterial : public virtual DiffuseMaterial
{
private:
	double diffusion;

public:
	AnisotropicDiffuseMaterial(const vec4 &c, double d)
		: DiffuseMaterial(c,r), diffusion(d)
	{

	}

	virtual bool isAttractive() const
	{
		return true;
	}

	vec3 direct(const vec3 &diffuse_direction, const vec3 &direction, const vec3 &normal) const
	{
		//setting divergence
		vec3 vr = (diffuse_direction*normal)/(direction*normal)*direction;
		vec3 vp = diffuse_direction - vr;
		vp = vp * (1.0 - diffusion);
		return norm(vp + vr);
	}

	virtual vec3 getReflection(const vec3 &d, const vec3 &n) const
	{
		return direct(DiffuseMaterial::getReflection(d,n), d - (2.0*n*d)*n ,n);
	}

	virtual vec4 trace(
			const Ray &ray,
			std::vector<Ray> &out,
			const Object::IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand,
			double weight = 1.0
			) const
	{

		for(int i = 0; i < param.rays_density; ++i)
		{
			out.push_back(
						Ray(
							state.point,
							getReflection(ray.direction,state.normal),
							(getColor() & ray.color)/param.rays_density)
						);
		}

		return nullvec4;
	}
};

#endif // ANISOTROPICDIFFUSEMATERIAL_H
