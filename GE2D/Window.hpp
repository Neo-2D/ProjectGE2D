#pragma once

#include "GameObject.hpp"
#include "SurfaceBuffer.hpp"
#include "Camera.hpp"
#include "MouseHandler.hpp"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define TILE_SIZE 16

class Window : public GameObject {
private:
	bool m_sdlInitialized = false;
	bool m_sdlImageInitialized = false;
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

    int m_windowWidth = WINDOW_WIDTH;
    int m_windowHeight = WINDOW_HEIGHT;

	SurfaceBuffer& m_surfaceBuffer;
	
	std::unique_ptr<MouseHandler> m_mouseHandler;

	std::unique_ptr<Camera> m_camera;
public:
	Window(SurfaceBuffer&);
	virtual ~Window();
	
	virtual bool init() override;
	virtual bool update() override;

	// Returns false if the window should close
	bool handleEvents();
	void handleMouseDrag(double dx, double dy);
};