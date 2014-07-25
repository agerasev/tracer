#ifndef RENDER_H
#define RENDER_H

#include<GL/glew.h>

#include<4u/window/glwindow.hpp>
#include<4u/window/event.hpp>
#include<4u/la/vec.hpp>

#include"tiling.h"

class Render : public GLWindow::Render, public GLWindow::Listener {
public:
	class Tracer {
	public:
		virtual vec4 trace(const vec2 &pix) = 0;
	};

private:
    float *vertex = nullptr;
    float *color = nullptr;
	int w, h;

	Tracer *tracer = nullptr;

    Tiling tiling;
    Uint32 time = 0x10;

    const int dmin = -4;
	const int dmax = 4;
    int det = dmin;

public:
	virtual void init() throw(Exception);
	virtual void resize(const GLWindow::Size &s);
    virtual void dispose();
    virtual void display();
	virtual void handle(const Event &event);
	void setTracer(Tracer *tr) {
		tracer = tr;
	}

private:
	void paint(vec4 c, int ix, int iy, int iw = 1, int ih = 1);
    void draw();
};

#endif // RENDER_H
