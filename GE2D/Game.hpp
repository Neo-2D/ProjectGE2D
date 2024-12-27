#pragma once

#include "GameObject.hpp"
#include "Surface.hpp"
#include "SurfaceBuffer.hpp"
#include "LevelLoader.hpp"
#include <vector>
#include <memory>

class Game : public GameObject, public SurfaceBuffer {
private:
	std::vector<std::unique_ptr<Surface>> m_surfaceBuffer;

	Game() = default;
public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	static Game& getInstance() {
		static Game instance;
		return instance;
	}

	bool update() override;
	bool init() override;

	virtual void bufferizeSurface(std::unique_ptr<Surface>&& surface) override;
	virtual void clearSurfaceBuffer() override;
    void eraseSurface(int x, int y);
	virtual const std::vector<std::unique_ptr<Surface>>& getSurfaceBuffer() const override;
};