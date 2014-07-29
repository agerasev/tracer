#ifndef DISRIBUTOR_H
#define DISRIBUTOR_H

#include<4u/thread/thread.hpp>
#include<4u/thread/mutex.hpp>

#include<list>

#include"render.h"

class Distributor : public Runnable
{
private:
	Render *rend;
	Mutex mutex;
	std::list<Thread*> pool;
	bool quited;
public:
	Distributor(Render *r)
		: rend(r)
	{

	}
	void start(int tnum)
	{
		for(int i = 0; i < tnum; ++i)
		{
			pool.push_back(new Thread(this,Thread::HIGH));
		}

		quited = false;

		for(Thread *t : pool)
		{
			t->start();
		}
	}
	void stop()
	{
		quited = true;

		for(Thread *t : pool)
		{
			t->join();
		}
	}

	virtual void run()
	{
		for(;;)
		{
			mutex.lock();
			if(quited)
			{
				return;
			}
			mutex.unlock();

			// LOCK
			mutex.lock();
			Tiling::Tile til;
			int d;
			bool w = rend->getWork(til,d);
			mutex.unlock();
			// UNLOCK

			int s;
			if(!w)
			{
				break;
			}
			std::vector<vec4> data(rend->trace(til,d,s));

			// LOCK
			mutex.lock();
			rend->passWork(data,til,s);
			mutex.unlock();
			// UNLOCK
		}
	}
};

#endif // DISRIBUTOR_H
