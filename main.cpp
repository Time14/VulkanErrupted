
#include <iostream>
#include <sdl/SDL.h>
#include "Display.h"
#include <math.h>
#undef main

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

APIE::Display* display;

void update(double tick)
{
	return;
}

void input(SDL_Event e)
{
	switch (e.type)
	{
		case(SDL_KEYUP) :
			std::cout << static_cast<char>(e.key.keysym.sym) << std::endl;
			std::cout << e.key.keysym.sym << std::endl;
			if (e.key.keysym.sym == 27)
			{
				display->setWindowDimensions(100, 50);
			}
			break;
		case(SDL_QUIT) :
			display->quit();
			break;
		default:
			break;
	}
}

void draw()
{
	SDL_Surface* surface();

	SDL_SetRenderDrawColor(display->getRenderer(), 0, 100, 0, 0);
	SDL_RenderClear(display->getRenderer());
	SDL_UpdateWindowSurface(display->getWindow());
	SDL_SetRenderDrawColor(display->getRenderer(), 255, 0, 0, 0);
	for (int i = 0; i < 25; i++)
	{
		SDL_Rect rect;

		rect.x = 100 + cos(0 + i * 2) * 50;
		rect.y = 100 + sin(0 + i * 2) * 50;
		rect.w = 100;
		rect.h = 100;

		SDL_RenderDrawRect(display->getRenderer(), &rect);
	}
	SDL_RenderPresent(display->getRenderer());
	SDL_Delay(16);
	return;
}

int main()
{
	display = new APIE::Display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "WORD!", false);
	display->setRunPointer(update);
	display->setDrawPointer(draw);
	display->setEventPointer(input);

	display->run();
	return 0;
}