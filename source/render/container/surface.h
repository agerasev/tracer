#ifndef SURFACE_H
#define SURFACE_H

#include<4u/la/vec.hpp>
#include<cstring>
#include<render/color.h>

class Surface
{
private:
	ivec4 bounds; /* (x,y,w,h) */
	vec4 coords; /* (left,width,down,height) */
	float *data;

public:
	Surface(const ivec4 &b, const vec4 &c) :
		  bounds(b),
		  coords(c),
		  data(new float[4*w()*h()])
	{

	}
	Surface(const float *d, const ivec4 &b, const vec4 &c) :
		  bounds(b),
		  coords(c),
		  data(new float[4*w()*h()])
	{
		memcpy(static_cast<void*>(data),static_cast<const void*>(d),4*sizeof(float)*w()*h());
	}
	Surface(const Surface &surface) :
		  bounds(surface.bounds),
		  coords(surface.coords),
		  data(new float[4*w()*h()])
	{
		memcpy(static_cast<void*>(data),static_cast<const void*>(surface.data),4*sizeof(float)*w()*h());
	}
	virtual ~Surface()
	{
		delete[] data;
	}
	Surface &operator = (const Surface &surface)
	{
		delete[] data;
		bounds = surface.bounds;
		coords = surface.coords;
		data = new float[4*w()*h()];
		memcpy(static_cast<void*>(data),static_cast<const void*>(surface.data),4*sizeof(float)*w()*h());

		return *this;
	}

	int x() const
	{
		return bounds[0];
	}
	int y() const
	{
		return bounds[1];
	}
	int w() const
	{
		return bounds[2];
	}
	int h() const
	{
		return bounds[3];
	}

	vec4 getPixel(int ax, int ay) const
	{
		float *src = data + 4*(ay*w() + ax);
		return vec4(src[0],src[1],src[2],src[3]);
	}
	void setPixel(const Color &pix, int ax, int ay)
	{
		float *dst = data + 4*(ay*w() + ax);
		dst[0] = pix.r();
		dst[1] = pix.g();
		dst[2] = pix.b();
		dst[3] = 1.0f;
	}

	ivec4 getBounds() const
	{
		return bounds;
	}

	vec2 getCoord(double ax, double ay) const
	{
		return vec2(coords[0] + ax*coords[1]/w(), coords[2] + ay*coords[3]/h());
	}
};

#endif // SURFACE_H
