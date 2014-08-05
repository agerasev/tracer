#include<SDL2/SDL.h>

#include<4u/window/glwindow.hpp>
#include<4u/thread/thread.hpp>

#include<viewer/localviewer.h>
#include<worker/localworker.h>
#include<worker/disributor.h>
#include<director/director.h>


int main(int argc, char *argv[]) {

	SDL_Init(SDL_INIT_VIDEO);

	/* Parameters needed for raytracing */
	TraceParams trace_params = {
		6,		/* recursion depth */
		{		/* spectator params */
			1		/* rays density */
		},
		{		/* scene params */
			2,		/* rays density */
			1,		/* attracting rays density */
		}
	};
	/* Parameters required by
	 * rendering infrastructure */
	RenderParams render_params =
	{
		2,		/* thread number */
		4,		/* detailing */
	};

	/* Traces performs ray tracing
	 * It's the heart of application */
	Tracer tracer(trace_params);

	/* Worker performs rendering operations and
	 * distributes them between threads */
	LocalWorker worker(&tracer,render_params);

	/* Viewer shows rendered images
	 * It's unnecessary to create it */
	LocalViewer viewer;

	/* Director distributes computations between workers
	 * and sends images to viewers
	 * It stores rendered data */
	Director director;
	director.resize(800,600);
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
