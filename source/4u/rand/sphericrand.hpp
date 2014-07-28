#ifndef SPHERICRAND_HPP
#define SPHERICRAND_HPP

#include"rand.hpp"
#include"contrand.hpp"

#include<cmath>
#include<4u/util/const.hpp>
#include<4u/la/vec.hpp>

#include<4u/util/const.hpp>

class SphericRand : public Rand<vec3>
{
private:
	ContRand generator;
public:
	virtual vec3 get()
	{
		double phi = 2.0*PI*generator.get();
		double theta = acos(1.0 - 2.0*generator.get());
		return vec3(cos(phi)*sin(theta),sin(phi)*sin(theta),cos(theta));
	}
};

class SemiSphericRand : public Rand<vec3>
{
private:
	SphericRand generator;
	vec3 normal;
public:
	SemiSphericRand()
	{

	}

	SemiSphericRand(const vec3 &n)
		: normal(n)
	{

	}

	void setNormal(const vec3 &n)
	{
		normal = n;
	}

	virtual vec3 get()
	{
		vec3 rand = generator.get();
		double proj = rand*normal;
		return rand - static_cast<double>(proj < 0)*(2.0*normal*proj);
	}
};

#endif // SPHERICRAND_HPP
