#include "Window.hpp"

Window::Window(SurfaceBuffer& surfaceBuffer) : 
	m_surfaceBuffer(surfaceBuffer),
	m_camera(std::make_unique<Camera>()),
	m_mouseHandler(std::make_unique<MouseHandler>([this](double dx, double dy) { this->handleMouseDrag(dx, dy); }))
{
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

bool Window::init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	m_sdlInitialized = true;

	// Initialize SDL_image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}
	m_sdlImageInitialized = true;

	// Create a window
	m_window = SDL_CreateWindow("GE2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (m_window == nullptr) {
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create a renderer for the window
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

bool Window::update() {
	// Clear the screen (optional, based on your needs)
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	// Calculate the offsets to center the content on the screen
	double zoomFactor = m_camera->getZoom() / 16.0f + 1;
	int offsetX = static_cast<int>((m_windowWidth - (TILE_SIZE * zoomFactor)) / 2);
	int offsetY = static_cast<int>((m_windowHeight - (TILE_SIZE * zoomFactor)) / 2);

	// Draw surfaces from SurfaceBuffer
	const std::vector<std::unique_ptr<Surface>>& surfaces = m_surfaceBuffer.getSurfaceBuffer();
	for (const auto& surface : surfaces) {
		// Create a texture from the image
		SDL_Surface* sdlSurface = IMG_Load(surface->getPath().c_str());
		if (sdlSurface == nullptr) {
			std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
			return false;
		}

		SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(m_renderer, sdlSurface);
		SDL_FreeSurface(sdlSurface);
		if (!sdlTexture) {
			std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
			return false;
		}

		SDL_Rect rect{
			static_cast<int>(surface->getX() * TILE_SIZE * zoomFactor) + offsetX,
			static_cast<int>(surface->getY() * TILE_SIZE * zoomFactor) + offsetY,
			static_cast<int>(surface->getBaseWidth() * TILE_SIZE * zoomFactor),
			static_cast<int>(surface->getBaseHeight() * TILE_SIZE * zoomFactor)
		};
		SDL_RenderCopy(m_renderer, sdlTexture, nullptr, &rect);
		SDL_DestroyTexture(sdlTexture);
	}

	// Present the rendered frame to the screen
	SDL_RenderPresent(m_renderer);

	return true;
}

bool Window::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
		else if (event.type == SDL_MOUSEWHEEL) {
			bool zoomIn = event.wheel.y > 0;
			if (zoomIn) {
				m_camera->zoomIn();
			}
			else {
				m_camera->zoomOut();
			}
			std::cout << "Zoom: " << m_camera->getZoom() << std::endl;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			m_mouseHandler->handleMouseButtonDown(event);
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			m_mouseHandler->handleMouseButtonUp(event);
		}
		else if (event.type == SDL_MOUSEMOTION) {
			m_mouseHandler->handleMouseMotion(event);
		}

        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                m_windowWidth = event.window.data1;
                m_windowHeight = event.window.data2;
				SDL_Rect viewport;
				viewport.x = 0;
				viewport.y = 0;
				viewport.w = m_windowWidth;  // Use updated width
				viewport.h = m_windowHeight; // Use updated height
				SDL_RenderSetViewport(m_renderer, &viewport);
            }
        }

		const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

		// Check for continuous key presses
        bool keyPress = false;
		if (currentKeyStates[SDL_SCANCODE_W]) {
			m_camera->moveUp();
            keyPress = true;
		}

		if (currentKeyStates[SDL_SCANCODE_S]) {
			m_camera->moveDown();
            keyPress = true;
		}

		if (currentKeyStates[SDL_SCANCODE_A]) {
            m_camera->moveLeft();
            keyPress = true;
		}

		if (currentKeyStates[SDL_SCANCODE_D]) {
            m_camera->moveRight();
            keyPress = true;
		}

		// Output the camera center
        if (keyPress) {
            std::cout << "Camera center: " << m_camera->getCenter().x << ", " << m_camera->getCenter().y << std::endl;
        }
	}
	return true;
}

void Window::handleMouseDrag(double dx, double dy) {
	std::cout << "Mouse drag: " << dx << ", " << dy << std::endl;
}