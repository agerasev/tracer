#ifndef SLICE_H
#define SLICE_H

#include<4u/la/vec.hpp>

/* Holds a valid pointer to data segment
 * And have bounds of this segment.
 * Slices are used for data transmission */

class Slice
{
private:
	float *_data;
	int _pitch;
	ivec4 _bounds; /* (x,w,y,h) */
	vec4 _coords; /* (left,width,down,height) */

protected:
	float *getData()
	{
		return _data;
	}
	void setData(float *d)
	{
		_data = d;
	}

public:
	Slice()
	{

	}
	Slice(float *data, int pitch, ivec4 __bounds__, vec4 __coords__)
		:
		  _data(data), _pitch(pitch),
		  _bounds(__bounds__),
		  _coords(__coords__)
	{

	}

	virtual ~Slice()
	{

	}

	int x() const
	{
		return _bounds[0];
	}
	int y() const
	{
		return _bounds[2];
	}
	int w() const
	{
		return _bounds[1];
	}
	int h() const
	{
		return _bounds[3];
	}

	vec4 getPixel(int ax, int ay) const
	{
		float *src = _data + 4*(ay*_pitch + ax);
		return vec4(src[0],src[1],src[2],src[3]);
	}
	void setPixel(const vec4 &pix, int ax, int ay)
	{
		float *dst = _data + 4*(ay*_pitch + ax);
		dst[0] = pix[0];
		dst[1] = pix[1];
		dst[2] = pix[2];
		dst[3] = pix[3];
	}

	ivec4 getBounds() const
	{
		return _bounds;
	}

	vec2 getCoord(double ax, double ay) const
	{
		return vec2(_coords[0] + ax*_coords[1]/w(), _coords[2] + ay*_coords[3]/h());
	}
};

#endif // SLICE_H
