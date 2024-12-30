#pragma once
#include "Vector2D.hpp"
#include "Window.hpp"
#include "EventHandler.hpp"
#include "Command.hpp"
#include "PaintCommand.hpp"
#include "EraseCommand.hpp"

#include <stack>

class Window;
class EventHandler;

class MapEditor
{
public:
    MapEditor(Window& window);
    ~MapEditor() = default;

    void paint(double x, double y);

    void erase(double x, double y);

    void undo();

    void addToUndoStack(std::unique_ptr<Command>&& command);

    Vector2D getSnappedCoordinates(double x, double y) const;

    void setCurrentPaintType(const std::string& type) { m_currentPaintType = type; }

    void nextPaintType();
    void previousPaintType();

private:
    Window& m_window;

    int m_currentPaintIndex = 0;
    std::vector<std::string> m_paintTypes;
    std::string m_currentPaintType;

    std::stack<std::unique_ptr<Command>> m_undoStack;
};


