#ifndef DISTANCESPHERE_H
#define DISTANCESPHERE_H

#include"distanceobject.h"
#include"materialobject.h"

class DistanceSphere : public DistanceObject, public MaterialObject
{
private:
	double radius;
public:
	DistanceSphere(const vec3 &pos, double r, Material *m)
		:
		  Object(pos),
		  DistanceObject(pos),
		  MaterialObject(pos,m),
		  radius(r)
	{

	}

	virtual double getDistance(const vec3 &pos) const
	{
		return (length(pos - getPosition()) - radius) + 3.0*sin(2*pos.x())*sin(2*pos.y())*sin(2*pos.z());
	}
};

#endif // DISTANCESPHERE_H
