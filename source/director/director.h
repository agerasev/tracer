#ifndef DIRECTOR_H
#define DIRECTOR_H

#include<list>
#include<iostream>

#include<common/worker.h>
#include<common/viewer.h>
#include<common/slice.h>

#include<4u/thread/thread.hpp>
#include<4u/thread/mutex.hpp>

#include"globalbuffer.h"

#include<viewer/localbuffer.h>

class Director : public Runnable, public Worker::Callback
{
private:
	int w, h;

	std::list<Viewer*> viewers;
	std::list<Worker*> workers;

	GlobalBuffer *buffer;
	std::vector<Slice>::iterator slice_iterator;

	Mutex mutex;
	std::queue<Slice> slice_queue;

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
			slice_iterator = buffer->begin();
			w = x; h = y;
		}
		mutex.unlock();
	}

	void updateViewers()
	{
		bool br = false;
		for(;;)
		{
			Slice slice;
			mutex.lock();
			{
				if(slice_queue.empty())
				{
					br = true;
				}
				else
				{
					slice = slice_queue.front();
					slice_queue.pop();
				}
			}
			mutex.unlock();

			if(br)
			{
				break;
			}

			mutex.lock();
			{
				for(Viewer *v : viewers)
				{
					v->update(slice);
				}
			}
			mutex.unlock();
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
					if(slice_iterator == buffer->end())
					{
						ret = true;
						break;
					}
					w->give(*slice_iterator);
					++slice_iterator;
				}
				if(ret)
				{
					break;
				}
			}
		}
		mutex.unlock();
	}

	virtual void done(const Slice &s)
	{
		//std::cout << "rendered " << s.y() << std::endl;
		//buffer->save();
		/* Add to queue */
		mutex.lock();
		{
			slice_queue.push(s);
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
			updateViewers();
		}
	}
};

#endif // DIRECTOR_H
