#ifndef DISKRAND_H
#define DISKRAND_H

#include<4u/la/vec.hpp>
#include<4u/rand/contrand.hpp>
#include<4u/util/const.hpp>

#include<math.h>

class DiskRandStatic
{
public:
	static vec2 wrap(ContRand &rand)
	{
		double r = sqrt(rand.get());
		double phi = 2.0*PI*rand.get();
		return r*vec2(cos(phi),sin(phi));
	}
};

class DiskRand : public Rand<vec2>
{
private:
	ContRand rand;
public:
	virtual vec2 get()
	{
		return DiskRandStatic::wrap(rand);
	}
};

#endif // DISKRAND_H
