#include "Display.h"

using namespace APIE;

Display::Display(uint32_t width, uint32_t height, std::string title, bool vsync)
{
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | (SDL_RENDERER_PRESENTVSYNC & vsync));
	running = true;
}


Display::~Display()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::setRunPointer(void(*run)(double delta))
{
	this->runPointer = run;
}

void Display::setDrawPointer(void(*drawPointer)())
{
	this->drawPointer = drawPointer;
}

void Display::setEventPointer(void(*eventPointer)(SDL_Event e))
{
	this->eventPointer = eventPointer;
}

void Display::setWindowTitle(std::string title)
{
	SDL_SetWindowTitle(window, title.c_str());
	this->title = title;
}

void APIE::Display::setWindowWidth(uint16_t width)
{
	windowWidth = width;
	updateWindowDimensions();
}

void APIE::Display::setWindowHeigth(uint16_t height)
{
	windowHeight = height;
	updateWindowDimensions();
}

void APIE::Display::setWindowDimensions(uint16_t width, uint16_t height)
{
	windowWidth = width;
	windowHeight = height;
	updateWindowDimensions();
}

std::string APIE::Display::getWindowTitle()
{
	return SDL_GetWindowTitle(window);
}

uint16_t APIE::Display::getWindowWidth()
{
	return windowWidth;
}

uint16_t APIE::Display::getWindowHeight()
{
	return windowHeight;
}

double APIE::Display::getDelta()
{
	return delta;
}

void Display::run()
{
	while (running)
	{
		updateDelta();
		(*runPointer)(delta);
		(*drawPointer)();

		pollEvents();
	}
}

void Display::quit()
{
	running = false;
}

SDL_Window * Display::getWindow()
{
	return window;
}

SDL_Renderer* Display::getRenderer()
{
	return renderer;
}

void Display::updateDelta()
{
	frames++;
	uint32_t time = SDL_GetTicks();

	//It's actually milliseconds!
	delta = (time - oldTime) / 1000;

	//If the program has run for more than 49 days, I felt we needed a fix.
	if (delta < 0)
	{
		delta = 1 / 60;
	}
	oldTime = time;
}

void Display::pollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		(*eventPointer)(e);
	}
}

void APIE::Display::updateWindowDimensions()
{
	SDL_SetWindowSize(window, windowWidth, windowHeight);
}
