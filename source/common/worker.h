#ifndef WORKER_H
#define WORKER_H

#include"slice.h"
#include"tracer/tracer.h"

class Worker
{
public:
	class Callback
	{
	public:
		virtual void done(const Slice &s) = 0;
	};

	virtual void setCallback(Callback *cb) = 0;

	/* Returns 0 if busy or non-zero if idle
	 * (may return number of idle threads) */
	virtual int idle() = 0;

	/* Gives work for one thread to render slice */
	virtual void give(Slice &slice) = 0;

	/* Interrupts current rendering */
	virtual void interrupt() = 0;
};

#endif // WORKER_H
