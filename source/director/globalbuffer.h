#ifndef GLOBALBUFFER_H
#define GLOBALBUFFER_H

#include<SDL2/SDL.h>
#include<GL/glew.h>

#include<4u/la/vec.hpp>
#include<vector>
#include<iostream>

#include<render/container/surface.h>

class GlobalBuffer
{
private:
	float *data = nullptr;
	int w = 0, h = 0;

	std::vector< std::pair<ivec4,vec4> > ranges;
	int slice_height = 1;

public:
	GlobalBuffer()
	{
		data = new float[4*w*h];
	}
	~GlobalBuffer()
	{
		delete[] data;
	}

	void resize(int x, int y)
	{
		/* Reallocates memory for data */
		delete[] data;
		w = x;
		h = y;
		data = new float[4*h*w];
		for(int iy = 0; iy < h; iy++) {
			for(int ix = 0; ix < w; ix++) {
				*(data + 4*(iy*w + ix))		= 0.0f;
				*(data + 4*(iy*w + ix) + 1)	= 0.0f;
				*(data + 4*(iy*w + ix) + 2)	= 0.0f;
				*(data + 4*(iy*w + ix) + 3)	= 0.0f;
			}
		}
		/* Making slices of memory */
		ranges.clear();
		int slice_number = (h + slice_height - 1)/slice_height;
		ranges.reserve(slice_number);
		for(int j = 0; j < slice_number; ++j)
		{
			int i = slice_number/2 - (j*(j%2) - j/2);
			int last_slice_height = slice_height;
			if(i + 1 == slice_number)
			{
				last_slice_height = (h % slice_height);
				if(last_slice_height == 0)
				{
					last_slice_height = slice_height;
				}
			}
			ranges.push_back(
						std::pair<ivec4, vec4>(
							ivec4(0, i*slice_height, w, last_slice_height),
							vec4(-w, 2.0*w, 2.0*i*slice_height - h, 2.0*last_slice_height)/h
							)
						);
		}
	}

	std::vector< std::pair<ivec4,vec4> >::iterator begin()
	{
		return ranges.begin();
	}

	std::vector< std::pair<ivec4,vec4> >::iterator end()
	{
		return ranges.end();
	}

	void update(const Surface *surface)
	{
		for(int iy = 0; iy < surface->h(); ++iy)
		{
			for(int ix = 0; ix < surface->w(); ++ix)
			{
				for(int i = 0; i < 4; ++i)
				{
					data[4*((iy + surface->y())*w + (ix + surface->x())) + i] = surface->getPixel(ix,iy)[i];
				}
			}
		}
	}

	void save() const
	{
		SDL_Surface *bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		for(int iy = 0; iy < h; ++iy)
		{
			for(int ix = 0; ix < w; ++ix)
			{
				const float *src = data + 4*((h - iy - 1)*w + ix);
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
		SDL_SaveBMP(bitmap,"render0000.bmp");
		//std::cout << "[info] flie was saved" << std::endl;
	}
};

#endif // GLOBALBUFFER_H
