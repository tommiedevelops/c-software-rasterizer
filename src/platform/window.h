#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct Window {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
	int width;
	int height;
	char * title;
} Window;

Window window_create(char* title, int width, int height);
void destroy_window(Window data);
void update_window(Window data, uint32_t* framebuffer);

#endif
