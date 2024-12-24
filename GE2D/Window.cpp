#include "Window.hpp"
#include "LevelLoader.hpp"

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

    loadTextures();

	return true;
}

void Window::loadTextures() {
    m_textureCache.clear();
	const auto& surfaces = m_surfaceBuffer.getSurfaceBuffer();
	for (const auto& surface : surfaces) {
		const std::string& path = surface->getPath();
		if (m_textureCache.find(path) == m_textureCache.end()) {
			SDL_Surface* sdlSurface = IMG_Load(path.c_str());
			if (!sdlSurface) {
				std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
				continue;
			}
			SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, sdlSurface);
			SDL_FreeSurface(sdlSurface);
			if (!texture) {
				std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
				continue;
			}
			m_textureCache[path] = texture;
		}
	}
}

bool Window::update() {
	// Clear the screen (optional, based on your needs)
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	// Calculate the offsets to center the content on the screen
	//double zoomFactor = m_camera->getZoom() / 16.0f + 1;
	double zoomFactor = m_camera->getZoom();
    Vector2D center = m_camera->getCenter();
	int offsetX = static_cast<int>(m_camera->getCenter().x * TILE_SIZE * zoomFactor + m_windowWidth / 2);
	int offsetY = static_cast<int>(m_camera->getCenter().y * TILE_SIZE * zoomFactor + m_windowHeight / 2);

	// Draw surfaces from SurfaceBuffer
	const std::vector<std::unique_ptr<Surface>>& surfaces = m_surfaceBuffer.getSurfaceBuffer();
	for (const auto& surface : surfaces) {
        SDL_Texture* sdlTexture = m_textureCache[surface->getPath()];
        if (!sdlTexture) {
            std::cerr << "Failed to get texture from cache" << std::endl;
            return false;
        }

		SDL_Rect rect{
			static_cast<int>(surface->getX() * TILE_SIZE * zoomFactor) + offsetX,
			static_cast<int>(surface->getY() * TILE_SIZE * zoomFactor) + offsetY,
			static_cast<int>(surface->getBaseWidth() * TILE_SIZE * zoomFactor),
			static_cast<int>(surface->getBaseHeight() * TILE_SIZE * zoomFactor)
		};
		SDL_RenderCopy(m_renderer, sdlTexture, nullptr, &rect);
	}

	// Present the rendered frame to the screen
	SDL_RenderPresent(m_renderer);

	return true;
}

bool Window::handleEvents()
{
    LevelLoader levelLoader;

	double zoomFactor = m_camera->getZoom();
	Vector2D center = m_camera->getCenter();
	int offsetX = static_cast<int>(m_camera->getCenter().x * TILE_SIZE * zoomFactor + m_windowWidth / 2);
	int offsetY = static_cast<int>(m_camera->getCenter().y * TILE_SIZE * zoomFactor + m_windowHeight / 2);

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
			if (event.button.button == SDL_BUTTON_MIDDLE)
				m_mouseHandler->handleMouseButtonDown(event);
            else if (event.button.button == SDL_BUTTON_LEFT) {
                // Testing Code for adding a texture to the texture buffer with a mouse click
				int adjustedX = event.button.x - offsetX;
				int adjustedY = event.button.y - offsetY;

				int snappedX = static_cast<int>(std::floor(adjustedX / 16.0));
				int snappedY = static_cast<int>(std::floor(adjustedY / 16.0));

				std::cout << "Mouse click at: " << adjustedX << ", " << adjustedY << std::endl;
				std::cout << "Mouse click snapped to tile: " << snappedX << ", " << snappedY << std::endl;

				std::string type = "dirt";

				std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/" + type + ".png", 1, 1, snappedX, snappedY);
                Game::getInstance().bufferizeSurface(std::move(s));
                loadTextures();
            }
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_MIDDLE)
				m_mouseHandler->handleMouseButtonUp(event);
		}
		else if (event.type == SDL_MOUSEMOTION) {
			m_mouseHandler->handleMouseMotion(event);
		}

        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                m_windowWidth = event.window.data1;
                m_windowHeight = event.window.data2;
            }
        }

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_g) {
				levelLoader.loadLevel("testLevel2");
                loadTextures();
			}
		}
	}
	return true;
}

void Window::handleMouseDrag(double dx, double dy) {
	std::cout << "Mouse drag: " << dx << ", " << dy << std::endl;
	m_camera->setCenter(
		{ float(m_camera->getCenter().x + dx / (TILE_SIZE)),
		float(m_camera->getCenter().y + dy / (TILE_SIZE)) }
	);
}