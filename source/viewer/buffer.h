#ifndef BUFFER_H
#define BUFFER_H

#include<SDL2/SDL.h>
#include<GL/glew.h>

#include<4u/la/vec.hpp>
#include<vector>
#include<iostream>

#include<common/slice.h>

class Buffer
{
private:
	float *color = nullptr;
	float *point = nullptr;
	int w = 0, h = 0;

	std::vector<Slice> slice;
	int slice_size = 2;

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
		for(int iy = 0; iy < h; iy++) {
			for(int ix = 0; ix < w; ix++) {
				*(color + 4*(iy*w + ix))		= 0.0f;
				*(color + 4*(iy*w + ix) + 1)	= 0.0f;
				*(color + 4*(iy*w + ix) + 2)	= 0.0f;
				*(color + 4*(iy*w + ix) + 3)	= 0.0f;
			}
		}
		/* Making slices of memory */
		slice.clear();
		int slice_number = (h + slice_size - 1)/slice_size;
		slice.reserve(slice_number);
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
			slice.push_back(
						Slice(
							color + 4*i*slice_size*w,
							w,
							ivec4(0, w, i*slice_size, last_slice_size),
							vec4(-w, 2.0*w, 2.0*i*slice_size - h, 2.0*last_slice_size)/h
							)
						);
		}
	}

	std::vector<Slice>::iterator begin()
	{
		return slice.begin();
	}

	std::vector<Slice>::iterator end()
	{
		return slice.end();
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

	void update(const Slice &slice)
	{
		for(int iy = 0; iy < slice.h(); ++iy)
		{
			for(int ix = 0; ix < slice.w(); ++ix)
			{
				for(int i = 0; i < 4; ++i)
				{
					color[4*((iy + slice.y())*w + (ix + slice.x())) + i] = slice.getPixel(ix,iy)[i];
				}
			}
		}
	}
};

#endif // BUFFER_H
