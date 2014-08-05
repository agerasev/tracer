#ifndef SCENE_H
#define SCENE_H

#include<list>

#include<object/object.h>
#include<object/attractor.h>

#include"ray.h"
#include"traceparams.h"

#include<4u/util/const.hpp>
#include<4u/rand/rand.hpp>

class Scene
{
private:
    std::list<Object*> objects;
	std::list<Attractor*> attractors;
public:
	/* Methods for objects placing */
    void addObject(Object *obj)
	{
        objects.push_back(obj);
	}
    void removeObject(Object *obj)
	{
        objects.remove(obj);
	}
    std::list<Object*> *getObjects()
    {
        return &objects;
    }

	/* Methods for attractors placing */
	void addAttractor(Attractor *obj)
    {
		attractors.push_back(obj);
    }
	void removeAttractor(Attractor *obj)
    {
		attractors.remove(obj);
    }
	std::list<Attractor*> *getAttractors()
	{
		return &attractors;
	}

public:
	vec4 trace(
			const std::vector<Ray> &in,
			std::vector<Ray> &out,
			const TraceParams::SceneParam &param,
			ContRand &rand
			) const
	{
		vec4 color = nullvec4;
		for(const Ray &r : in)
		{
			color += traceRay(r,out,param,rand);
		}
		return color;
	}

private:
	vec4 traceRay(
			const Ray &ray,
			std::vector<Ray> &out,
			const TraceParams::SceneParam &param,
			ContRand &rand
			) const
	{
		double record = 0.0;
		Object *target = nullptr;
		Object::IntersectState target_state;

        for(Object *obj : objects)
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
			std::vector< std::pair<vec3,double> > force_dir;
			if(target->isAttractive())
			{
				for(Attractor *emi : attractors)
				{
					emi->attract(target_state.point,force_dir,param,rand);
				}
			}
			return target->trace(ray,out,target_state,force_dir,param,rand);
		}

		return diffuse(ray.direction) & ray.color;
	}

	vec4 diffuse(const vec3 &dir) const
	{
		// double col = 0.5 + 0.5*dir.y();
		// return vec4(col,col,0.8*col + 0.2,1.0);
		// return vec4(0.2,0.2,0.3,1);
		return vec4(0,0,0,1);
	}
};

#endif // SCENE_H
