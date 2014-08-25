#ifndef MATERIALOBJECT_H
#define MATERIALOBJECT_H

#include<render/object.h>
#include<render/material.h>

template <class T>
class MaterialObject : public T
{
private:
	const Material *material;
public:
	template <typename ... Args>
	MaterialObject(const Material *m, Args ... args) :
		T(args ...),
		material(m)
	{

	}

	virtual Color trace(
			const Ray &ray,
			const Object::Intersection &state,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand
			) const
	{
		return material->trace(ray,state.point,state.normal,add,params,rand);
	}

	virtual void cast(
			const Ray &ray,
			const Object::Intersection &state,
			const vec3 &dir,
			double prob,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand
			) const
	{
		material->cast(ray,state.point,state.normal,dir,prob,add,params,rand);
	}

	virtual unsigned int getInteractionKind(const Object::Intersection &) const
	{
		return material->getInteractionKind();
	}
};

#endif // MATERIALOBJECT_H
