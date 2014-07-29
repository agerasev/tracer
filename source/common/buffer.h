#ifndef BUFFER_H
#define BUFFER_H

#include<SDL2/SDL.h>
#include<GL/glew.h>

#include<4u/la/vec.hpp>
#include<vector>
#include<iostream>

class Buffer
{
public:
	class Slice
	{
	public:
		float *data;
		int x, y, w, h;

		Slice(float *dat, int ax, int ay, int aw, int ah)
		{
			data = dat;
			x = ax;
			y = ay;
			w = aw;
			h = ah;
		}
	};

private:
	float *color = nullptr;
	float *point = nullptr;
	int w = 0, h = 0;

	std::vector<Slice> slice;
	int slice_size = 4;

public:
	Buffer()
	{
		color = new float[4*w*h];
		point = new float[2*w*h];
	}
	~Buffer()
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

		/* Making slices of memory */
		slice.clear();
		int slice_number = (h + slice_size - 1)/slice_size;
		slice.reserve(slice_number);
		for(int i = 0; i < slice_number; ++i)
		{
			slice.push_back(Slice(color + 4*i*slice_size*w, 0, i*slice_size, w, slice_size));
		}
		int last_slice_size = (h % slice_size);
		if(last_slice_size == 0)
		{
			last_slice_size = slice_size;
		}
		slice[slice_number - 1].h = last_slice_size;
	}

	std::vector<Slice>::iterator begin()
	{
		return slice.begin();
	}

	std::vector<Slice>::iterator end()
	{
		return slice.end();
	}

	float *getPointData()
	{
		return point;
	}

	float *getColorData()
	{
		return color;
	}

	void save()
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
};

#endif // BUFFER_H
