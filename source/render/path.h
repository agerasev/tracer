#ifndef PATH_H
#define PATH_H

#include<vector>
#include"ray.h"
#include"color.h"
#include"object.h"

class Path
{
public:
	Ray ray;
	const Object *object;
	Object::Intersection state;
	Color glow;
	std::vector<Path> paths;
	Path(const Ray &r, const Object *o = nullptr) :
		ray(r), object(o)
	{

	}
};

#endif // PATH_H
