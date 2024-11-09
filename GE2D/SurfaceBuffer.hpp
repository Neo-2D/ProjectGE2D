#pragma once

#include "Surface.hpp"

#include <vector>
#include <memory>

class SurfaceBuffer {
public:
	virtual void bufferizeSurface(std::unique_ptr<Surface>&&) = 0;
	virtual void clearSurfaceBuffer() = 0;
	virtual const std::vector<std::unique_ptr<Surface>>& getSurfaceBuffer() const = 0;
};