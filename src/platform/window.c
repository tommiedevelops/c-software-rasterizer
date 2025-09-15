
#include "window.h"

Window window_create(char* title, int width, int height){

	// Initialise SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create window
	SDL_Window* window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 0
	);
	
	// Disable Cursor (if possible)
	SDL_ShowCursor(SDL_DISABLE);

	// Create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Create texture
	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		width, height 
	);
	
	// TODO
	// make Window struct return
	Window win = {0};
	return win;	
}

void update_window(Window win, uint32_t* framebuffer) {

	// Update texture with framebuffer pixels
	SDL_UpdateTexture(win.texture, NULL, framebuffer, win.width * sizeof(uint32_t));

	// Draw
	SDL_RenderClear(win.renderer);
	SDL_RenderCopy(win.renderer, win.texture, NULL, NULL);
	SDL_RenderPresent(win.renderer);
}
