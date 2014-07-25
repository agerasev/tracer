#ifndef CONTRAND_HPP
#define CONTRAND_HPP

#include"rand.hpp"

#include<ctime>

class ContRandInt : public Rand<unsigned int>
{
private:
	static const unsigned int LCA_A = 1103515245;
	static const unsigned int LCA_B = 12345;
	unsigned int last;
public:
	ContRandInt(unsigned int seed = static_cast<unsigned int>(time(nullptr)))
		: last(seed)
	{

	}

	virtual unsigned int get()
	{
		return last = last*LCA_A + LCA_B;
	}
};

class ContRand : public Rand<double>
{
private:
	ContRandInt generator;
	const double NORM_FACTOR;
public:
	ContRand() :
		generator(),
		NORM_FACTOR(1.0/static_cast<double>(0xffffffffu))
	{

	}

	virtual double get()
	{
		return NORM_FACTOR*generator.get();
	}
};

#endif // CONTRAND_HPP
