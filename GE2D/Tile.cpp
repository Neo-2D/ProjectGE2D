#include "Tile.hpp"

Tile::Tile(std::unique_ptr<Surface> surface) : m_surface(std::move(surface)) {}

Surface* const Tile::getSurface() const
{
	return m_surface.get();
}