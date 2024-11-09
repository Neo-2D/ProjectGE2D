#include "Window.hpp"

Window::Window(SurfaceBuffer& surfaceBuffer) : m_surfaceBuffer(surfaceBuffer)
{
	init();
}

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

void Window::update() {
	// Clear the screen (optional, based on your needs)
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	// Draw surfaces from SurfaceBuffer
	const std::vector<std::unique_ptr<Surface>>& surfaces = m_surfaceBuffer.getSurfaceBuffer();
	for (const auto& surface : surfaces) {
		std::cout << surface->getPath() << std::endl;
		// Here you'd add code to render the surfaces onto the screen
	}

	// Draw a red square
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_Rect rect{ 100, 100, 100, 100 };
	SDL_RenderFillRect(m_renderer, &rect);

	// Present the rendered frame to the screen
	SDL_RenderPresent(m_renderer);
}

bool Window::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}
