#ifndef TRACEPARAMS_H
#define TRACEPARAMS_H

class TraceParams
{
public:
	class SpectatorParam
	{
	public:

	};
	class SceneParam
	{
	public:
		int rays_density;
		int recursion_depth;
	};

	SpectatorParam spectator;
	SceneParam scene;
};

#endif // TRACEPARAMS_H
