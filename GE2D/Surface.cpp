#include "Surface.hpp"

Surface::Surface(const std::string& path, const int baseWidth, const int baseHeight)
	: m_path(path), m_baseWidth(baseWidth), m_baseHeight(baseHeight) {}

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