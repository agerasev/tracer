#ifndef SCENE_H
#define SCENE_H

#include<list>
using namespace std;

#include"object.h"
#include"ray.h"
#include"beam.h"

class Scene
{
private:
	list<Object*> container;
public:
	void add(Object *obj) {
		container.push_back(obj);
	}
	void remove(Object *obj) {
		container.remove(obj);
	}
	list<Object*>::iterator begin() {
		return container.begin();
	}
	list<Object*>::iterator end() {
		return container.end();
	}
	bool trace(const Ray &ray, Beam &beam) {
		bool hit = false;
		double record = 0.0;
		for(Object *obj : container) {
			vec3 pnt;
			Beam lbm;
			if(obj->trace(ray,pnt,lbm)) {
				double dist = (pnt - ray.start)*ray.direction;
				if(dist < record || !hit) {
					record = dist;
					beam = lbm;
					hit = true;
				}
			}
		}
		return hit;
	}
};

#endif // SCENE_H
