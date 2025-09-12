#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "platform/window.h"
#include "platform/game_time.h"

#include "app/app.h"
#include "scene/scene_manager.h"
#include "gfx/render.h"

#define WINDOW_TITLE "Software Rasterizer"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void) {
	// ----- Top Level Structures -----
	Window          window            = NULL;
	GameTime        clock             = {0};	
	Renderer*       renderer          = NULL;
	SceneManager*   scene_manager     = NULL;
	App*            app               = NULL;

	// ----- Init Platform -----
	window = window_create(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
	clock = time_init(&clock);	

	// ----- Init mid-level services -----
	renderer = renderer_create(window);
	scene_manager = scene_manager_create();

	// ----- Init App -----
	app = app_create(renderer, scene_manager);
	
	// Initialize framebuffer and z-buffer
	uint32_t framebuffer[WIDTH * HEIGHT] = {0};
	float zbuffer[WIDTH * HEIGHT] = {0};

        bool running = true;
        SDL_Event event;

        while(running) {
		
		// Handle Time
		update_time(&time);
		/* print_fps(&time); */

		// Clear the buffers	
		memset(framebuffer, 0x0, sizeof(framebuffer));
		memset(zbuffer, 0x0, sizeof(zbuffer));

                // Event Handling
		int mouse_dx = 0;
		int mouse_dy = 0;

                while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT: running = false; break;
				case SDL_MOUSEMOTION:
					mouse_dx += event.motion.xrel;
					mouse_dy += event.motion.yrel;
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) running = false;
					break;
			}
                }	

		const Uint8* kb = SDL_GetKeyboardState(NULL);

		// ---- SCRIPTING SECTION -----

		struct Vec3f move_dir = {0};
		struct Vec3f move_vec = {0};

		if(kb[SDL_SCANCODE_W]) {
			move_dir = quat_get_forward(cam.transform.rotation);
			move_vec = vec3f_scale(move_dir, cam_speed * time.delta_time);
		}

		if(kb[SDL_SCANCODE_A]) {
			move_dir = vec3f_scale(quat_get_right(cam.transform.rotation), -1.0f);
			move_vec = vec3f_scale(move_dir, cam_speed * time.delta_time);
		}

		if(kb[SDL_SCANCODE_S]) {
			move_dir = vec3f_scale(quat_get_forward(cam.transform.rotation), -1.0f);
			move_vec = vec3f_scale(move_dir, cam_speed * time.delta_time);
		}

		if(kb[SDL_SCANCODE_D]) {
			move_dir = quat_get_right(cam.transform.rotation);
			move_vec = vec3f_scale(move_dir, cam_speed * time.delta_time);
		}
	
		// --- END OF SCRIPTING SECTION ---
		render_scene(framebuffer, zbuffer, scene);

		// Update SDL2 window w/ new framebuffer
                update_window(window_data, framebuffer);
        }

        /* Clean Up */

	free(mesh.vertices);
	free(mesh.triangles);
        destroy_window(window_data);
        return 0;
}
