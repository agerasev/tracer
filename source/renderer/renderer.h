#ifndef MANDELBROT_H
#define MANDELBROT_H

#include<GL/glew.h>

#include"../window/glwindow.h"
//#include"../buffer/buffer.h"

#include"tiling.h"
#include"../util/color.hpp"

class Renderer : public GLWindow::Renderer, public GLWindow::Listener {
public:
	class Tracer {
	public:
		virtual Color trace(double x, double y) = 0;
	};

private:
    float *vertex = nullptr;
    float *color = nullptr;
    int w, h;
    //Buffer buffer;

	Tracer *tracer = nullptr;

    Tiling tiling;
    Uint32 time = 0x10;

    const int dmin = -4;
	const int dmax = 4;
    int det = dmin;

public:
    virtual void init();
    virtual void resize(const GLWindow::Size &s);
    virtual void dispose();
    virtual void display();
    virtual void handle(const SDL_Event &event);
	void setTracer(Tracer *tr) {
		tracer = tr;
	}

private:
	void paint(Color c, int ix, int iy, int iw = 1, int ih = 1);
    void draw();
};

#endif // MANDELBROT_H
