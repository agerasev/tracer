#ifndef TRACER_H
#define TRACER_H

#include<vector>

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
	Tracer() :
		spect(vec3(0,0,0),mat3(1),0.2){
		scene.add(new Sphere(vec3(-1,0,-8),1.0,Color(0.9,0,0)));
		scene.add(new Sphere(vec3(0.5,0,-8),0.5,Color(0,0,0.9)));
	}
	virtual Color trace(double x, double y) {
		Color sum(0,0,0);

		std::vector<Ray> buffer0;
		std::vector<Ray> buffer1;

		std::vector<Ray> *src = &buffer0;
		std::vector<Ray> *dst = &buffer1;

		src->push_back(spect.trace(x,y));
		for(int i = 0; i < 0x10; ++i) {
			for(const Ray &r : *src) {
				sum = sum + scene.trace(r,*dst,4);
				src->clear();
				//swapping
				std::vector<Ray> *tmp = src;
				src = dst;
				dst = tmp;
			}
		}

		return sum;
	}
};

#endif // TRACER_H
