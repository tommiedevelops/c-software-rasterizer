#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "triangle.h"
#include "color.h"
#include "render.h"
#include "constants.h"

typedef struct Triangle {
	Vertex* A;
	Vertex* B;
	Vertex* C;
} Triangle;

Triangle triangle_create(Vertex* A, Vertex* B, Vertex* C){

	Triangle tri = {
		.A = A,
		.B = B,
		.C = C
	};

	return tri;
}

Vec3f triangle_calculate_normal(Triangle tri){
	Vec3f u = vec3f_add(tri.v0, vec3f_scale(tri.v1, -1));
	Vec3f v = vec3f_add(tri.v0, vec3f_scale(tri.v2, -1));
	Vec3f n = vec3f_normalize(vec3f_cross(u,v));
	return n;
}

void triangle_log(struct Triangle tri){
	printf("printing triangle:\n");
	print_vec3f(tri.v0);
	print_vec3f(tri.v1);
	print_vec3f(tri.v2);
	printf("end triangle\n");
}

Bounds triangle_get_bounds(Triangle tri){
        /* return: [xmin, xmax, ymin, ymax, zmin, zmax] */
        Bounds bounds = BOUNDS_DEFAULT;
	if (tri->A.pos.x > bounds.xmax) {bounds.xmax = tri->A.pos.x;}
	if (tri->A.pos.y > bounds.ymax) {bounds.ymax = tri->A.pos.y;}
	if (tri->A.pos.z > bounds.zmax) {bounds.zmax = tri->A.pos.z;}

	if (tri->B.pos.x > bounds.xmax) {bounds.xmax = tri->B.pos.x;}
	if (tri->B.pos.y > bounds.ymax) {bounds.ymax = tri->B.pos.y;}
	if (tri->B.pos.z > bounds.zmax) {bounds.zmax = tri->B.pos.z;}

	if (tri->C.pos.x > bounds.xmax) {bounds.xmax = tri->C.pos.x;}
	if (tri->C.pos.y > bounds.ymax) {bounds.ymax = tri->C.pos.y;}
	if (tri->C.pos.z > bounds.zmax) {bounds.zmax = tri->C.pos.z;}

	if (tri->A.pos.x < bounds.xmin) {bounds.xmin = tri->A.pos.x;}
	if (tri->A.pos.y < bounds.ymin) {bounds.ymin = tri->A.pos.y;}
	if (tri->A.pos.z < bounds.zmin) {bounds.zmin = tri->A.pos.z;}

	if (tri->B.pos.x < bounds.xmin) {bounds.xmin = tri->B.pos.x;}
	if (tri->B.pos.y < bounds.ymin) {bounds.ymin = tri->B.pos.y;}
	if (tri->B.pos.z < bounds.zmin) {bounds.zmin = tri->B.pos.z;}

	if (tri->C.pos.x < bounds.xmin) {bounds.xmin = tri->C.pos.x;}
	if (tri->C.pos.y < bounds.ymin) {bounds.ymin = tri->C.pos.y;}
	if (tri->C.pos.z < bounds.zmin) {bounds.zmin = tri->C.pos.z;}

        return bounds;
}

bool inside_triangle(float alpha, float beta, float gamma){
	return (alpha > 0) && (beta > 0) && (gamma > 0) && (alpha <= 1) && (beta <= 1) && (gamma <= 1);
}

float interpolate_depth(struct Triangle tri, float alpha, float beta, float gamma){
	// the basic idea is that each point x,y has a z value. i just need to calculate it
	float z0 = tri.v0.z;
	float z1 = tri.v1.z;
	float z2 = tri.v2.z;

	float depth = alpha*z0 + beta*z1 + gamma*z2;

	return depth;
}

bool point_inside(struct Vec4f point){	
	float w = point.w;
	return (point.x >= -w) && (point.x <= w) && 
	       (point.y >= -w) && (point.y <= w) &&
               (point.z >= 0) && (point.z <= w);	       
}

void rasterize_triangle(Vertex A, Vertex B, Vertex C, Material mat, Renderer r) {

	// Get width and height of the viewport
	int width = r.window->width;
	int height = r.window->height;
	
	
	// Calculate bounds of triangle ON THE VIEWPORT
	int xmin = (int)bounds.xmin;
	int xmax = (int)bounds.xmax;
	int ymin = (int)bounds.ymin;
	int ymax = (int)bounds.ymax;

	// Loop through each pixel within the bounds on the viewport
	for(int y = ymin; y <= ymax; y++){
		for(int x = xmin; x <= xmax; x++) {

			Vec3f bary_coords = calculate_bary_coords(A,B,C);
			
			// for pixels inside the triangle
			if( inside_triangle(alpha, beta, gamma) ) {
				// interpolate the depth, normals,
				float depth = interpolate_depth(tri, alpha, beta, gamma);	
				if(depth >= zbuffer[x + y*width]){
					// place pixel onto the framebuffer and update the zbuffer
					place_pixel(x,y,color,framebuffer);			
					zbuffer[x + y*width] = depth;
				}
			}	

		}

	}
}


