#include "Game.hpp"

static int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

bool Game::update()
{
	return true;
}

bool Game::init()
{	
    LevelLoader::getInstance().loadLevel("testLevel");
	return true;
}

void Game::bufferizeSurface(std::unique_ptr<Surface>&& surface)
{
    for (const auto& s : m_surfaceBuffer) {
        if (s->getX() == surface->getX() && s->getY() == surface->getY()) {
            if (s->getType() != surface->getType()) {
                //Remove the surface and add the new one
                eraseSurface(surface->getX(), surface->getY());
                m_surfaceBuffer.push_back(std::move(surface));
            }
            return;
        }
    }
	m_surfaceBuffer.push_back(std::move(surface));
}

void Game::clearSurfaceBuffer()
{
	m_surfaceBuffer.clear();
}

void Game::eraseSurface(int x, int y)
{
    for (auto it = m_surfaceBuffer.begin(); it != m_surfaceBuffer.end(); ++it) {
        if ((*it)->getX() == x && (*it)->getY() == y) {
            m_surfaceBuffer.erase(it);
            return;
        }
    }

    //Need to replace the vector with an unordered_map to make this operation O(1)
    //It's getting slow with a lot of surfaces
}

const std::vector<std::unique_ptr<Surface>>& Game::getSurfaceBuffer() const
{
	return m_surfaceBuffer;
}
