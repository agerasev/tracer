#ifndef SURFACERESULT_H
#define SURFACERESULT_H

#include<common/result.h>
#include<render/container/surface.h>

const unsigned int TYPE_RESULT_SURFACE = 0x1;

class SurfaceResult : public Result
{
private:
	Surface *surface;
public:
	SurfaceResult(const ivec4 &bounds, const vec4 &coords)
		: Result(TYPE_RESULT_SURFACE)
	{
		surface = new Surface(bounds,coords);
	}
	virtual ~SurfaceResult()
	{
		delete surface;
	}

	Surface *getSurface()
	{
		return surface;
	}
	const Surface *getSurface() const
	{
		return surface;
	}
};

#endif // SURFACERESULT_H
