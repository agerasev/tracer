#ifndef SPECULARANDDIFFUSEMATERIAL_H
#define SPECULARANDDIFFUSEMATERIAL_H

#include<vector>
#include<utility>
#include<initializer_list>

#include<render/material.h>

class HybridMaterial : public Material
{
private:
	std::vector<std::pair<const Material*,double>> materials;

public:
	HybridMaterial(std::initializer_list<std::pair<const Material *,double>> list)
	{
		for(const std::pair<const Material *, double> &p : list)
		{
			materials.push_back(p);
		}
	}

	/* Returns glow color and adds secondary rays */
	virtual Color trace(
			const Ray &ray,
			const vec3 &point,
			const vec3 &normal,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand,
			double weight = 1.0
			) const
	{
		Color color(0,0,0);
		for(const auto &p : materials)
		{
			color += p.first->trace(ray,point,normal,add,params,rand,weight*p.second);
		}
		return color;
	}

	virtual void cast(
			const Ray &ray,
			const vec3 &point,
			const vec3 &normal,
			const vec3 &dir,
			double prob,
			std::function<void(Ray &&)> add,
			const SceneParams &params,
			ContRand &rand,
			double weight = 1.0
			) const
	{
		for(const auto &p : materials)
		{
			p.first->cast(ray,point,normal,dir,prob,add,params,rand,weight*p.second);
		}
	}

	/* Returns kind of interaction as bitfield */
	virtual unsigned int getInteractionKind() const
	{
		unsigned int kind = 0;
		for(const auto &p : materials)
		{
			kind |= p.first->getInteractionKind();
		}
		return kind;
	}
};

#endif // SPECULARANDDIFFUSEMATERIAL_H
