#ifndef TASK_H
#define TASK_H

#include<memory>
#include<4u/rand/contrand.hpp>
#include<render/scene.h>
#include"result.h"

class Task
{
public:
	/* Performs some rendering operations with scene */
	virtual std::unique_ptr<const Result> perform(const Scene *scene, ContRand &rand) = 0;

	/* Interrupts rendering process */
	virtual void interrupt() = 0;
};

#endif // TASK_H
