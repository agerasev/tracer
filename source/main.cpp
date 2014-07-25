#include<SDL2/SDL.h>
#include<4u/window/glwindow.hpp>
#include"render/render.h"
#include"tracer/tracer.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
	GLWindow window("CRendAP",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
	Render render;
	Tracer tracer;
	render.setTracer(&tracer);
	window.setRender(&render);
	window.setListener(&render);
    window.start();
    SDL_Quit();
    return 0;
}
