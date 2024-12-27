#include <iostream>

#pragma warning(push)
#pragma warning(disable: 4061) // Replace with the specific warning code for fallthrough
#pragma warning(disable: 26819) // Disable MSVC-specific analyzer warnings for fallthrough

#include <SDL_stdinc.h>

#pragma warning(pop)

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

    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "Keybindings:" << std::endl;
    std::cout << "- L: Load level" << std::endl;
    std::cout << "- S: Save level" << std::endl;
    std::cout << "- Left mouse button: Paint" << std::endl;
    std::cout << "- Right mouse button: Erase" << std::endl;
    std::cout << "- Middle mouse button: Drag" << std::endl;
    std::cout << "- Scroll wheel: Zoom" << std::endl;
    std::cout << "--------------------------------------------------\n" << std::endl;

	while (true) {
		//Clear the console

		bool eventHandled = window.handleEvents();
		if (!eventHandled) {
			break;
		}

		bool gameUpdated = Game::getInstance().update();
		if (!gameUpdated) {
			std::cerr << "Failed to update game" << std::endl;
			return 1;
		}

		bool windowUpdated = window.draw();
		if (!windowUpdated) {
			std::cerr << "Failed to update window" << std::endl;
			return 1;
		}
	}

    return 0;
}