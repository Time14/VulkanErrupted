#pragma once

#include <sdl\SDL.h>
#include <string>
#include <iostream>

namespace APIE
{

	class Display
	{
	public:
		Display(uint32_t width, uint32_t height, std::string title, bool vsync);
		~Display();

		void setRunPointer(void(*runPointer) (double delta));
		void setDrawPointer(void(*drawPointer) ());
		void setEventPointer(void(*eventPointer) (SDL_Event e));
		void setWindowTitle(std::string title);

		void setWindowWidth(uint16_t width);
		void setWindowHeigth(uint16_t height);
		void setWindowDimensions(uint16_t width, uint16_t height);

		std::string getWindowTitle();
		uint16_t getWindowWidth();
		uint16_t getWindowHeight();

		double getDelta();

		void run();
		void quit();

		SDL_Window* getWindow();
		SDL_Renderer* getRenderer();

	private:
		void updateDelta();
		void pollEvents();
		void updateWindowDimensions();
		
		uint16_t windowWidth = 0;
		uint16_t windowHeight = 0;

		SDL_Window* window;
		SDL_Renderer* renderer;

		uint32_t frames;
		uint32_t oldTime;
		double delta;

		bool running;
		std::string title;

		void(*runPointer) (double delta);
		void(*drawPointer) ();
		void(*eventPointer) (SDL_Event e);
	};

}