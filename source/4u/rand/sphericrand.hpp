#ifndef SPHERICRAND_HPP
#define SPHERICRAND_HPP

#include"rand.hpp"
#include"contrand.hpp"

#include<cmath>
#include<4u/util/const.hpp>
#include<4u/la/vec.hpp>

#include<4u/util/const.hpp>

class SphericRandStatic
{
public:
	static vec3 wrap(ContRand &rand)
	{
		double phi = 2.0*PI*rand.get();
		double theta = acos(1.0 - 2.0*rand.get());
		return vec3(cos(phi)*sin(theta),sin(phi)*sin(theta),cos(theta));
	}
};

class SphericRand : public Rand<vec3>
{
private:
	ContRand generator;
public:
	virtual vec3 get()
	{
		return SphericRandStatic::wrap(generator);
	}
};

class SemiSphericRandStatic
{
private:
	static vec3 reflect(const vec3 &rand, const vec3 &normal)
	{
		double proj = rand*normal;
		return rand - static_cast<double>(proj < 0)*(2.0*normal*proj);
	}

public:
	static vec3 wrap(SphericRand &spheric_rand, const vec3 &normal)
	{
		return reflect(spheric_rand.get(),normal);
	}
	static vec3 wrap(ContRand &rand, const vec3 &normal)
	{
		return reflect(SphericRandStatic::wrap(rand),normal);
	}
};

class SemiSphericRand : public Rand<vec3, const vec3 &>
{
private:
	SphericRand generator;
public:
	virtual vec3 get(const vec3 &normal)
	{
		return SemiSphericRandStatic::wrap(generator,normal);
	}
};

#endif // SPHERICRAND_HPP
