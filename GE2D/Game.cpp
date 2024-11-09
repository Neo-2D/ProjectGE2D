#include "Game.hpp"

void Game::update()
{
}

void Game::init()
{
	std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/ship.png", 8, 8);
	bufferizeSurface(std::move(s));
}

void Game::bufferizeSurface(std::unique_ptr<Surface>&& surface)
{
	m_surfaceBuffer.push_back(std::move(surface));
}

void Game::clearSurfaceBuffer()
{
	m_surfaceBuffer.clear();
}

const const std::vector<std::unique_ptr<Surface>>& Game::getSurfaceBuffer() const
{
	return m_surfaceBuffer;
}
