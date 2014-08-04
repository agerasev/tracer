#ifndef TRACEPARAMS_H
#define TRACEPARAMS_H

class TraceParams
{
public:
	int recursion_depth;

	class SpectatorParam
	{
	public:
		int rays_density;
	};
	class SceneParam
	{
	public:
		int rays_density;
		int emitting_rays_density;
	};

	SpectatorParam spectator;
	SceneParam scene;
};

#endif // TRACEPARAMS_H
