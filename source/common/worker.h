#ifndef WORKER_H
#define WORKER_H

#include<memory>
#include"task.h"
#include"result.h"

class Worker
{
public:
	class Callback
	{
	public:
		virtual void done(std::unique_ptr<const Result> result) = 0;
	};

	virtual void setCallback(Callback *cb) = 0;

	/* Returns 0 if busy or non-zero if idle
	 * (may return number of idle threads) */
	virtual int idle() = 0;

	/* Gives work for one thread to render task */
	virtual void give(std::unique_ptr<Task> task) = 0;

	/* Interrupts current rendering */
	virtual void interrupt() = 0;
};

#endif // WORKER_H
