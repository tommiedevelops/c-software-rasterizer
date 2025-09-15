#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>

#include "scene_manager.h"
#include "render.h"
#include "input_handler.h"

typedef struct App { 
	Renderer* r;
	SceneManager* s;
	InputHandler* input;
} App;

App* app_create(Renderer* r, SceneManager* s, InputHandler* input); // Renderer, SceneManager
void app_start(App* app); // Prepares the scene
void app_update(App* app, double dt); // Updates any time dependencies
void app_render(App* app); // Render the current frame
void app_shutdown(App* app); // Close window and clean up resources
void app_destroy(App* app); // Clean up app itself

#endif
