#include "triangle.h"

#include <stdio.h>
#include <stdlib.h>

Triangle triangle_create(Vertex* A, Vertex* B, Vertex* C){

	Triangle tri = {
		.A = A,
		.B = B,
		.C = C
	};

	return tri;
}

Vec3f triangle_calculate_normal(Triangle tri){
	//TODO	
}

void triangle_log(struct Triangle tri){
	// TODO
}

Bounds triangle_get_bounds(Triangle tri){
        /* return: [xmin, xmax, ymin, ymax, zmin, zmax] */
        Bounds bounds = BOUNDS_DEFAULT;
	if (tri.A->pos.x > bounds.xmax) {bounds.xmax = tri.A->pos.x;}
	if (tri.A->pos.y > bounds.ymax) {bounds.ymax = tri.A->pos.y;}
	if (tri.A->pos.z > bounds.zmax) {bounds.zmax = tri.A->pos.z;}

	if (tri.B->pos.x > bounds.xmax) {bounds.xmax = tri.B->pos.x;}
	if (tri.B->pos.y > bounds.ymax) {bounds.ymax = tri.B->pos.y;}
	if (tri.B->pos.z > bounds.zmax) {bounds.zmax = tri.B->pos.z;}

	if (tri.C->pos.x > bounds.xmax) {bounds.xmax = tri.C->pos.x;}
	if (tri.C->pos.y > bounds.ymax) {bounds.ymax = tri.C->pos.y;}
	if (tri.C->pos.z > bounds.zmax) {bounds.zmax = tri.C->pos.z;}

	if (tri.A->pos.x < bounds.xmin) {bounds.xmin = tri.A->pos.x;}
	if (tri.A->pos.y < bounds.ymin) {bounds.ymin = tri.A->pos.y;}
	if (tri.A->pos.z < bounds.zmin) {bounds.zmin = tri.A->pos.z;}

	if (tri.B->pos.x < bounds.xmin) {bounds.xmin = tri.B->pos.x;}
	if (tri.B->pos.y < bounds.ymin) {bounds.ymin = tri.B->pos.y;}
	if (tri.B->pos.z < bounds.zmin) {bounds.zmin = tri.B->pos.z;}

	if (tri.C->pos.x < bounds.xmin) {bounds.xmin = tri.C->pos.x;}
	if (tri.C->pos.y < bounds.ymin) {bounds.ymin = tri.C->pos.y;}
	if (tri.C->pos.z < bounds.zmin) {bounds.zmin = tri.C->pos.z;}

        return bounds;
}

bool inside_triangle(float alpha, float beta, float gamma){
	return (alpha > 0) && (beta > 0) && (gamma > 0) && (alpha <= 1) && (beta <= 1) && (gamma <= 1);
}

/* float interpolate_depth(struct Triangle tri, float alpha, float beta, float gamma){ */
/* 	// the basic idea is that each point x,y has a z value. i just need to calculate it */
/* 	float z0 = tri.A.z; */
/* 	float z1 = tri.B.z; */
/* 	float z2 = tri.C.z; */

/* 	float depth = alpha*z0 + beta*z1 + gamma*z2; */

/* 	return depth; */
/* } */

bool point_inside(struct Vec4f point){	
	float w = point.w;
	return (point.x >= -w) && (point.x <= w) && 
	       (point.y >= -w) && (point.y <= w) &&
               (point.z >= 0) && (point.z <= w);	       
}

/* void rasterize_triangle(Triangle tri, Renderer* r, Material* mat) { */

/* 	// Get width and height of the viewport */
/* 	int width = r->width; */
/* 	int height = r->height; */
	
	
/* 	// Calculate bounds of triangle ON THE VIEWPORT */
/* 	int xmin = (int)bounds.xmin; */
/* 	int xmax = (int)bounds.xmax; */
/* 	int ymin = (int)bounds.ymin; */
/* 	int ymax = (int)bounds.ymax; */

/* 	// Loop through each pixel within the bounds on the viewport */
/* 	for(int y = ymin; y <= ymax; y++){ */
/* 		for(int x = xmin; x <= xmax; x++) { */

/* 			Vec3f bary_coords = vertex_calculate_bary_coords(x,y,tri); */
	
/* 			// for pixels inside the triangle */
/* 			if( inside_triangle(alpha, beta, gamma) ) { */
/* 				// interpolate the depth, normals, */
/* 				float depth = interpolate_depth(tri, alpha, beta, gamma); */	
/* 				if(depth >= zbuffer[x + y*width]){ */
/* 					// place pixel onto the framebuffer and update the zbuffer */
/* 					place_pixel(x,y,color,framebuffer); */			
/* 					zbuffer[x + y*width] = depth; */
/* 				} */
/* 			} */	

/* 		} */

/* 	} */
/* } */


