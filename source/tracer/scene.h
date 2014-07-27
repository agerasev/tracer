#ifndef SCENE_H
#define SCENE_H

#include<list>

#include<object/object.h>
#include"ray.h"
#include"traceparams.h"

class Scene
{
private:
	std::list<Object*> container;

public:
	/* Methods for objects placing */
	void add(Object *obj)
	{
		container.push_back(obj);
	}
	void remove(Object *obj)
	{
		container.remove(obj);
	}
	std::list<Object*>::iterator begin()
	{
		return container.begin();
	}
	std::list<Object*>::iterator end()
	{
		return container.end();
	}

public:
	vec4 trace(const std::vector<Ray> &in, std::vector<Ray> &out, const TraceParams::SceneParam &param)
	{
		vec4 color = nullvec4;
		for(const Ray &r : in)
		{
			color += traceRay(r,out,param);
		}
		return color;
	}

private:
	vec4 traceRay(const Ray &ray, std::vector<Ray> &out, const TraceParams::SceneParam &param)
	{
		double record = 0.0;
		Object *target = nullptr;
		Object::IntersectState target_state;

		for(Object *obj : container)
		{
			Object::IntersectState state;

			if(obj->intersect(ray,state,param))
			{

				double dist = (state.point - ray.start)*ray.direction;

				if(dist < record || target == nullptr)
				{
					record = dist;
					target = obj;
					target_state = state;
				}
			}
		}

		if(target != nullptr)
		{
			return target->trace(ray,out,target_state,param);
		}

		return diffuse(ray.direction) & ray.color;
	}

	vec4 diffuse(const vec3 &dir) const
	{
		double col = 0.5 + 0.5*dir.y();
		return vec4(col,col,0.8*col + 0.2,1.0);
	}
};

#endif // SCENE_H
