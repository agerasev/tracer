#ifndef SCENE_H
#define SCENE_H

#include<list>

#include"object.h"
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
	/* Recursive raytraces scene */
	vec4 trace(const std::vector<Ray> &beam, const TraceParams::SceneParam &param, int recurse = 0)
	{
		if(recurse >= param.recursion_depth)
		{
			return nullvec4;
		}
		vec4 color = nullvec4;
		for(const Ray &r : beam)
		{
			color += traceRay(r,param,recurse);
		}
		return color;
	}

private:
	vec4 traceRay(const Ray &ray, const TraceParams::SceneParam &param, int recurse)
	{
		double record = 0.0;
		Object *target = nullptr;
		Object::IntersectState *target_state = nullptr;

		for(Object *obj : container)
		{

			Object::IntersectState *state = nullptr;
			vec3 point;

			if(obj->intersect(ray,point,param,state))
			{

				double dist = (point - ray.start)*ray.direction;

				if(dist < record || target == nullptr)
				{
					record = dist;
					if(target != nullptr)
					{
						target->forget(target_state);
					}
					target = obj;
					target_state = state;
				}
				else
				{
					obj->forget(state);
				}
			}
		}

		vec4 color;
		if(target != nullptr)
		{
			//std::vector<Ray> beam = target->trace(ray,color,param,target_state);

			target->forget(target_state);

			/* Recursively call tracing */
			trace(target->trace(ray,color,param,target_state), param, recurse + 1);

		}
		else
		{
			color = diffuse(ray.direction);
		}

		return color & ray.color;
	}

	vec4 diffuse(const vec3 &dir) const
	{
		double col = dir.y()*dir.y();
		return vec4(col,col,0.8*col + 0.2,1.0);
	}
};

#endif // SCENE_H
