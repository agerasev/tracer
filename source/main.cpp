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

#include<render/spectator/planespectator.h>

#include<render/object/sphere.h>
#include<render/object/polygon.h>
#include<render/object/materialobject.h>
#include<render/object/distanceobject.h>

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
		2,		/* detailing */
		2,		/* recursion depth */
		{		/* scene parameters */
			2,		/* diffuse rays number */
			1,		/* emitting rays number */
		}
	};

	/* Worker thread number */
	int threads = 2;

	/* Scene initializing */
	Scene scene;
	scene.setSpectator(new PlaneSpectator(vec3(0,0,0),unimat3,0.4,5.0,0.0));

	scene.addObject(
				new MaterialObject<DistanceObject>(
					/* new HybridMaterial{
						std::pair<const Material*,double>(new SpecularMaterial(WHITE),0.1),
						std::pair<const Material*,double>(new DiffuseMaterial(Color(0.4,1,0.4)),0.9)
					},*/
					new DiffuseMaterial(WHITE),
					vec3(-0.2,0,-3),
					2.0,
					[](const vec3 &pos)
					{
						typedef complex<complex<double>> qtr;
						vec3 x(S32,0,0.5),y(0,1,0),z(-0.5,0,S32);
						qtr a(pos*x,pos*y,pos*z,0.0), c(-0.5,0.6,0.4,0.0);
						int i = 0;
						const int iter = 0xa;
						for(; i < iter; ++i)
						{
							a = a*a + c;
							if(abs2(a).r() > 4.0)
							{
								break;
							}
						}
						return (4.0*(iter - i - 1) + abs2(a).r() - 4.0)/(8.0*iter);
					}
					)
				);
	/*
	scene.addObject(new MaterialObject<Quad>(
						new DiffuseMaterial(WHITE),
						vec3(0,-1,-6),
						vec3(0,1,0),
						std::initializer_list<vec3>{vec3(8,-1,2),vec3(8,-1,-14),vec3(-8,-1,-14),vec3(-8,-1,2)}
						));
	*/

	Sphere *omni1 = new MaterialObject<Sphere>(new EmittingMaterial(Color(512,512,256)),vec3(2,5,-3),0.2);
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
