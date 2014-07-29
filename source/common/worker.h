#ifndef WORKER_H
#define WORKER_H

#include"slice.h"

class Worker
{
public:

	/* Returns 0 if busy or non-zero if idle
	 * (may return number of idle threads) */
	virtual int isIdle() = 0;

	/* Gives work for one thread to render slice */
	virtual void render(Slice &slice) = 0;
};

#endif // WORKER_H
