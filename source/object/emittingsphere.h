#ifndef EMITTINGSPHERE_H
#define EMITTINGSPHERE_H

#include"sphere.h"
#include"emitter.h"

#include<vector>
#include<utility>

#include<4u/la/vec.hpp>
#include<4u/util/op.hpp>
#include<4u/rand/diskrand.h>

class EmittingSphere : public Sphere, public Emitter
{
private:
	vec4 glow;

public:
	EmittingSphere(const vec3 &pos, double rad, const Material *mat, const vec4 &g)
		: Sphere(pos,rad,mat), glow(g)
	{

	}

	virtual vec4 trace(
			const Ray &ray,
            std::vector<Ray> &out,
			const IntersectState &state,
			const std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand
			) const
	{
		return Sphere::trace(ray,out,state,fdir,param,rand) + (glow & ray.color);
	}

	virtual void attract(
			const vec3 &point,
			std::vector< std::pair<vec3,double> > &fdir,
			const TraceParams::SceneParam &param,
			ContRand &rand
			) const
	{
		vec3 dist = getPosition() - point;
		vec3 nrm = -norm(dist);
		double cosa = sqrt(1.0 - sqr(getRadius())/sqr(dist));
		double prob = 0.5*(1.0 - cosa);
		vec3 bx, by;
		if(sqr(by = nrm^vec3(0,0,1)) > 1e-12)
		{
            by = norm(by);
            bx = norm(by^dist);
		}
        else
        {
            bx = vec3(1,0,0);
            by = vec3(0,1,0);
        }
		double h = getRadius()*cosa;

		for(int i = 0; i < param.emitting_rays_density; ++i)
		{
            vec2 zeta = DiskRandStatic::wrap(rand);
            fdir.push_back(
                        std::pair<vec3,double>(
							norm(h*(zeta.x()*bx + zeta.y()*by) + (1.0 - sqr(getRadius())/sqr(dist))*dist),
                            prob
                            )
                        );
        }
	}
};

#endif // EMITTINGSPHERE_H
