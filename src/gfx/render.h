#ifndef RENDER_H
#define RENDER_H

#pragma once
#include "scene_manager.h"
#include "window.h"
#include "triangle.h"
#include "vector.h"
#include "vertex.h"

typedef struct Renderer Renderer;

// Life Cycle
Renderer* renderer_create(Window* window);
void renderer_destroy(Renderer* r);

// State
void renderer_set_clear_color(Renderer* r, uint32_t clear_color);
void renderer_clear_framebuffer(Renderer* r);
void renderer_clear_zbuffer(Renderer* r);

// Rendering
void renderer_draw_scene(Renderer* r, Scene* scene);
void renderer_begin_frame(Renderer* r); // clear framebuffer 
void renderer_end_frame(Renderer* r); // write to SDL window

#endif
