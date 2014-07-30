#ifndef DISRIBUTOR_H
#define DISRIBUTOR_H

#include<4u/thread/thread.hpp>
#include<4u/thread/mutex.hpp>

#include<list>

class Distributor
{
private:
	Runnable *runnable;
	std::list<Thread*> pool;
public:
	Distributor(Runnable *r)
		: runnable(r)
	{

	}
	void start(int tnum)
	{
		for(int i = 0; i < tnum; ++i)
		{
			pool.push_back(new Thread(runnable,Thread::HIGH));
		}

		for(Thread *t : pool)
		{
			t->start();
		}
	}
	void stop()
	{
		for(Thread *t : pool)
		{
			t->join();
		}
	}
};

#endif // DISRIBUTOR_H
