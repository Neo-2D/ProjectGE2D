#include "EventHandler.hpp"

bool EventHandler::handleEvent(const SDL_Event& event) {
    switch (event.type) {
    case SDL_QUIT:
        return false;
    case SDL_MOUSEMOTION:
        handleMouseMotion(event);
        break;
    case SDL_MOUSEBUTTONDOWN:
        handleMouseButtonDown(event);
        break;
    case SDL_MOUSEBUTTONUP:
        handleMouseButtonUp(event);
        break;
    case SDL_MOUSEWHEEL:
        handleMouseWheel(event);
        break;
    case SDL_KEYDOWN:
        handleKeyDown(event);
        break;
    case SDL_WINDOWEVENT:
        handleWindowEvent(event);
        break;
    default:
        break;
    }
    return true;
}

void EventHandler::handleMouseMotion(const SDL_Event& event) {
    if (isMouseHeldDown) {
        // Testing Code for adding a texture to the texture buffer with a mouse click
        double zoomFactor = m_camera.getZoom();
        int offsetX = static_cast<int>(m_camera.getCenter().x * TILE_SIZE * zoomFactor + m_window.getWidth() / 2);
        int offsetY = static_cast<int>(m_camera.getCenter().y * TILE_SIZE * zoomFactor + m_window.getHeight() / 2);

        int adjustedX = event.motion.x - offsetX;
        int adjustedY = event.motion.y - offsetY;
        int snappedX = static_cast<int>(std::floor(adjustedX / (TILE_SIZE * zoomFactor)));
        int snappedY = static_cast<int>(std::floor(adjustedY / (TILE_SIZE * zoomFactor)));

        std::string type = "dirt";
        std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/" + type + ".png", 1, 1, snappedX, snappedY, type);
        Game::getInstance().bufferizeSurface(std::move(s));
        m_window.loadTextures();
    }

    m_mouseHandler.handleMouseMotion(event);
}

void EventHandler::handleMouseButtonDown(const SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseHandler.handleMouseButtonDown(event);
    }
    else if (event.button.button == SDL_BUTTON_LEFT) {
        isMouseHeldDown = true;
        handleMouseMotion(event);
    }
}

void EventHandler::handleMouseButtonUp(const SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseHandler.handleMouseButtonUp(event);
    }
    else if (event.button.button == SDL_BUTTON_LEFT) {
        isMouseHeldDown = false;
    }
}

void EventHandler::handleMouseWheel(const SDL_Event& event) {
    if (event.wheel.y > 0) {
        m_camera.zoomIn();
    }
    else {
        m_camera.zoomOut();
    }
    std::cout << "Zoom: " << m_camera.getZoom() << std::endl;
}

#include <thread>
#include <chrono>

void EventHandler::handleKeyDown(const SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_l) {
        std::cout << "Loading level: " << "testLevel" << std::endl;
        LevelLoader::getInstance().loadLevel("testLevel");
        m_window.loadTextures();
    }
    else if (event.key.keysym.sym == SDLK_s) {
        LevelLoader::getInstance().saveLevel();
    }
}

void EventHandler::handleWindowEvent(const SDL_Event& event) {
    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        m_window.setWidth(event.window.data1);
        m_window.setHeight(event.window.data2);
    }
}
