#include<SDL2/SDL.h>

#include<4u/window/glwindow.hpp>
#include<4u/thread/thread.hpp>

#include<viewer/localviewer.h>
#include<worker/localworker.h>
#include<worker/disributor.h>
#include<director/director.h>


int main(int argc, char *argv[]) {

	SDL_Init(SDL_INIT_VIDEO);

	int threads = 1;

	GLWindow window("CRendAP",Window::Size(800,600),SDL_WINDOW_RESIZABLE);

	LocalViewer viewer;

	LocalWorker worker(2*threads);
	Distributor distributor(&worker);

	Director director;
	director.resize(800,600);
	Thread thread(&director);

	director.add(&worker);
	director.add(&viewer);

	window.setRender(&viewer);

	distributor.start(threads);
	thread.start();
	window.start();

	director.quit();
	worker.quit();
	thread.join();
	distributor.stop();

	SDL_Quit();

    return 0;
}
