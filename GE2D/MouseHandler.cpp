#include "MouseHandler.hpp"

void MouseHandler::handleMouseButtonDown(const SDL_Event& event)
{
	dragging = true;
	startingX = event.button.x;
	startingY = event.button.y;
}

void MouseHandler::handleMouseButtonUp(const SDL_Event& event)
{
	dragging = false;
}

void MouseHandler::handleMouseMotion(const SDL_Event& event)
{
	if (dragging) {
		float deltaX = event.motion.x - startingX;
		float deltaY = event.motion.y - startingY;

		startingX = event.motion.x;
		startingY = event.motion.y;

		if (onDrag) {
			onDrag(deltaX, deltaY);
		}
	}
}