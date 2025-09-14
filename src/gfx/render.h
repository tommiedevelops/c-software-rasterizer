#ifndef RENDER_H
#define RENDER_H

#include "scene_manager.h"

typedef struct Renderer Renderer;
void renderer_draw_scene(Renderer* r, Scene* scene);

#endif
