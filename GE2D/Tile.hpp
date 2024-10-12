#pragma once

#include <memory>
#include "Surface.hpp"

class Tile {
private:
	std::unique_ptr<Surface> m_surface;
	
public:
	Tile(std::unique_ptr<Surface> surface);
	virtual ~Tile() = default;

	Surface* const getSurface() const;
};