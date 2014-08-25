#ifndef POLYGON_H
#define POLYGON_H

#include<utility>
#include<initializer_list>

#include<4u/la/vec.hpp>
#include<4u/rand/contrand.hpp>

#include<render/object.h>
#include<render/params.h>

#include"plane.h"

template <int N>
class Polygon : public Plane
{
private:
	vec3 vertex[N];
	double size;

public:
	Polygon(const vec3 &p, const vec3 &n, std::initializer_list<vec3> v)
		:
		  Plane(p,n)
	{
		auto ii = v.begin();
		for(int i = 0; i < N && ii != v.end(); ++i, ++ii) {
			vertex[i] = *ii;
		}

		double max_dist2 = 0.0;
		for(int i = 0; i < N; ++i) {
			double dist2 = sqr(vertex[i] - getPosition());
			if(dist2 > max_dist2)
			{
				max_dist2 = dist2;
			}
		}
		size = sqrt(max_dist2);
	}

	virtual double getSize() const
	{
		return size;
	}

	virtual bool intersect(
			const Ray &ray,
			Intersection &state,
			const SceneParams &params,
			ContRand &rand
			) const
	{
		bool sect = Plane::intersect(ray,state,params,rand);
		if(!sect)
		{
			return false;
		}

		vec3 normal = getNormal();
		for(int i = 0; i < N-1; ++i)
		{
			if(((state.point - vertex[i])^(vertex[i+1] - vertex[i]))*normal > 0.0)
			{
				return false;
			}
		}
		if(((state.point - vertex[N-1])^(vertex[0] - vertex[N-1]))*normal > 0.0)
		{
			return false;
		}
		return true;
	}

};

typedef Polygon<3> Triangle;
typedef Polygon<4> Quad;

#endif // POLYGON_H
