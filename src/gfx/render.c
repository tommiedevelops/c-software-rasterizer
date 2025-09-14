#include <stdio.h> 
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vec3f.h"
#include "scene_manager.h"

typedef struct Renderer Renderer {
	Window* window;
	uint32_t* framebuffer;
	uint32_t* zbuffer;
	uint32_t clear_color;
};

renderer_beginFrame(Renderer* r);
rednerer_endFrame(Renderer* r);


int clip_triangle_clipspace(Vertex* A, Vertex* B, Vertex* C, Triangle* tmp){
	//TODO
	return 1;
}

void renderer_draw_scene(Renderer* r, Scene scene) {
	const Camera* cam = scene->cam;
	Mat4 PV = mat4_mul_mat4(get_P(cam), get_V(cam));

	for(int i = 0; i < scene.num_gameObjects; i++) {
		
		const GameObject* go = scene->gameObjects[i];
		const Mesh* mesh = &go->mesh;
		const Material* mat = &go->material;

		Mat4 MVP = mat4_mul_mat4( PV, get_M(go) );	

		for(int t = 0; t < go.mesh.num_triangles; t++) {
			
			// Assemble Primitives
			Vertex A = create_vertex(vertices[triangles[3*t]], NULL, NULL);
			Vertex B = create_vertex(vertices[triangles[3*t+1]], NULL, NULL);
			Vertex C = create_vertex(vertices[triangles[3*t+2]], NULL, NULL);

			// Apply MVP
			A.pos = mat4_mul_vec4(MVP, A.pos);
			B.pos = mat4_mul_vec4(MVP, B.pos);
			C.pos = mat4_mul_vec4(MVP, C.pos);
			
			// Clipping
			Triangle tmp[2];
			int n = clip_triangle_clipspace(&A,&B,&C,tmp);
			if(!n) continue;		
			
			for(int k = 0; k < n; k++){
				// prep perspective-correct-data
				prep_perspective_divide_terms(&tmp[k].a);
				prep_perspective_divide_terms(&tmp[k].b);
				prep_perspective_divide_terms(&tmp[k].c);

				// divide + viewport
				ndc_to_screen(&tmp[k].a, r->width, r->height);
				ndc_to_screen(&tmp[k].b, r->width, r->height);
				ndc_to_screen(&tmp[k].c, r->width, r->height);

			}

			rasterize_triangle(r, &tmp[k], mat);
			
						
		}
	}
}

