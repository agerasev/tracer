#ifndef TRANSPARENTMATERIAL_H
#define TRANSPARENTMATERIAL_H

#include<cmath>

#include"material.h"

#include<4u/util/op.hpp>
#include<4u/util/const.hpp>

class TransparentMaterial : public virtual Material
{
private:
	vec4 color;
	double factor;

public:
	TransparentMaterial(double n, const vec4 &col = vec4(1,1,1,1))
		: factor(n), color(col)
	{

	}

	virtual bool isAttractive() const
	{
		return false;
	}

	vec4 getColor() const
	{
		return color;
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
		double cosa = ray.direction*state.normal;
		vec3 fp = ray.direction - cosa*state.normal;
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
			vec3 dir = rp + state.normal*sgn(cosa)*sqrt(1.0 - sqr(rp));
			out.push_back(
						Ray(
							state.point,
							dir,
							weight*(getColor() & ray.color),
							ray.flag ^ Ray::INSIDE
							)
						);
		}
		return nullvec4;
	}
};

#endif // TRANSPARENTMATERIAL_H
