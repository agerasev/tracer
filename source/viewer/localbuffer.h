#ifndef LOCALBUFFER_H
#define LOCALBUFFER_H

#include<SDL2/SDL.h>
#include<GL/glew.h>

#include<4u/la/vec.hpp>
#include<vector>
#include<iostream>

#include<render/container/surface.h>

class LocalBuffer
{
private:
	float *color = nullptr;
	float *point = nullptr;
	int w = 0, h = 0;

public:
	LocalBuffer()
	{
		color = new float[4*w*h];
		point = new float[2*w*h];
	}
	~LocalBuffer()
	{
		delete[] color;
		delete[] point;
	}

	void resize(int x, int y)
	{
		/* Reallocates memory for data */
		delete[] point;
		delete[] color;
		w = x;
		h = y;
		color = new float[4*h*w];
		point = new float[2*h*w];
		for(int iy = 0; iy < h; iy++) {
			for(int ix = 0; ix < w; ix++) {
				*(point + 2*(iy*w + ix)) = (ix - w/2.0f + 0.5f)/((float)w/2.0f);
				*(point + 2*(iy*w + ix) + 1) = (iy - h/2.0f + 0.5f)/((float)h/2.0f);
			}
		}
		for(int iy = 0; iy < h; iy++) {
			for(int ix = 0; ix < w; ix++) {
				*(color + 4*(iy*w + ix))		= 0.0f;
				*(color + 4*(iy*w + ix) + 1)	= 0.0f;
				*(color + 4*(iy*w + ix) + 2)	= 0.0f;
				*(color + 4*(iy*w + ix) + 3)	= 0.0f;
			}
		}
	}

	const float *getPointData()
	{
		return point;
	}

	const float *getColorData()
	{
		return color;
	}

	void save() const
	{
		SDL_Surface *bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		for(int iy = 0; iy < h; ++iy)
		{
			for(int ix = 0; ix < w; ++ix)
			{
				const float *src = color + 4*((h - iy - 1)*w + ix);
				unsigned int *dst = static_cast<unsigned int*>(bitmap->pixels) + (iy*w + ix);
				*dst = 0;
				for(int i = 0; i < 4; ++i)
				{
					float comp = *(src+i);
					comp = comp >= 0.0 ? (comp <= 1.0 ? comp : 1.0) : 0.0;
					*dst |= ( static_cast<unsigned int>(comp*0xff) << (8*i) );
				}
			}
		}
		SDL_SaveBMP(bitmap,"../output/render.bmp");
		std::cout << "'render.bmp' was saved to 'output'" << std::endl;
	}

	void update(const Surface *surface)
	{
		for(int iy = 0; iy < surface->h(); ++iy)
		{
			for(int ix = 0; ix < surface->w(); ++ix)
			{
				for(int i = 0; i < 4; ++i)
				{
					color[4*((iy + surface->y())*w + (ix + surface->x())) + i] = surface->getPixel(ix,iy)[i];
				}
			}
		}
	}
};

#endif // LOCALBUFFER_H
