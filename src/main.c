#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "window.h"
#include "game_time.h"
#include "input_handler.h"

#include "app.h"
#include "scene_manager.h"
#include "render.h"

#define WINDOW_TITLE "Software Rasterizer"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void) {
	// ----- Top Level Structures -----
	Window          window            =  {0};
	GameTime        clock             =  {0};	
	SDL_Event       event             =  {0};
	Renderer*       renderer          = NULL;
	SceneManager*   scene_manager     = NULL;
	App*            app               = NULL;
	InputHandler*   input_handler     = NULL;

	// ----- Init Platform -----
	window = window_create(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
	gameTime_init(&clock);	

	// ----- Init mid-level services -----
	renderer      = renderer_create(&window);
	scene_manager = scene_manager_create();
	input_handler = inputHandler_create();
	app           = app_create(renderer, scene_manager, input_handler);

	// ----- Start App -----
	app_start(app);	

	// ----- Main Loop -----
        bool running = true;
        while(running) {
		gameTime_update(&clock);
		input_beginFrame(input_handler);
		
		while(SDL_PollEvent(&event)){
			running = input_processEvent(&event);
		}
		
		app_update(app, gameTime_deltaTime(&time));
		input_endFrame(input_handler);

		renderer_beginFrame(renderer);
		app_render(app);
		renderer_endFrame(renderer);
        }

	// ----- Clean Up -----
        return 0;
}
