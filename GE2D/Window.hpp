#pragma once

#include "GameObject.hpp"
#include "SurfaceBuffer.hpp"
#include "Camera.hpp"
#include "MouseHandler.hpp"
#include "EventHandler.hpp"
#include "MapEditor.hpp"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr int TILE_SIZE = 16;

class MapEditor;
class EventHandler;

class Window {
private:
	bool m_sdlInitialized = false;
	bool m_sdlImageInitialized = false;
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
    


    int m_windowWidth = WINDOW_WIDTH;
    int m_windowHeight = WINDOW_HEIGHT;

	SurfaceBuffer& m_surfaceBuffer;
	std::unordered_map<std::string, SDL_Texture*> m_textureCache;
	
	std::unique_ptr<MouseHandler> m_mouseHandler;

	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<EventHandler> m_eventHandler;
public:
	Window(SurfaceBuffer&);
	virtual ~Window();
	
	virtual bool init();
	virtual bool draw();
    void loadTextures();

	// Returns false if the window should close
	bool handleEvents();
	void handleMouseDrag(double dx, double dy);

    void setWidth(int width) { m_windowWidth = width; }
    void setHeight(int height) { m_windowHeight = height; }
    int getWidth() const { return m_windowWidth; }
    int getHeight() const { return m_windowHeight; }

    Camera& getCamera() { return *m_camera; }
};