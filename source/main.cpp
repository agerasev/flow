#include<SDL2/SDL.h>
#include<4u/window/glwindow.hpp>
#include"simulator.hpp"

int main(int,char*[])
{
	SDL_Init(SDL_INIT_VIDEO);

	GLWindow *win = new GLWindow("Flow",Window::Size(400,300));
	Simulator *sim = new Simulator();

	win->setRender(sim);
	win->setListener(sim);

	win->start();

	delete sim;
	delete win;

	SDL_Quit();
}
