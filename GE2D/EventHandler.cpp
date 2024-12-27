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
    if (isLeftMouseHeldDown) {
        m_mapEditor->paint(event.motion.x, event.motion.y);
    }
    else if (isRightMouseHeldDown) {
        m_mapEditor->erase(event.motion.x, event.motion.y);
    }

    m_mouseHandler.handleMouseMotion(event);
}

void EventHandler::handleMouseButtonDown(const SDL_Event& event) {
    switch (event.button.button) {
    case SDL_BUTTON_LEFT:
        isLeftMouseHeldDown = true;
        m_mapEditor->paint(event.button.x, event.button.y);
        break;
    case SDL_BUTTON_RIGHT:
        isRightMouseHeldDown = true;
        m_mapEditor->erase(event.button.x, event.button.y);
        break;
    case SDL_BUTTON_MIDDLE:
        m_mouseHandler.handleMouseButtonDown(event);
        break;
    default:
        break;
    }
}

void EventHandler::handleMouseButtonUp(const SDL_Event& event) {
    switch (event.button.button) {
    case SDL_BUTTON_LEFT:
        isLeftMouseHeldDown = false;
        break;
    case SDL_BUTTON_RIGHT:
        isRightMouseHeldDown = false;
        break;
    case SDL_BUTTON_MIDDLE:
        m_mouseHandler.handleMouseButtonUp(event);
        break;
    default:
        break;
    }
}

void EventHandler::handleMouseWheel(const SDL_Event& event) {
    if (event.wheel.y > 0) {
        m_camera.zoomIn();
    }
    else {
        m_camera.zoomOut();
    }
}

void EventHandler::handleKeyDown(const SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_l:
        LevelLoader::getInstance().loadLevel("testLevel");
        m_window.getCamera().setCenter(Vector2D(0, 0));
        m_window.loadTextures();
        break;
    case SDLK_s:
        LevelLoader::getInstance().saveLevel();
        break;
    case SDLK_UP:
        m_mapEditor->nextPaintType();
        break;
    case SDLK_DOWN:
        m_mapEditor->previousPaintType();
        break;
    default:
        break;
    }
}

void EventHandler::handleWindowEvent(const SDL_Event& event) {
    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        m_window.setWidth(event.window.data1);
        m_window.setHeight(event.window.data2);
    }
}
