#include<SDL2/SDL.h>
#include"window/glwindow.h"
#include"renderer/renderer.h"
#include"tracer/tracer.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
	GLWindow window("CRendAP",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
	Renderer renderer;
	Tracer tracer;
	renderer.setTracer(&tracer);
	window.setRenderer(&renderer);
	window.setListener(&renderer);
    window.start();
    SDL_Quit();
    return 0;
}
