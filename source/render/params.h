#ifndef PARAMS_H
#define PARAMS_H

#include<4u/thread/threadlocalstorage.hpp>

struct SceneParams
{
	/* Number of rays */
	int diffuse_rays;
	int emitting_rays;

};

struct RenderParams
{
	int detailing;
	int recursion_depth;
	SceneParams scene;
};

#endif // PARAMS_H
