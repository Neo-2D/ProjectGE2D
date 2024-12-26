#pragma once
#include "Window.hpp"
#include "EventHandler.hpp"

class Window;
class EventHandler;

class MapEditor
{
public:
    MapEditor(Window& window) : m_window(window) {}
    ~MapEditor() = default;

private:
    Window& m_window;
};


