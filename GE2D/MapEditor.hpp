#pragma once
#include "Window.hpp"
#include "EventHandler.hpp"



class Window;
class EventHandler;

class MapEditor
{
public:
    MapEditor(Window& window);
    ~MapEditor() = default;

    void paint(double x, double y);

    void erase(double x, double y);

    Vector2D getSnappedCoordinates(double x, double y) const;

    void setCurrentPaintType(const std::string& type) { m_currentPaintType = type; }

    void nextPaintType();
    void previousPaintType();

private:
    Window& m_window;

    int m_currentPaintIndex = 0;
    std::vector<std::string> m_paintTypes;
    std::string m_currentPaintType;
};


