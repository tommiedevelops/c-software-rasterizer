#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "constants.h"

typedef struct Window {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
} Window;

Window initialise_window(char* title, int width, int height);
void destroy_window(Window data);
void update_window(Window data, uint32_t* framebuffer);

#endif
