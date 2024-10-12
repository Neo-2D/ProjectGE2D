#include "Game.hpp"

void Game::update()
{
}

void Game::init()
{
}

void Game::bufferizeSurface(Surface& surface)
{
	m_surfaceBuffer.push_back(&surface);
}

void Game::clearSurfaceBuffer()
{
	m_surfaceBuffer.clear();
}

const std::vector<Surface*>& Game::getSurfaceBuffer() const
{
	return m_surfaceBuffer;
}
