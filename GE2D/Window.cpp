#include "Window.hpp"

Window::~Window()
{
	if (m_sdlImageInitialized) {
		IMG_Quit();
	}

	if (m_sdlInitialized) {
		SDL_Quit();
	}

	if (m_window != nullptr) {
		SDL_DestroyWindow(m_window);
	}

	if (m_renderer != nullptr) {
		SDL_DestroyRenderer(m_renderer);
	}
}

void Window::init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
	}
	m_sdlInitialized = true;

	// Initialize SDL_image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
	}
	m_sdlImageInitialized = true;

	// Create a window
	m_window = SDL_CreateWindow("GE2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) {
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
	}

	// Create a renderer for the window
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
	}
}
