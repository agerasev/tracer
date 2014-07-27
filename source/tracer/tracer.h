#ifndef TRACER_H
#define TRACER_H

#include<render/render.h>
#include<4u/la/vec.hpp>

#include"traceparams.h"
#include"scene.h"
#include"spectator.h"

#include<object/object.h>
#include<object/sphere.h>

#include<material/specularmaterial.h>

class Tracer : public Render::Tracer {
private:
	Spectator spect;
	Scene scene;
	TraceParams params;
public:
	Tracer()
		: spect(nullvec3,unimat3,0.4)
	{
		params.scene.rays_density = 2;
		params.recursion_depth = 4;

		Material *m = new SpecularMaterial();

		for(int ix = 0; ix < 6; ++ix)
		{
			for(int iy = 0; iy < 4; ++iy)
			{
				for(int iz = 0; iz < 4; ++iz)
				{
					scene.add(new Sphere(vec3(ix - 2.5, iy - 1.5, iz - 7), 0.2, m));
				}
			}
		}
	}
	virtual vec4 trace(const vec2 &pix)
	{
		std::vector<Ray> buffer0, buffer1;
		std::vector<Ray> *src = &buffer0, *dst = &buffer1;

		/* Get initial beam */
		spect.trace(pix,*src,params.spectator);

		vec4 color = nullvec4;
		for(int i = 0; i < params.recursion_depth; ++i)
		{
			/* Raytrace */
			color += scene.trace(*src,*dst,params.scene);

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
