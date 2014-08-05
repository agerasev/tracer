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
#include<object/attractingsphere.h>
#include<object/quad.h>

#include<material/specularanddiffusematerial.h>
#include<material/specularandtransparentmaterial.h>
#include<material/emittingmaterial.h>

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
		spect = new PointSpectator(nullvec3,unimat3,0.6,4.0,0.0);

		AttractingSphere *red = new AttractingSphere(
					vec3(0.6,-0.4,-3),
					0.6,
					new SpecularAndTransparentMaterial(0.1,1.4,vec4(1.0,0.4,0.4,1))
					);
		AttractingSphere *blue = new AttractingSphere(
					vec3(-0.6,-0.2,-4),
					0.8,
					new SpecularAndDiffuseMaterial(0.1,vec4(0.4,0.4,1.0,1))
					);
		scene.addAttractor(red);
		scene.addObject(red);
		//scene.addAttractor(blue);
		scene.addObject(blue);
		AttractingSphere *emi = new AttractingSphere(vec3(12,24,-16), 4.0, new EmittingMaterial(vec4(2e2,2e2,2e2,1)));
		scene.addAttractor(emi);
		scene.addObject(emi);

		vec3 qv[4] = {vec3(5,-1,-9),vec3(-5,-1,-9),vec3(-5,-1,1),vec3(5,-1,1)};
		scene.addObject(
					new Quad(
						qv,
						new DiffuseMaterial(vec4(0.4,0.4,0.4,1))
						)
					);
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
