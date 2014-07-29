#include<SDL2/SDL.h>
#include<4u/window/glwindow.hpp>
#include<viewer/localviewer.h>
#include<worker/localworker.h>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
	GLWindow window("CRendAP",Window::Size(800,600),SDL_WINDOW_RESIZABLE);
	LocalViewer viewer;
	LocalWorker worker;
	viewer.setWorker(&worker);
	window.setRender(&viewer);
	window.start();
    SDL_Quit();
    return 0;
}
