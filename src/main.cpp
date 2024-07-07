#include <iostream>
#include <SDL2/SDL.h>
#include "3DRenderer.h"
#include <vector>

// cube
Shape3D cube({
	{0.0, 0.0, 0.0}, {50.0, 0.0, 0.0},
	{0.0, -50.0, 0.0}, {50.0, -50.0, 0.0},
	{0.0, 0.0, 50.0}, {50.0, 0.0, 50.0},
	{0.0, -50.0, 50}, {50.0, -50.0, 50.0}
}, {
	{0, 1}, {0, 2}, {0, 4},
	{1, 5}, {1, 3},
	{2, 3}, {2, 6},
	{3, 7},
	{4, 6}, {4, 5},
	{6, 7}, {5, 7}
});

// pyramid
Shape3D pyramid({
{
    {100.0, 100.0, 100.0}, {50.0, 50.0, 0}, {50.0, 150.0, 0},
    {150.0, 50.0, 0}, {150.0, 150.0, 0}
},
{
    {0, 1}, {0, 2},
    {0, 3}, {0, 4},
    {1, 3}, {3, 4},
    {2, 4}, {1, 2}
}
});

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
Renderer3D *renderer_3d;
bool running = true;

int main() {
    SDL_Init( SDL_INIT_VIDEO );
    window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    renderer = SDL_CreateRenderer(window, 0, 0);

    renderer_3d = new Renderer3D(window, renderer);



	std::vector<Shape3D> shapes = {cube, pyramid};
    while (running) {
		const Uint8* keystates = SDL_GetKeyboardState(NULL);
    	renderer_3d->renderShapes(shapes);
        if (SDL_QuitRequested() || keystates[SDL_SCANCODE_Q]) { running = false; break;}
		if (keystates[SDL_SCANCODE_P]) {
		    renderer_3d->pauseRotation();
		}
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
