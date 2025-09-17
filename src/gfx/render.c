#include "render.h"

#include <stdio.h> 
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define LOG_ERROR(msg) \
    fprintf(stderr, "[ERROR] %s:%d %s(): %s\n", __FILE__, __LINE__, __func__, msg)

struct Renderer {
	Window*    window;
	int        width, height;
	uint32_t*  framebuffer;
	uint32_t*  zbuffer;
	uint32_t   clear_color;
};

// Life Cycle
Renderer* renderer_create(Window* win) {

	if(win == NULL) {
		LOG_ERROR("window is NULL");
		return NULL;
	}

	Renderer* r = calloc(1, sizeof(*r));
	
	if(!r) {
		LOG_ERROR("allocation failed");
		return NULL;
	}

	r->window = win;
	r->width  = win->width;
	r->height = win->height;

	int num_pixels = r->width * r->height;

	r->framebuffer = malloc(sizeof(uint32_t) * num_pixels);
	r->zbuffer     = malloc(sizeof(uint32_t) * num_pixels);

	if(!r->framebuffer || !r->zbuffer) {
		LOG_ERROR("framebuffer or zbuffer allocation failed");
		free(r->framebuffer);
		free(r->zbuffer);
		free(r);
		return NULL;
	}

	r->clear_color = 0x000000FF; // RGBA black
	
	return r;
}

void renderer_destroy(Renderer* r) {

	if(NULL == r) {
	       	LOG_ERROR("NULL ptr");
		return;
	}

	free(r->framebuffer);
	free(r->zbuffer);
	free(r);
}

void renderer_begin_frame(Renderer* r) {
	//TODO
}
void renderer_end_frame(Renderer* r) {
	//TODO 	
}
void renderer_set_clear_color(Renderer* r, uint32_t clear_color);
void renderer_clear(Renderer* r);

bool inside_frustum(Vertex* v){
	if(v->pos.x < -v->pos.w || v->pos.x > v->pos.w) return false;
	if(v->pos.y < -v->pos.w || v->pos.y > v->pos.w) return false;
	if(v->pos.z < 0 || v->pos.z > v->pos.w) return false;
	return true;
}

int clip_triangle_clipspace(Vertex* A, Vertex* B, Vertex* C, Triangle* tmp){
	// TODO
}

void rasterize_triangle(Triangle* tri, Renderer* r, Material* mat) {
	// TODO
}


void renderer_draw_scene(Renderer* r, Scene* scene) {
	Camera* cam; //fix
	Mat4 PV = mat4_mul_mat4(get_projection_matrix(*cam), get_view_matrix(*cam));
	int num_gameObjects = 0; //fix
	for(int i = 0; i < num_gameObjects; i++) {
		
		//GameObject* go = scene->gameObjects[i];
		GameObject* go;
		Mesh* mesh = go->mesh;
		Material* mat = go->material;

		int* triangles = mesh->triangles;
		Vec3f* vertices = mesh->vertices;
		int num_triangles = mesh->num_triangles;
		int num_vertices = mesh->num_vertices;

		Mat4 MVP = mat4_mul_mat4( PV, get_model_matrix(go->transform) );	

		for(int t = 0; t < num_triangles; t++) {
			
			// Assemble Primitives
			Vertex A = vertex_create(vertices[triangles[3*t]], NULL, NULL);
			Vertex B = vertex_create(vertices[triangles[3*t+1]], NULL, NULL);
			Vertex C = vertex_create(vertices[triangles[3*t+2]], NULL, NULL);

			// Apply MVP
			A.pos = mat4_mul_vec4(MVP, A.pos);
			B.pos = mat4_mul_vec4(MVP, B.pos);
			C.pos = mat4_mul_vec4(MVP, C.pos);
			
			// Clipping
			Triangle tmp[2];
			int n = clip_triangle_clipspace(&A,&B,&C,tmp);
			if(!n) continue;		
			
			for(int k = 0; k < n; k++){
				// prep persp.Ctive.Corr.Ct-.A.A
				/* prep_perspective_divide_terms(tmp[k].A); */
				/* prep_perspective_divide_terms(tmp[k].B); */
				/* prep_perspective_divide_terms(tmp[k].C); */

				// divide + viewport
				/* ndc_to_screen(&tmp[k].A, r->width, r->height); */
				/* ndc_to_screen(&tmp[k].B, r->width, r->height); */
				/* ndc_to_screen(&tmp[k].C, r->width, r->height); */
				
				// rasterize
				rasterize_triangle(&tmp[k], r, mat);
			}
			
						
		}
	}
}

