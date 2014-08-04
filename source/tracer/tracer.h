#ifndef TRACER_H
#define TRACER_H

#include<vector>

//#include<render/render.h>
#include<4u/la/vec.hpp>
#include<4u/rand/rand.hpp>
#include<4u/util/op.hpp>

#include"traceparams.h"
#include"scene.h"
#include<spectator/pointspectator.h>

#include<object/object.h>
#include<object/sphere.h>
#include<object/emittingsphere.h>
#include<object/quad.h>

#include<material/specularanddiffusematerial.h>
#include<material/absorbingmaterial.h>

class Tracer
{
private:
	Spectator *spect;
	Scene scene;
	const TraceParams params;
public:
	Tracer(const TraceParams p)
		: params(p)
	{
		spect = new PointSpectator(nullvec3,unimat3,0.6,6.0,0.06);

		scene.addObject(new Sphere(vec3(-1.0,0,-6), 1.0, new DiffuseMaterial(vec4(0.8,0.2,0.2,1))));
		scene.addObject(new Sphere(vec3(1.0,0,-6), 1.0, new DiffuseMaterial(vec4(0.2,0.2,0.8,1))));
		scene.addObject(new Sphere(vec3(0.2,-0.6,-2), 0.4, new DiffuseMaterial(vec4(0.2,0.8,0.2,1))));
		EmittingSphere *emi = new EmittingSphere(vec3(12,24,-16), 4.0, new AbsorbingMaterial(), vec4(2e2,2e2,2e2,1));
		scene.addEmitter(emi);
		scene.addObject(emi);

		vec3 qv[4] = {vec3(5,-1,-9),vec3(-5,-1,-9),vec3(-5,-1,1),vec3(5,-1,1)};
		scene.addObject(
					new Quad(
						qv,
						new DiffuseMaterial(vec4(0.4,0.4,0.4,1))
						)
					);

		/*
		for(int ix = 0; ix < 3; ++ix)
		{
			for(int iy = 0; iy < 2; ++iy)
			{
				for(int iz = 0; iz < 4; ++iz)
				{
					scene.add(new Sphere(vec3(ix - 1, iy - 0.5, iz - 6), 0.2, m));
				}
			}
		}
		*/
	}
	virtual vec4 trace(const vec2 &pix, ContRand &rand) const
	{
		std::vector<Ray> buffer0, buffer1;

		int max_rays = _pow(params.scene.rays_density,params.recursion_depth);
		buffer0.reserve(max_rays);
		buffer1.reserve(max_rays);

		std::vector<Ray> *src = &buffer0, *dst = &buffer1;

		/* Get initial beam */
		spect->trace(pix,*src,params.spectator,rand);

		vec4 color = nullvec4;
		for(int i = 0; i < params.recursion_depth; ++i)
		{
			/* Raytrace */
			color += scene.trace(*src,*dst,params.scene,rand);

			/* Clear src */
			src->clear();

			/* Swap buffers */
			std::vector<Ray> *tmp = src;
			src = dst;
			dst = tmp;
		}
		return color;
	}
};

#endif // TRACER_H
