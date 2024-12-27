#include "EventHandler.hpp"

EventHandler::EventHandler(Window& window, Camera& camera, MouseHandler& mouseHandler)
    : m_window(window), m_camera(camera), m_mouseHandler(mouseHandler) {
    m_mapEditor = std::make_unique<MapEditor>(window);
}

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

        m_mapEditor->paint(event.motion.x, event.motion.y, "dirt");
    }

    m_mouseHandler.handleMouseMotion(event);
}

void EventHandler::handleMouseButtonDown(const SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseHandler.handleMouseButtonDown(event);
    }
    else if (event.button.button == SDL_BUTTON_LEFT) {
        isMouseHeldDown = true;
        m_mapEditor->paint(event.button.x, event.button.y, "dirt");
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
        m_window.getCamera().setCenter(Vector2D(0, 0));
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
