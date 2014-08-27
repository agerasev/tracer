#ifndef SCENE_H
#define SCENE_H

#include<list>
#include<utility>

#include"object.h"
#include"attractor.h"
#include"emitter.h"
#include"spectator.h"

#include<4u/util/const.hpp>
#include<4u/rand/rand.hpp>

#include"container/photonmap.h"

class Scene
{
private:
	std::list<Object*> objects;
	std::list<const Object*> const_objects;

	std::list<Attractor*> attractors;
	std::list<const Attractor*> const_attractors;

	std::list<Emitter*> emitters;
	std::list<const Emitter*> const_emitters;

	Spectator *spectator = nullptr;

	PhotonMap *photon_map = nullptr;

public:
	/* Methods for objects placing */
	void addObject(Object *obj)
	{
		objects.push_back(obj);
		const_objects.push_back(obj);
	}
	void removeObject(Object *obj)
	{
		objects.remove(obj);
		const_objects.remove(obj);
	}
	const std::list<Object*> *getObjects()
    {
		return &objects;
	}
	const std::list<const Object*> *getObjects() const
	{
		return &const_objects;
	}

	/* Methods for attractors placing */
	void addAttractor(Attractor *obj)
	{
		attractors.push_back(obj);
		const_attractors.push_back(obj);
	}
	void removeAttractor(Attractor *obj)
	{
		attractors.remove(obj);
		const_attractors.remove(obj);
	}
	const std::list<Attractor*> *getAttractors()
	{
		return &attractors;
	}
	const std::list<const Attractor*> *getAttractors() const
	{
		return &const_attractors;
	}

	/* Methods for emitters placing */
	void addEmitter(Emitter *obj)
	{
		emitters.push_back(obj);
		const_emitters.push_back(obj);
	}
	void removeEmitter(Emitter *obj)
	{
		emitters.remove(obj);
		const_emitters.remove(obj);
	}
	const std::list<Emitter*> *getEmitters()
	{
		return &emitters;
	}
	const std::list<const Emitter*> *getEmitters() const
	{
		return &const_emitters;
	}

	/* Spectator */
	void setSpectator(Spectator *sp)
	{
		spectator = sp;
	}
	Spectator *getSpectator()
	{
		return spectator;
	}
	const Spectator *getSpectator() const
	{
		return spectator;
	}

	/* Setting photon map */
	void setPhotonMap(PhotonMap *map)
	{
		photon_map = map;
	}
	PhotonMap *getPhotonMap()
	{
		return photon_map;
	}
	const PhotonMap *getPhotonMap() const
	{
		return photon_map;
	}

	const Object* intersect(const Ray &ray, Object::Intersection &state, const SceneParams &params, ContRand &rand) const
	{
		double record = INFINITY;
		Object *target = nullptr;
		Object::Intersection target_state;

		for(Object *obj : objects)
		{
			Object::Intersection st;

			if(obj->intersect(ray,st,params,rand))
			{
				double dist = st.distance;

				if(dist < record)
				{
					record = dist;
					target = obj;
					target_state = st;
				}
			}
		}

		state = target_state;
		return target;
	}

	Color collectPhotons(const vec3 &)
	{
		/* TODO: collect photons */
		return Color(0,0,0);
	}

	Color getAtmosphereColor(const Ray &) const
	{
		// double col = 0.5 + 0.5*ray.direction.y();
		// return Color(col,col,0.8*col + 0.2);
		// return Color(1,1,1);
		return Color(0,0,0);
	}
};

#endif // SCENE_H
