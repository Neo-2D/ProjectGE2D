#include "MapEditor.hpp"

void MapEditor::paint(double x, double y, const std::string& type)
{
    double zoomFactor = m_window.getCamera().getZoom();

    int offsetX = static_cast<int>(m_window.getCamera().getCenter().x * TILE_SIZE * zoomFactor + m_window.getWidth() / 2);
    int offsetY = static_cast<int>(m_window.getCamera().getCenter().y * TILE_SIZE * zoomFactor + m_window.getHeight() / 2);

    int adjustedX = x - offsetX;
    int adjustedY = y - offsetY;

    int snappedX = static_cast<int>(std::floor(adjustedX / (TILE_SIZE * zoomFactor)));
    int snappedY = static_cast<int>(std::floor(adjustedY / (TILE_SIZE * zoomFactor)));


    std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/" + type + ".png", 1, 1, snappedX, snappedY, type);
    Game::getInstance().bufferizeSurface(std::move(s));
    m_window.loadTextures();
}

void MapEditor::erase(double x, double y)
{
    double zoomFactor = m_window.getCamera().getZoom();
    int offsetX = static_cast<int>(m_window.getCamera().getCenter().x * TILE_SIZE * zoomFactor + m_window.getWidth() / 2);
    int offsetY = static_cast<int>(m_window.getCamera().getCenter().y * TILE_SIZE * zoomFactor + m_window.getHeight() / 2);
    int adjustedX = x - offsetX;
    int adjustedY = y - offsetY;
    int snappedX = static_cast<int>(std::floor(adjustedX / (TILE_SIZE * zoomFactor)));
    int snappedY = static_cast<int>(std::floor(adjustedY / (TILE_SIZE * zoomFactor)));
    //Game::getInstance().eraseSurface(snappedX, snappedY);
    m_window.loadTextures();
}
