#include "Window.hpp"
#include "LevelLoader.hpp"

Window::Window(SurfaceBuffer& surfaceBuffer) : 
	m_surfaceBuffer(surfaceBuffer),
	m_camera(std::make_unique<Camera>()),
	m_mouseHandler(std::make_unique<MouseHandler>([this](double dx, double dy) { this->handleMouseDrag(dx, dy); })),
    m_eventHandler(std::make_unique<EventHandler>(*this, *m_camera, *m_mouseHandler))
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

bool Window::draw() {
	// Clear the screen (optional, based on your needs)
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	// Calculate the offsets to center the content on the screen
	//double zoomFactor = m_camera->getZoom() / 16.0f + 1;
	double zoomFactor = m_camera->getZoom();
    Vector2D center = m_camera->getCenter();
	int offsetX = static_cast<int>(m_camera->getCenter().x * TILE_SIZE * zoomFactor + m_windowWidth / 2.0f);
	int offsetY = static_cast<int>(m_camera->getCenter().y * TILE_SIZE * zoomFactor + m_windowHeight / 2.0f);

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

bool mouseHeldDown = false;

bool Window::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (!m_eventHandler->handleEvent(event)) {
			return false;
		}
	}

	return true;
}

void Window::handleMouseDrag(double dx, double dy) {
	m_camera->setCenter(
		{ float(m_camera->getCenter().x + dx / (TILE_SIZE * m_camera->getZoom())),
		float(m_camera->getCenter().y + dy / (TILE_SIZE * m_camera->getZoom())) }
	);
}