#pragma once

#include "GameObject.hpp"
#include "Surface.hpp"
#include "SurfaceBuffer.hpp"
#include <vector>
#include <memory>

class Game : public GameObject, public SurfaceBuffer {
private:
	std::vector<Surface*> m_surfaceBuffer;

public:
	Game() = default;

	void update() override;
	void init() override;

	virtual void bufferizeSurface(Surface& surface) override;
	virtual void clearSurfaceBuffer() override;
	virtual const std::vector<Surface*>& getSurfaceBuffer() const override;
};