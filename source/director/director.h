#ifndef DIRECTOR_H
#define DIRECTOR_H

#include<list>
#include<iostream>
#include<memory>
#include<queue>

#include<common/worker.h>
#include<common/viewer.h>

#include<4u/thread/thread.hpp>
#include<4u/thread/mutex.hpp>

#include"task/pathtracingtask.h"
#include"result/photonmapresult.h"

#include"globalbuffer.h"

#include<viewer/localbuffer.h>

class Director : public Runnable, public Worker::Callback
{
private:
	int w, h;

	std::list<Viewer*> viewers;
	std::list<Worker*> workers;

	RenderParams params;

	GlobalBuffer *buffer;
	std::vector< std::pair<ivec4,vec4> >::iterator range_iterator;

	Mutex mutex;
	std::queue< std::unique_ptr<const Result> > result_queue;

	int rendering_slices = 0;
	bool dumped = false;

	bool quited = false;

public:
	Director()
	{
		mutex.lock();
		{
			w = 0; h = 0;
			buffer = new GlobalBuffer();
		}
		mutex.unlock();
	}

	~Director()
	{
		mutex.lock();
		{
			delete buffer;
		}
		mutex.unlock();
	}

	void add(Worker *w)
	{
		mutex.lock();
		{
			workers.push_back(w);
			w->setCallback(this);
		}
		mutex.unlock();
	}
	void remove(Worker *w)
	{
		mutex.lock();
		{
			workers.remove(w);
			w->setCallback(nullptr);
		}
		mutex.unlock();
	}
	void add(Viewer *v)
	{
		mutex.lock();
		{
			viewers.push_back(v);
			v->resize(w,h);
		}
		mutex.unlock();
	}
	void remove(Viewer *v)
	{
		mutex.lock();
		{
			viewers.remove(v);
		}
		mutex.unlock();
	}

	void resize(int x, int y)
	{
		mutex.lock();
		{
			for(Worker *w : workers)
			{
				w->interrupt();
			}
			for(Viewer *v : viewers)
			{
				v->resize(x,y);
			}
			buffer->resize(x,y);
			range_iterator = buffer->begin();
			w = x; h = y;
		}
		mutex.unlock();
	}

	void setParams(const RenderParams &p)
	{
		params = p;
	}

	void update()
	{
		bool br = false;
		for(;;)
		{
			std::unique_ptr<const Result> result;
			mutex.lock();
			{
				if(result_queue.empty())
				{
					br = true;
				}
				else
				{
					result = std::move(result_queue.front());
					result_queue.pop();
				}
			}
			mutex.unlock();

			if(br)
			{
				break;
			}

			if(result->type == TYPE_RESULT_SURFACE)
			{
				const Surface *surface = nullptr;
				const SurfaceResult *sr = dynamic_cast<const SurfaceResult *>(result.get());
				if(sr != nullptr)
				{
					surface = new Surface(*sr->getSurface());
				}

				if(surface == nullptr)
				{
					return;
				}

				mutex.lock();
				{
					buffer->update(surface);
					for(Viewer *v : viewers)
					{
						v->update(std::unique_ptr<const Surface>(surface));
					}
				}
				mutex.unlock();
			}
			else if(result->type == TYPE_RESULT_PHOTON_MAP)
			{

			}
		}
		if(!dumped && rendering_slices == 0 && range_iterator == buffer->end())
		{
			std::cout << SDL_GetTicks()/1000.0 << " seconds" << std::endl;
			buffer->save();
			dumped = true;
		}
	}

	void distributeWork()
	{
		bool ret = false;
		mutex.lock();
		{
			for(Worker *w : workers)
			{
				while(w->idle() > 0)
				{
					if(range_iterator == buffer->end())
					{
						ret = true;
						break;
					}
					w->give(std::unique_ptr<Task>(new PathTracingTask(
													  range_iterator->first,
													  range_iterator->second,
													  params
													  )));
					++range_iterator;
					++rendering_slices;
				}
				if(ret)
				{
					break;
				}
			}
		}
		mutex.unlock();
	}

	virtual void done(std::unique_ptr<const Result> result)
	{
		mutex.lock();
		{
			result_queue.push(std::move(result));
			--rendering_slices;
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

			SDL_Delay(0x20);
			distributeWork();
			update();
		}
	}
};

#endif // DIRECTOR_H
