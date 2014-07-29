#ifndef LOCALVIEWER_H
#define LOCALVIEWER_H

#include<common/viewer.h>

#include<GL/glew.h>

#include"buffer.h"
#include<queue>

#include<4u/window/glwindow.hpp>
#include<4u/la/vec.hpp>
#include<4u/thread/mutex.hpp>

#include<common/worker.h>

class LocalViewer : public Viewer, public GLWindow::Render {

private:
	/* Local width and height */
	int lw, lh;

	/* Server width and height */
	int gw, gh;

	/* Local shared data */
	Buffer *buffer;
	Mutex mutex;

	/* Just for test */
	Worker *worker;
	std::vector<Slice>::iterator slice_iterator;

public:
	virtual void init() throw(Exception)
	{
		lw = 0; lh = 0;

		mutex.lock();
		{
			gw = 0; gh = 0;
			buffer = new Buffer();
		}
		mutex.unlock();

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );
	}

	virtual void resize(const GLWindow::Size &s)
	{
		lw = s.w; lh = s.h;

		glClear(GL_COLOR_BUFFER_BIT);

		resize(lw,lh);
	}

	virtual void dispose()
	{
		mutex.lock();
		{
			delete buffer;
		}
		mutex.unlock();
	}

	virtual void display()
	{
		if(slice_iterator != buffer->end())
		{
			worker->render(*slice_iterator);
			++slice_iterator;
		}
		else
		{
			/* Prevents big FPS - it's not required here */
			SDL_Delay(0x40);
		}

		/* Transfers local shared data to GPU
		 * TODO: Transfer only updated data */
		mutex.lock();
		{
			glVertexPointer( 2, GL_FLOAT, 0, buffer->getPointData() );
			glColorPointer( 4, GL_FLOAT, 0, buffer->getColorData() );

			glDrawArrays(GL_POINTS, 0, gw*gh);
		}
		mutex.unlock();
	}

	virtual void update(const Slice &slice)
	{
		/* Updates local shared data */
		mutex.lock();
		{
			buffer->update(slice);
		}
		mutex.unlock();
	}

	virtual void resize(int w, int h)
	{
		/* Reallocates local shared data */
		mutex.lock();
		{
			gw = w; gh = h;
			buffer->resize(w,h);
			slice_iterator = buffer->begin();
		}
		mutex.unlock();

		glClear(GL_COLOR_BUFFER_BIT);
	}

	/* Just for test */
	void setWorker(Worker *w)
	{
		worker = w;
	}
};

#endif // LOCALVIEWER_H
