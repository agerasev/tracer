#include"renderer.h"

void Renderer::init() {
    w = 0; h = 0;
    color = new float[0];
    vertex = new float[0];

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
}

void Renderer::resize(const GLWindow::Size &s) {
    delete[] vertex;
    delete[] color;
    w = s.w;
    h = s.h;
    color = new float[3*h*w];
    vertex = new float[2*h*w];
    tiling.resize(w,h);
    det = dmin;
    for(int iy = 0; iy < h; iy++) {
        for(int ix = 0; ix < w; ix++) {
            *(vertex + 2*(iy*w + ix)) = (ix - w/2.0f + 0.5f)/((float)w/2.0f);
            *(vertex + 2*(iy*w + ix) + 1) = (iy - h/2.0f + 0.5f)/((float)h/2.0f);
        }
    }
    /*
    buffer.setSize(w*h);
    buffer.bufferVertex(vertex);
    buffer.bufferColor(color);
    */
}

void Renderer::dispose() {
    delete[] color;
    delete[] vertex;
}

void Renderer::display() {

    Uint32 lasttime = SDL_GetTicks();
    while((SDL_GetTicks() - lasttime) < time && !tiling.end()) {
        draw();
    }
    if(tiling.end() && det < dmax) {
        tiling.rewind();
        ++det;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glVertexPointer( 2, GL_FLOAT, 0, vertex );
    glColorPointer( 3, GL_FLOAT, 0, color );
    glDrawArrays(GL_POINTS,0,w*h);
}

void Renderer::handle(const SDL_Event &event) {
	switch(event.type) {

	}
}

void Renderer::paint(Color c, int ix, int iy, int iw, int ih) {
    for(int iix = ix; (iix < ix + iw)&&(iix < w); ++iix) {
        for(int iiy = iy; (iiy < iy + ih)&&(iiy < h); ++iiy) {
            float *cp = color + 3*(iiy*w + iix);
			cp[0] = c.r();
			cp[1] = c.g();
			cp[2] = c.b();
        }
    }
}

void Renderer::draw() {

	if(tracer == nullptr) {
		return;
	}

    Tiling::Tile t = tiling.current();

    int step = 1;
    if(det < 0) {
        step <<= -det;
    }
    int fsize = 1;
    double fstep = 1.0;
    if(det > 0) {
        fstep /= 1<<det;
        fsize <<= det;
    }
    for(int iy = t.y; iy < t.y + t.h; iy+=step) {
        for(int ix = t.x; ix < t.x + t.w; ix+=step) {

			Color col(0,0,0,1);

            for(int jx = 0; jx < fsize; ++jx) {
                for(int jy = 0; jy < fsize; ++jy) {

					double x = (ix + 0.5*step + fstep*(jx-fsize/2.0+0.5) - w/2.0 + 0.5)/(h/2.0);
					double y = (iy + 0.5*step + fstep*(jy-fsize/2.0+0.5) - h/2.0 + 0.5)/(h/2.0);

					col = col + tracer->trace(x,y);
                }
            }
            paint(col/(fsize*fsize),ix,iy,step,step);
        }
    }

    tiling.next();
}
