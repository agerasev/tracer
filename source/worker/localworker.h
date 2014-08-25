#ifndef LOCALWORKER_H
#define LOCALWORKER_H

#include<common/task.h>
#include<common/result.h>
#include<common/worker.h>

#include<4u/thread/thread.hpp>
#include<4u/thread/mutex.hpp>
#include<4u/rand/contrand.hpp>

#include<memory>
#include<queue>

#include"disributor.h"

#include<render/scene.h>

class LocalWorker : public Worker, public Runnable
{
private:
	const Scene *scene;
	bool quited = false;

	Mutex mutex;
	int free;
	ContRandInt init_rand;

	std::queue< std::unique_ptr<Task> > tasks;

	Callback *callback;

	Distributor distributor;
	int threads;

public:
	LocalWorker(const Scene *s, int t)
		: scene(s), free(2*t), init_rand(), distributor(this), threads(t)
	{

	}

	virtual void setCallback(Callback *cb)
	{
		callback = cb;
	}

	virtual int idle()
	{
		int ret;
		mutex.lock();
		{
			ret = free - tasks.size();
		}
		mutex.unlock();
		return ret;
	}

	virtual void give(std::unique_ptr<Task> task)
	{
		mutex.lock();
		{
			tasks.push(std::move(task));
		}
		mutex.unlock();
	}

	void performTasks(ContRand &rand)
	{
		bool br = false;
		bool fr = true;
		for(;;)
		{
			std::unique_ptr<Task> task;

			mutex.lock();
			{
				if(tasks.empty())
				{
					br = true;
				}
				else
				{
					fr = false;
					task = std::move(tasks.front());
					tasks.pop();
				}
			}
			mutex.unlock();

			if(fr)
			{
				SDL_Delay(0x10);
			}
			if(br)
			{
				break;
			}

			mutex.lock();
			{
				--free;
			}
			mutex.unlock();

			callback->done(task->perform(scene,rand));

			mutex.lock();
			{
				++free;
			}
			mutex.unlock();
		}
	}

	virtual void interrupt()
	{
		mutex.lock();
		{
			while(!tasks.empty())
			{
				tasks.pop();
			}
		}
		mutex.unlock();
	}

	void quit()
	{
		mutex.lock();
		{
			quited = true;
		}
		mutex.unlock();
	}

	virtual void run()
	{
		mutex.lock();
		ContRand rand(0x562f1091*init_rand.get());
		mutex.unlock();

		bool br = false;
		for(;;)
		{
			mutex.lock();
			{
				if(quited)
				{
					br = true;
				}
			}
			mutex.unlock();

			if(br)
			{
				break;
			}

			performTasks(rand);
		}
	}

	void start()
	{
		distributor.start(threads);
	}

	void wait()
	{
		distributor.stop();
	}
};

#endif // LOCALWORKER_H
