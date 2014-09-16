#include<SDL2/SDL.h>
#include<4u/window/glwindow.hpp>

int main(int,char*[])
{
	SDL_Init(SDL_INIT_VIDEO);

	GLWindow *win = new GLWindow("Flow",Window::Size(800,600));

	win->start();

	delete win;

	SDL_Quit();
}
