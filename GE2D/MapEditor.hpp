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

    void paint(double x, double y, const std::string& type);

    void erase(double x, double y);

private:
    Window& m_window;
};


