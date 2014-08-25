#ifndef MODIFIER_H
#define MODIFIER_H

#include<tracer/scene.h>

class Modifier
{
public:
	virtual void modify(Scene *scene) = 0;
};

#endif // MODIFIER_H
