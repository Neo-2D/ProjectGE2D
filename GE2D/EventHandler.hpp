#pragma once
#include "Window.hpp"
#include "Camera.hpp"
#include "MouseHandler.hpp"
#include "LevelLoader.hpp"
#include "MapEditor.hpp"

#include <SDL.h>

class Window;
class MapEditor;

class EventHandler {
public:
    EventHandler(Window& window, Camera& camera, MouseHandler& mouseHandler);

    bool handleEvent(const SDL_Event& event);

private:
    Window& m_window;
    Camera& m_camera;
    MouseHandler& m_mouseHandler;
    std::unique_ptr<MapEditor> m_mapEditor;
    bool isLeftMouseHeldDown = false;
    bool isRightMouseHeldDown = false;

    void handleMouseMotion(const SDL_Event& event);
    void handleMouseButtonDown(const SDL_Event& event);
    void handleMouseButtonUp(const SDL_Event& event);
    void handleMouseWheel(const SDL_Event& event);
    void handleKeyDown(const SDL_Event& event);
    void handleWindowEvent(const SDL_Event& event);
};


