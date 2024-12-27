#include "Game.hpp"

bool Game::update()
{
	return true;
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

bool Game::init()
{	
	return true;
}

void Game::bufferizeSurface(std::unique_ptr<Surface>&& surface)
{
    for (const auto& s : m_surfaceBuffer) {
        if (s->getX() == surface->getX() && s->getY() == surface->getY()) {
            return;
        }
    }
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
