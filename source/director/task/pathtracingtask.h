#ifndef PATHTRACINGTASK_H
#define PATHTRACINGTASK_H

#include<memory>
#include<common/task.h>
#include<render/params.h>
#include<render/algorithm/pathtracing.h>
#include<director/result/surfaceresult.h>

class PathTracingTask : public Task
{
private:
	PathTracing tracing;
	ivec4 bounds;
	vec4 coords;
	const RenderParams &params;
public:
	PathTracingTask(const ivec4 &b, const vec4 &c, const RenderParams &p)
		: bounds(b), coords(c), params(p)
	{

	}

	virtual std::unique_ptr<const Result> perform(
			const Scene *scene,
			ContRand &rand
			)
	{
		SurfaceResult *result = new SurfaceResult(bounds,coords);
		tracing.perform(scene,*result->getSurface(),params,rand);
		return std::unique_ptr<const Result>(result);
	}

	virtual void interrupt()
	{
		tracing.interrupt();
	}
};

#endif // PATHTRACINGTASK_H
