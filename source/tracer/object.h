#ifndef OBJECT_H
#define OBJECT_H

#include<vector>

#include"../util/vec.hpp"
#include"../util/mat.hpp"

#include"object.h"
#include"ray.h"

class Object
{
public:
	vec3 position;
	mat3 orientation;

	Object(const vec3 &pos = vec3(0,0,0), const mat3 &ori = mat3(1)) :
		position(pos), orientation(ori) {}

	virtual double size() const = 0;
	virtual bool collide(const Ray &ray, vec3 &pnt) const = 0;
	virtual Color trace(const Ray &ray, std::vector<Ray> &buffer, int quality) const = 0;
};

#endif // OBJECT_H
