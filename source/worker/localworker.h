#ifndef LOCALWORKER_H
#define LOCALWORKER_H

#include<common/worker.h>
#include<common/slice.h>

#include<4u/thread/thread.hpp>
#include<4u/thread/mutex.hpp>

#include<tracer/tracer.h>

class LocalWorker : public Worker
{
private:
	Mutex mutex;
	bool idle;

	Tracer *tracer;

public:
	LocalWorker()
		: idle(true), tracer(new Tracer())
	{

	}

	virtual int isIdle()
	{
		mutex.lock();
		{
			return idle;
		}
		mutex.unlock();
	}

	virtual void render(Slice &slice)
	{
		mutex.lock();
		{
			idle = false;
		}
		mutex.unlock();

		int detalization = 32;
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
					}
				}
				slice.setPixel(color/(detalization*detalization),ix,iy);
			}
		}

		mutex.lock();
		{
			idle = true;
		}
		mutex.unlock();
	}
};

#endif // LOCALWORKER_H
