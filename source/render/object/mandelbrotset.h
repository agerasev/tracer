#ifndef MANDELBROTSET_H
#define MANDELBROTSET_H

#include<4u/la/vec3.hpp>
#include<4u/la/mat.hpp>

#include<4u/complex/quaternion.hpp>
typedef complex<complex<double>> quaternion;

#include"distanceobject.h"

template <int DEPTH>
class MandelbrotSet : public DistanceObject
{
public:
	/* p - object center,  b - basis of object, r - max size,
	 * c - initial point in fractal computation, d - depth */
	MandelbrotSet(const vec3 &p, double r) :
		DistanceObject(p,r,0.4,1e-4)
	{

	}

	virtual double getDistance(const vec3 &pos) const
	{
		quaternion a(0.0,0.0,0.0,0.0), c(-pos.y(),-pos.z(),-pos.x(),0.0);
		int i = 0;
		for(; i < DEPTH; ++i)
		{
			a = a*a + c;
			if(abs2(a).r() > 4.0)
			{
				break;
			}
		}
		return (4.0*(1<<(DEPTH - i - 1)) + abs2(a).r() - 4.0)/(4.0*(1<<DEPTH));
	}
};


#endif // MANDELBROTSET_H
