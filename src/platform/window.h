#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Window Window;
Window window_create(char* title, int width, int height);

void destroy_window(Window window);
void update_window(Window window, uint32_t* framebuffer);

#endif
