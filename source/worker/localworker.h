#ifndef LOCALWORKER_H
#define LOCALWORKER_H

#include<common/worker.h>
#include<common/slice.h>

#include<4u/thread/thread.hpp>
#include<4u/thread/mutex.hpp>

#include<queue>

#include<tracer/tracer.h>

class LocalWorker : public Worker, public Runnable
{
private:
	Mutex mutex;
	int free;

	Tracer *tracer;
	bool quited = false;

	std::queue<Slice> tasks;

	Callback *callback;

public:
	LocalWorker(int f = 1)
		: free(f), tracer(new Tracer())
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

	void renderTasks()
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

			render(slice);
			callback->done(slice);
		}
	}

	void render(Slice &slice)
	{
		mutex.lock();
		{
			--free;
		}
		mutex.unlock();

		int detalization = 4;
		for(int iy = 0; iy < slice.h(); ++iy)
		{
			for(int ix = 0; ix < slice.w(); ++ix)
			{
				vec4 color = vec4(0,0,0,1);
				for(int jy = 0; jy < detalization; ++jy)
				{
					for(int jx = 0; jx < detalization; ++jx)
					{
						color += tracer->trace(
									slice.getCoord(
										ix + static_cast<double>(jx)/detalization - 0.5,
										iy + static_cast<double>(jy)/detalization - 0.5
										)
									);
						if(quited)
						{
							return;
						}
					}
				}
				slice.setPixel(color/(detalization*detalization),ix,iy);
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

			renderTasks();
		}
	}
};

#endif // LOCALWORKER_H
