#ifndef GLOBALBUFFER_H
#define GLOBALBUFFER_H

#include<SDL2/SDL.h>
#include<GL/glew.h>

#include<4u/la/vec.hpp>
#include<vector>
#include<iostream>

#include<common/slice.h>

class GlobalBuffer
{
private:
	float *data = nullptr;
	int w = 0, h = 0;

	std::vector<Slice> slices;
	int slice_size = 1;

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
		slices.clear();
		int slice_number = (h + slice_size - 1)/slice_size;
		slices.reserve(slice_number);
		for(int j = 0; j < slice_number; ++j)
		{
			int i = slice_number/2 - (j*(j%2) - j/2);
			int last_slice_size = slice_size;
			if(i + 1 == slice_number)
			{
				last_slice_size = (h % slice_size);
				if(last_slice_size == 0)
				{
					last_slice_size = slice_size;
				}
			}
			slices.push_back(
						Slice(
							data + 4*i*slice_size*w,
							w,
							ivec4(0, w, i*slice_size, last_slice_size),
							vec4(-w, 2.0*w, 2.0*i*slice_size - h, 2.0*last_slice_size)/h
							)
						);
		}
	}

	std::vector<Slice>::iterator begin()
	{
		return slices.begin();
	}

	std::vector<Slice>::iterator end()
	{
		return slices.end();
	}

	void update(const Slice &slice)
	{
		for(int iy = 0; iy < slice.h(); ++iy)
		{
			for(int ix = 0; ix < slice.w(); ++ix)
			{
				for(int i = 0; i < 4; ++i)
				{
					data[4*((iy + slice.y())*w + (ix + slice.x())) + i] = slice.getPixel(ix,iy)[i];
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
