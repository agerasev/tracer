#ifndef JULIASET_H
#define JULIASET_H

#include<4u/la/vec3.hpp>
#include<4u/la/mat.hpp>

#include<4u/complex/quaternion.hpp>
typedef complex<complex<double>> quaternion;

#include"distanceobject.h"

template <int DEPTH>
class JuliaSet : public DistanceObject
{
private:
	mat3 basis;
	quaternion constant;

public:
	/* p - object center,  b - basis of object, r - max size,
	 * c - initial point in fractal computation, d - depth */
	JuliaSet(const vec3 &p, double r, const mat3 &b, const quaternion &c) :
		DistanceObject(p,r,0.5,1e-4),
		basis(b),
		constant(c)
	{

	}

	virtual double getDistance(const vec3 &pos) const
	{
		vec3 bpos = basis*pos;
		quaternion a(bpos.x(),bpos.y(),bpos.z(),0.0), c = constant;
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

#endif // JULIASET_H
