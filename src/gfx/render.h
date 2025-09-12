#ifndef RENDER_H
#define RENDER_H

#include "triangle.h"
#include "scene_manager.h" // get rid of this dependency

typedef struct Renderer Renderer;

void place_pixel(int x, int y, uint32_t value, uint32_t* framebuffer); 
void render_scene(uint32_t* framebuffer, float* zbuffer, struct Scene scene);

#endif
