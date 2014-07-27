#include"render.h"

#include<SDL2/SDL.h>
#include<iostream>

void Render::init() throw(Exception) {
    w = 0; h = 0;
    color = new float[0];
    vertex = new float[0];

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
}

void Render::resize(const GLWindow::Size &s) {
    delete[] vertex;
    delete[] color;
    w = s.w;
    h = s.h;
	color = new float[4*h*w];
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

void Render::dispose() {
    delete[] color;
    delete[] vertex;
}

void Render::display() {

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
	glColorPointer( 4, GL_FLOAT, 0, color );
    glDrawArrays(GL_POINTS,0,w*h);
}

void Render::handle(const Event &event) {
	switch(event.type) {
	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_s)
		{
			SDL_Surface *bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
			for(int iy = 0; iy < h; ++iy)
			{
				for(int ix = 0; ix < w; ++ix)
				{
					float *data = color + 4*((h - iy - 1)*w + ix);
					*(static_cast<unsigned int*>(bitmap->pixels) + (iy*w + ix)) =
							(static_cast<unsigned int>((*(data+0))*0xff)<<0) +
							(static_cast<unsigned int>((*(data+1))*0xff)<<8) +
							(static_cast<unsigned int>((*(data+2))*0xff)<<16) +
							(static_cast<unsigned int>((*(data+3))*0xff)<<24);
				}
			}
			SDL_SaveBMP(bitmap,"../output/render.bmp");
			std::cout << "'render.bmp' was saved to 'output'" << std::endl;
		}
		break;
	default:
		break;
	}
}

void Render::paint(vec4 c, int ix, int iy, int iw, int ih) {
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

void Render::draw() {

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

			vec4 col(0,0,0,0);

            for(int jx = 0; jx < fsize; ++jx) {
                for(int jy = 0; jy < fsize; ++jy) {

					double x = (ix + 0.5*step + fstep*(jx-fsize/2.0+0.5) - w/2.0 + 0.5)/(h/2.0);
					double y = (iy + 0.5*step + fstep*(jy-fsize/2.0+0.5) - h/2.0 + 0.5)/(h/2.0);

					col = col + tracer->trace(vec2(x,y));
                }
            }
            paint(col/(fsize*fsize),ix,iy,step,step);
        }
    }

    tiling.next();
}
