#ifndef SCENE_H
#define SCENE_H

#include<list>
#include<vector>

#include"object.h"
#include"ray.h"

class Scene
{
private:
	std::list<Object*> container;
	Color diffuse = Color(1,1,1);
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
	Color trace(const Ray &ray, std::vector<Ray> &buffer, int quality) {
		double record = 0.0;
		Object *target = nullptr;
		for(Object *obj : container) {
			vec3 pnt;
			if(obj->collide(ray,pnt)) {
				double dist = (pnt - ray.start)*ray.direction;
				if(dist < record || target == nullptr) {
					record = dist;
					target = obj;
				}
			}
		}
		if(target != nullptr) {
			return target->trace(ray,buffer,quality);
		}
		return diffuse*ray.color;
	}
};

#endif // SCENE_H
