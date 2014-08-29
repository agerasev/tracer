#include<SDL2/SDL.h>

#include<4u/window/glwindow.hpp>
#include<4u/thread/thread.hpp>
#include<4u/complex/quaternion.hpp>

#include<viewer/localviewer.h>
#include<worker/localworker.h>
#include<worker/disributor.h>
#include<director/director.h>

#include<render/params.h>
#include<render/scene.h>

#include<render/spectator/pointspectator.h>
#include<render/spectator/planespectator.h>

#include<render/object/sphere.h>
#include<render/object/polygon.h>
#include<render/object/materialobject.h>
#include<render/object/distanceobject.h>
#include<render/object/mandelbrotset.h>
#include<render/object/juliaset.h>
#include<render/object/functional.h>

#include<render/material/specularmaterial.h>
#include<render/material/transparentmaterial.h>
#include<render/material/diffusematerial.h>
#include<render/material/glowingmaterial.h>
#include<render/material/emittingmaterial.h>
#include<render/material/hybridmaterial.h>
#include<render/material/anisotropicdiffusematerial.h>

int main(int, char *[]) {

	SDL_Init(SDL_INIT_VIDEO);

	/* Parameters needed for raytracing */
	RenderParams render_params = {
		1,		/* detailing */
		2,		/* recursion depth */
		{		/* scene primary parameters */
			4,		/* diffuse rays number */
			4,		/* emitting rays number */
		},
		{		/* scene secondary parameters */
			0,		/* diffuse rays number */
			1,		/* emitting rays number */
		}
	};

	/* Worker thread number */
	int threads = 2;

	/* Scene initializing */
	Scene scene;
	// scene.setSpectator(new PlaneSpectator(vec3(0,0,0),unimat3,0.4,4.0,0.02));
	scene.setSpectator(new PointSpectator(vec3(0,0,0),unimat3));

	scene.addObject(
				new MaterialObject<MandelbrotSet<0x9>>(
					new HybridMaterial{
						std::pair<const Material*,double>(new SpecularMaterial(WHITE),0.1),
						std::pair<const Material*,double>(new DiffuseMaterial(Color(1,0.9,0)),0.9)
					},
					vec3(0,-0.64,-3.6),
					2.0
					)
				);
	// mat3(std::initializer_list<double>{ S32,0,0.5, 0,1,0, -0.5,0,S32 }),
	// quaternion(-0.6,0.6,0.0,0.0),

	/*
	scene.addObject(new MaterialObject<Quad>(
						new DiffuseMaterial(WHITE*0.6),
						vec3(0,-1,-6),
						vec3(0,1,0),
						std::initializer_list<vec3>{vec3(8,-1,2),vec3(8,-1,-14),vec3(-8,-1,-14),vec3(-8,-1,2)}
						));
	*/

	Sphere *omni1 = new MaterialObject<Sphere>(new EmittingMaterial(Color(32,32,16)),vec3(2,5,-3),0.8);
	scene.addObject(omni1);
	scene.addEmitter(omni1);

	Sphere *omni2 = new MaterialObject<Sphere>(new EmittingMaterial(Color(2,2,2)),vec3(-3,-5,-2),1.6);
	scene.addObject(omni2);
	scene.addEmitter(omni2);

	/* Worker performs rendering operations and
	 * distributes them between threads */
	LocalWorker worker(&scene,threads);

	/* Viewer shows rendered images
	 * It's unnecessary to create it */
	LocalViewer viewer;

	/* Director distributes computations between workers
	 * and sends images to viewers
	 * It stores rendered data */
	Director director;
	director.resize(800,600);
	director.setParams(render_params);
	Thread thread(&director);

	/* Binds worker and viewer to director */
	director.add(&worker);
	director.add(&viewer);

	/* Creates window and sets render */
	GLWindow window("Tracer",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
	window.setRender(&viewer);

	/* Starts threads */
	worker.start();
	thread.start();

	/* Joins main loop */
	window.start();

	/* Sends signal you want to quit */
	director.quit();
	worker.quit();

	/* Waiting for threads */
	thread.join();
	worker.wait();

	SDL_Quit();

    return 0;
}
