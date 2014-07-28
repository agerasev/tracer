#ifndef TRACEPARAMS_H
#define TRACEPARAMS_H

class TraceParams
{
public:
	int recursion_depth;

	class SpectatorParam
	{
	public:

	};
	class SceneParam
	{
	public:
		int rays_density;
		double min_ray_intensity;
	};

	SpectatorParam spectator;
	SceneParam scene;
};

#endif // TRACEPARAMS_H
