#pragma once
#include <functional>
#include <SDL_image.h>

class MouseHandler {
private:
	bool dragging = false;
	float startingX = 0.0, startingY = 0.0;
	std::function<void(float, float)> onDrag;

public:
	explicit MouseHandler(std::function<void(float, float)> onDrag) : onDrag(onDrag) {}

	void handleMouseButtonDown(const SDL_Event& event);
	void handleMouseButtonUp(const SDL_Event& event);
	void handleMouseMotion(const SDL_Event& event);
};