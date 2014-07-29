#ifndef RENDER_H
#define RENDER_H

#include<GL/glew.h>

#include<vector>
#include<queue>

#include<4u/window/glwindow.hpp>
#include<4u/window/event.hpp>
#include<4u/la/vec.hpp>

#include"buffer.h"

class Render : public GLWindow::Render, public GLWindow::Listener {
public:
	class Tracer {
	public:
		virtual vec4 trace(const vec2 &pix) const = 0;
	};

private:

	int w, h;

	Buffer *buffer = nullptr;
	std::vector<Buffer::Slice>::iterator slice;
	std::queue<Buffer::Slice> update;

	Tracer *tracer = nullptr;

    Uint32 time = 0x10;

public:
	virtual void init() throw(Exception)
	{
		w = 0; h = 0;

		buffer = new Buffer();

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );
	}

	virtual void resize(const GLWindow::Size &s)
	{
		/* Clears updates */
		while(!update.empty())
		{
			update.pop();
		}

		w = s.w;
		h = s.h;

		/* Reallocates */
		buffer->resize(w,h);

		glClear(GL_COLOR_BUFFER_BIT);
	}

	virtual void dispose()
	{
		delete buffer;
	}

	virtual void display()
	{
		/*
		Uint32 lasttime = SDL_GetTicks();
		while((SDL_GetTicks() - lasttime) < time) {
			// mutex.lock();
			Tiling::Tile til;
			int d;
			bool w = getWork(til,d);
			// mutex.unlock();

			int s;
			if(!w)
			{
				break;
			}
			std::vector<vec4> data(trace(til,d,s));

			// mutex.lock();
			passWork(data,til,s);
			// mutex.unlock();

		}
		*/

		SDL_Delay(0x20);

		glVertexPointer( 2, GL_FLOAT, 0, buffer->getPointData() );
		glColorPointer( 4, GL_FLOAT, 0, buffer->getColorData() );

		while(!update.empty())
		{
			Buffer::Slice s = update.front();
			glDrawArrays(GL_POINTS, s.y*w + s.x, (s.y + s.h)*s.w);
			update.pop();
		}
	}

	virtual void handle(const Event &event)
	{
		switch(event.type) {
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_s)
			{
				buffer->save();
			}
			break;
		default:
			break;
		}
	}
	void setTracer(Tracer *tr) {
		tracer = tr;
	}

	/*
private:
	void paint(vec4 c, int ix, int iy, int iw = 1, int ih = 1)
	{
		for(int iix = ix; (iix < ix + iw)&&(iix < w); ++iix) {
			for(int iiy = iy; (iiy < iy + ih)&&(iiy < h); ++iiy) {
				float *cp = color + 4*(iiy*w + iix);
				cp[0] = c.x();
				cp[1] = c.y();
				cp[2] = c.z();
				cp[3] = 1.0;
			}
		}
	}
	*/

	/*
public:
	bool getWork(Tiling::Tile &til, int &d)
	{
		if(!tiling.end()) {
			til = tiling.current();
			d = det;
			tiling.next();
			return true;
		}
		else
		{
			if(tiling.end() && det < dmax) {
				tiling.rewind();
				++det;
				til = tiling.current();
				d = det;
				tiling.next();
				return true;
			}
		}
		return false;
	}
	std::vector<vec4> trace(const Tiling::Tile &t, int d, int &s) const
	{
		std::vector<vec4> data;

		int step = 1;
		if(d < 0) {
			step <<= -d;
		}
		int fsize = 1;
		double fstep = 1.0;
		if(d > 0) {
			fstep /= 1<<d;
			fsize <<= d;
		}
		for(int iy = t.y; iy < t.y + t.h; iy+=step) {
			for(int ix = t.x; ix < t.x + t.w; ix+=step) {

				vec4 col(0,0,0,0);

				for(int jx = 0; jx < fsize; ++jx) {
					for(int jy = 0; jy < fsize; ++jy) {

						double x = (ix + 0.5*step + fstep*(jx-fsize/2.0+0.5) - w/2.0 + 0.5)/(h/2.0);
						double y = (iy + 0.5*step + fstep*(jy-fsize/2.0+0.5) - h/2.0 + 0.5)/(h/2.0);

						col = col + tracer->trace(vec2(x,y));
					}
				}

				col /= fsize*fsize;
				data.push_back(col);
			}
		}

		s = step;
		return data;
	}
	void passWork(const std::vector<vec4> &data, const Tiling::Tile &t, int step)
	{
		int i = 0;
		for(int iy = t.y; iy < t.y + t.h; iy+=step) {
			for(int ix = t.x; ix < t.x + t.w; ix+=step) {
				paint(data[i++],ix,iy,step,step);
			}
		}
	}
	*/
};


#endif // RENDER_H
