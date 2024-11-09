#pragma once

#include "GameObject.hpp"
#include "SurfaceBuffer.hpp"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class Window : public GameObject {
private:
	bool m_sdlInitialized = false;
	bool m_sdlImageInitialized = false;
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	SurfaceBuffer& m_surfaceBuffer;
public:
	Window(SurfaceBuffer&);
	virtual ~Window();
	
	virtual void init() override;
	virtual void update() override;

	// Returns false if the window should close
	bool handleEvents();
};