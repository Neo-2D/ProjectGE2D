#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Window.hpp"
#include "Game.hpp"
#include "LevelLoader.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char** argv) {
	bool gameInitialized = Game::getInstance().init();
	if (!gameInitialized) {
		std::cerr << "Failed to initialize game" << std::endl;
		return 1;
	}

	Window window(Game::getInstance());

	bool windowInitialized = window.init();
	if (!windowInitialized) {
		std::cerr << "Failed to initialize window" << std::endl;
		return 1;
	}

	while (true) {
		std::cout << "bingbong" << std::endl;
		bool eventHandled = window.handleEvents();
		if (!eventHandled) {
			break;
		}

		bool gameUpdated = Game::getInstance().update();
		if (!gameUpdated) {
			std::cerr << "Failed to update game" << std::endl;
			return 1;
		}

		bool windowUpdated = window.update();
		if (!windowUpdated) {
			std::cerr << "Failed to update window" << std::endl;
			return 1;
		}
	}

    return 0;
}