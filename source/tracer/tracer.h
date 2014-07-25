#ifndef TRACER_H
#define TRACER_H

#include<render/render.h>
#include<4u/la/vec.hpp>

#include"traceparams.h"
#include"scene.h"
#include"spectator.h"

#include"object.h"
#include<object/sphere.h>

class Tracer : public Render::Tracer {
private:
	Spectator spect;
	Scene scene;
	TraceParams params;
public:
	Tracer()
		: spect(nullvec3,unimat3,0.6)
	{
		params.scene.rays_density = 2;
		params.scene.recursion_depth = 1;

		scene.add(new Sphere(vec3(0,0,-4),1));
	}
	virtual vec4 trace(const vec2 &pix)
	{
		return scene.trace(spect.beam(pix,params.spectator),params.scene);
	}
};

#endif // TRACER_H
