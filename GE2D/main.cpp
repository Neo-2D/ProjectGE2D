#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char** argv) {
	// Load an image
	SDL_Surface* tileSurface = IMG_Load("assets/dirt.png");
	if (tileSurface == nullptr) {
		std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		IMG_Quit();
		return 1;
	}

	// Create a texture from the image
	SDL_Texture* tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
	SDL_FreeSurface(tileSurface);
	if (!tileTexture) {
		std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		IMG_Quit();
		return 1;
	}

	bool running{ true };
	SDL_Event event;
	double zoomFactor{ 1.0 };
	int dragging{ false };
	double startingX{ 0.0 }, startingY{ 0.0 };
	double offsetX{ 0.0 }, offsetY{ 0.0 };

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if (event.type == SDL_MOUSEWHEEL) {
				bool zoomIn = event.wheel.y > 0;
				if (zoomIn) {
					zoomFactor += 0.2;
				}
				else {
					zoomFactor = std::max(1.0, zoomFactor - 0.2);
				}
				std::cout << "Zoom factor: " << zoomFactor << std::endl;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (!dragging) {
						std::cout << "dragging = true" << std::endl;
					}

					startingX = event.button.x;
					startingY = event.button.y;
					dragging = true;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (dragging) {
						std::cout << "dragging = false" << std::endl;
					}

					dragging = false;
				}
			}
			else if (event.type == SDL_MOUSEMOTION) {
				if (dragging) {
					offsetX += event.motion.x - startingX;
					offsetY += event.motion.y - startingY;

					startingX = event.motion.x;	
					startingY = event.motion.y;

					std::cout << "offsetX: " << offsetX << ", offsetY: " << offsetY << std::endl;
				}
			}
		}

		const Uint8* keystates = SDL_GetKeyboardState(NULL);
		if (keystates[SDL_SCANCODE_W]) {
			offsetY -= 0.2;
		}
		if (keystates[SDL_SCANCODE_S]) {
			offsetY += 0.2;
		}
		if (keystates[SDL_SCANCODE_A]) {
			offsetX -= 0.2;
		}
		if (keystates[SDL_SCANCODE_D]) {
			offsetX += 0.2;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//int zoomLevel = zoomFactor;
		//if (zoomLevel < 1) {
		//	zoomLevel = 1;
		//}
		int tileSide = 16 * zoomFactor;

		// Draw the image
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((i + j) % 2 == 0) { // Only draw on even sum indices to create a chess pattern
					SDL_Rect destRect = { i * tileSide + offsetX, j * tileSide + offsetY, tileSide, tileSide };
					SDL_RenderCopy(renderer, tileTexture, nullptr, &destRect);
				}
			}
		}

		// Display 
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyTexture(tileTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

    return 0;
}