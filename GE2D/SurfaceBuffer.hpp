#pragma once

#include "Surface.hpp"

#include <vector>

class SurfaceBuffer {
public:
	virtual void bufferizeSurface(Surface& surface) = 0;
	virtual void clearSurfaceBuffer() = 0;
	virtual const std::vector<Surface*>& getSurfaceBuffer() const = 0;
};