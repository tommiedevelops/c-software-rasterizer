#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Window {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
	int width;
	int height;
	char * title;
} Window;

Window window_create(char* title, int width, int height);

void destroy_window(Window window);
void update_window(Window window, uint32_t* framebuffer);

#endif
