#ifndef OBJECT_H
#define OBJECT_H

#include"../util/vec.hpp"
#include"../util/mat.hpp"

#include"object.h"
#include"ray.h"
#include"beam.h"

class Object
{
public:
	vec3 position;
	mat3 orientation;

	Object(const vec3 &pos = vec3(0,0,0), const mat3 &ori = mat3(1)) :
		position(pos), orientation(ori) {}

	virtual double size() const = 0;
	virtual bool trace(const Ray &ray, vec3 &pnt, Beam &beam) const = 0;
};

#endif // OBJECT_H
