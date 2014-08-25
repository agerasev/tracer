#ifndef LOCALVIEWER_H
#define LOCALVIEWER_H

#include<common/viewer.h>

#include<GL/glew.h>

#include"localbuffer.h"
#include<queue>

#include<4u/window/glwindow.hpp>
#include<4u/la/vec.hpp>
#include<4u/thread/mutex.hpp>

#include<director/director.h>
#include<worker/localworker.h>

class LocalViewer : public Viewer, public GLWindow::Render {

private:
	/* Local width and height */
	int lw, lh;

	/* Server width and height */
	int gw, gh;

	/* Local data */
	LocalBuffer *buffer;

	/* Shared slice queue */
	std::queue< std::unique_ptr<const Surface> > surface_queue;
	Mutex mutex;

	int redraw = 2;

public:
	LocalViewer()
	{
		mutex.lock();
		{
			gw = 0; gh = 0;
			buffer = new LocalBuffer();
		}
		mutex.unlock();
	}

	virtual ~LocalViewer()
	{
		mutex.lock();
		{
			delete buffer;
		}
		mutex.unlock();
	}

	virtual void init() throw(Exception)
	{
		lw = 0; lh = 0;

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );

		redraw = true;
	}

	virtual void resize(const GLWindow::Size &s)
	{
		lw = s.w; lh = s.h;

		glClear(GL_COLOR_BUFFER_BIT);

		redraw = 2;
	}

	virtual void dispose()
	{

	}

	virtual void display()
	{
		/* Prevents big FPS - it's not required here */
		SDL_Delay(0x40);

		/* Update data from queue */
		/* Updates local shared data */
		bool br = false;
		for(;;)
		{
			std::unique_ptr<const Surface> surface;
			mutex.lock();
			{
				if(surface_queue.empty())
				{
					br = true;
				}
				else
				{
					surface = std::move(surface_queue.front());
					surface_queue.pop();
				}
			}
			mutex.unlock();

			if(br)
			{
				break;
			}

			redraw = 2;
			buffer->update(surface.get());
		}

		if(redraw > 0)
		{
			--redraw;

			/* Transfers data to GPU
			 * TODO: Transfer only updated data */
			glVertexPointer( 2, GL_FLOAT, 0, buffer->getPointData() );
			glColorPointer( 4, GL_FLOAT, 0, buffer->getColorData() );

			glDrawArrays(GL_POINTS, 0, gw*gh);
		}
	}

	virtual void update(std::unique_ptr<const Surface> surface)
	{
		/* Add to queue */
		mutex.lock();
		{
			surface_queue.push(std::move(surface));
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
		}
		mutex.unlock();

		glClear(GL_COLOR_BUFFER_BIT);
	}
};

#endif // LOCALVIEWER_H
