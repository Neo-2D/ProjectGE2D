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
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0) {
				std::unique_ptr<Surface> s = std::make_unique<Surface>("assets/dirt.png", 1, 1, i, j);
				bufferizeSurface(std::move(s));
			}
		}
	}

	return true;
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
