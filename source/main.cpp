#include<SDL2/SDL.h>
#include<4u/window/glwindow.hpp>
#include"render/render.h"
#include"tracer/tracer.h"
//#include"render/disributor.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
	GLWindow window("CRendAP",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
	Render render;
	Tracer tracer;
	//Distributor distrib(&render);
	render.setTracer(&tracer);
	window.setRender(&render);
	window.setListener(&render);
	//distrib.start(1);
    window.start();
	//distrib.stop();
    SDL_Quit();
    return 0;
}
