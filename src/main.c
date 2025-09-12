#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "platform/window.h"
#include "platform/game_time.h"

#include "app/app.h"
#include "scene/scene_manager.h"
#include "gfx/render.h"

#define WINDOW_TITLE "Software Rasterizer"
#define WINDOW_W 1280
#define WINDOW_H 720

int main(void) {
	// ----- Top Level Structures -----
	Window*         window       = NULL;
	GameTime        clock        = {0};	
	Renderer*       renderer     = NULL;
	SceneManager*   manager      = NULL;
	App*            app          = NULL;

	// ----- Init Platform -----
	window = window_create(WINDOW_TITLE, WINDOW_W, WINDOW_H);
	clock = time_init(&clock);	

	// ----- Init mid-level services -----
	renderer = renderer_create(window);
	manager = scene_manager_create();

	// ----- Init App -----
	app = app_create(renderer, scene);
	
	// Initialize framebuffer and z-buffer
	uint32_t framebuffer[WIDTH * HEIGHT] = {0};
	float zbuffer[WIDTH * HEIGHT] = {0};

        /* Prepare Window using SDL */
        struct SDL_Data window_data = initialise_window();

        /* Render Loop */
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

		// Hide the cursor
		const Uint8* kb = SDL_GetKeyboardState(NULL);

		// ---- SCRIPTING SECTION -----
		// Apply transformations to game object
		float angular_velocity = 0.2f; 
		float cam_speed = -1.0f;
		float yaw = time.delta_time * angular_velocity * mouse_dx;

		// input handling 	
		struct Quaternion cam_delta_lr = quat_normalize(quat_angle_axis(yaw, VEC3F_Y));
		cam.transform.rotation = quat_normalize(quat_mul(cam.transform.rotation, cam_delta_lr));

		float angle = time.delta_time * angular_velocity * mouse_dx;

		// input handling 	
		struct Quaternion cam_delta = quat_normalize(quat_angle_axis(angle, VEC3F_Y));
		cam.transform.rotation = quat_normalize(quat_mul(cam.transform.rotation, cam_delta));

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

		cam.transform.position = vec3f_add(cam.transform.position, move_vec);

		float go_angle = angular_velocity * time.delta_time;

		struct Vec3f rot_axis = {.x = 1.0f, .y = 1.0f, .z = 1.0f};
		struct Vec3f rot_axis1 = {.x = -1.0f, .y = 1.0f, .z = 1.0f};
		struct Vec3f rot_axis2 = {.x = 1.0f, .y = 1.0f, .z = -1.0f};

		struct Quaternion rot = quat_normalize(quat_angle_axis(go_angle, rot_axis));
		struct Quaternion rot1 = quat_normalize(quat_angle_axis(2*go_angle, rot_axis1));
		struct Quaternion rot2 = quat_normalize(quat_angle_axis(3*go_angle, rot_axis2));

		go.transform.rotation = quat_normalize(quat_mul(go.transform.rotation, rot));
		go1.transform.rotation = quat_normalize(quat_mul(go1.transform.rotation, rot1));
		go2.transform.rotation = quat_normalize(quat_mul(go2.transform.rotation, rot2));

	
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
