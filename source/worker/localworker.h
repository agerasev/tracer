#ifndef LOCALWORKER_H
#define LOCALWORKER_H

#include<common/worker.h>
#include<common/slice.h>

#include<4u/thread/thread.hpp>
#include<4u/thread/mutex.hpp>
#include<4u/rand/contrand.hpp>

#include<queue>

#include"disributor.h"
#include"renderparams.h"

#include<tracer/tracer.h>

class LocalWorker : public Worker, public Runnable
{
private:
	Tracer *tracer;
	bool quited = false;

	Mutex mutex;
	int free;
	ContRandInt init_rand;

	std::queue<Slice> tasks;

	Callback *callback;

	Distributor distributor;
	const RenderParams params;

public:
	LocalWorker(Tracer *t, const RenderParams p)
		: tracer(t), free(2*p.threads), init_rand(), distributor(this), params(p)
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

	virtual void give(Slice &slice)
	{
		mutex.lock();
		{
			tasks.push(slice);
		}
		mutex.unlock();
	}

	void renderTasks(ContRand &rand)
	{
		bool br = false;
		bool fr = true;
		for(;;)
		{
			Slice slice;

			mutex.lock();
			{
				if(tasks.empty())
				{
					br = true;
				}
				else
				{
					fr = false;
					slice = tasks.front();
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

			render(slice,rand);
			callback->done(slice);
		}
	}

	void render(Slice &slice, ContRand &rand)
	{
		mutex.lock();
		{
			--free;
		}
		mutex.unlock();

		for(int iy = 0; iy < slice.h(); ++iy)
		{
			for(int ix = 0; ix < slice.w(); ++ix)
			{
				vec4 color = nullvec4;
				for(int jy = 0; jy < params.detailing; ++jy)
				{
					vec4 lcolor = nullvec4;
					for(int jx = 0; jx < params.detailing; ++jx)
					{
						lcolor += tracer->trace(
									slice.getCoord(
										ix + static_cast<double>(jx)/params.detailing - 0.5,
										iy + static_cast<double>(jy)/params.detailing - 0.5
										),
									rand
									);
						if(quited)
						{
							return;
						}
					}
					color += lcolor/params.detailing;
				}
				slice.setPixel(
							color/params.detailing,
							ix,iy
							);
			}
		}

		mutex.lock();
		{
			++free;
		}
		mutex.unlock();
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

			renderTasks(rand);
		}
	}

	void start()
	{
		distributor.start(params.threads);
	}

	void wait()
	{
		distributor.stop();
	}
};

#endif // LOCALWORKER_H
