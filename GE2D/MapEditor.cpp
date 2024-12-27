#include "MapEditor.hpp"
#include <iostream>
#include <filesystem>

MapEditor::MapEditor(Window& window) : m_window(window) 
{
    std::string directory = "assets/textures/tiles";

    namespace fs = std::filesystem;

    m_paintTypes.clear();

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.ends_with(".png")) {
                filename = filename.substr(0, filename.size() - 4);
                m_paintTypes.push_back(filename);
            }
        }
    }

    m_currentPaintType = m_paintTypes[m_currentPaintIndex];

    std::cout << "Paint types: ";
    for (const auto& type : m_paintTypes) {
        std::cout << type << " ";
    }
}

void MapEditor::paint(double x, double y)
{
    Vector2D snapped = getSnappedCoordinates(x, y);

    std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/textures/tiles/" + m_currentPaintType + ".png", 1, 1, snapped.x, snapped.y, m_currentPaintType);
    Game::getInstance().bufferizeSurface(std::move(s));
    m_window.loadTextures();
}

void MapEditor::erase(double x, double y)
{
    Vector2D snapped = getSnappedCoordinates(x, y);
    Game::getInstance().eraseSurface(snapped.x, snapped.y);
    m_window.loadTextures();
}

Vector2D MapEditor::getSnappedCoordinates(double x, double y) const
{
    double zoomFactor = m_window.getCamera().getZoom();

    int offsetX = static_cast<int>(m_window.getCamera().getCenter().x * TILE_SIZE * zoomFactor + m_window.getWidth() / 2.0f);
    int offsetY = static_cast<int>(m_window.getCamera().getCenter().y * TILE_SIZE * zoomFactor + m_window.getHeight() / 2.0f);

    int adjustedX = x - offsetX;
    int adjustedY = y - offsetY;

    int snappedX = static_cast<int>(std::floor(adjustedX / (TILE_SIZE * zoomFactor)));
    int snappedY = static_cast<int>(std::floor(adjustedY / (TILE_SIZE * zoomFactor)));

    return Vector2D(snappedX, snappedY);
}

void MapEditor::nextPaintType()
{
    m_currentPaintType = m_paintTypes[++m_currentPaintIndex % m_paintTypes.size()];
    std::cout << "Current paint type: " << m_currentPaintType << std::endl;
}

void MapEditor::previousPaintType()
{
    m_currentPaintType = m_paintTypes[--m_currentPaintIndex % m_paintTypes.size()];
    std::cout << "Current paint type: " << m_currentPaintType << std::endl;
}
