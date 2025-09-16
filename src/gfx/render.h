#ifndef RENDER_H
#define RENDER_H

#pragma once
#include "scene_manager.h"
#include "window.h"
#include "triangle.h"
#include "vector.h"
#include "vertex.h"

typedef struct Renderer {
	Window* window;
	int width, height;
	uint32_t* framebuffer;
	uint32_t* zbuffer;
	uint32_t clear_color;
} Renderer;

Renderer* renderer_create(Window* window);

void renderer_setClearColor(Renderer* r, uint32_t clear_color);
void renderer_clear(Renderer* r);

void renderer_draw_scene(Renderer* r, Scene* scene);
void renderer_beginFrame(Renderer* r); // clear framebuffer 
void renderer_endFrame(Renderer* r); // write to SDL window

#endif
