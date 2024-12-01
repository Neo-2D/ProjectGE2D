#include "Surface.hpp"

Surface::Surface(const std::string& path, const int baseWidth, const int baseHeight, const float x, const float y)
	: m_path(path), m_baseWidth(baseWidth), m_baseHeight(baseHeight), m_x(x), m_y(y) {}

const std::string& Surface::getPath() const {
	return m_path;
}

int Surface::getBaseWidth() const
{
	return m_baseWidth;
}

int Surface::getBaseHeight() const
{
	return m_baseHeight;
}

float Surface::getX() const
{
	return m_x;
}

float Surface::getY() const
{
	return m_y;
}
