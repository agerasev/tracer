#ifndef TRACER_H
#define TRACER_H

#include"../renderer/renderer.h"
#include"../util/color.hpp"

#include"scene.h"
#include"spectator.h"

#include"object/sphere.h"

class Tracer : public Renderer::Tracer {
private:
	Scene scene;
	Spectator spect;
public:
	Tracer() {
		scene.add(new Sphere(vec3(0,0,-8)));
		scene.add(new Sphere(vec3(1,1,-6),0.5));
	}
	virtual Color trace(double x, double y) {
		Beam beam;
		if(scene.trace(spect.trace(x,y),beam)) {
            return Color(1,1,1,1);
		}
		return Color(0,0,0,1);
	}
};

#endif // TRACER_H
