#ifndef VERTEX_H
#define VERTEX_H

#include "vector.h"

typedef struct Vertex {
	Vec4f pos;
	Vec2f uv;
	Vec3f normal;

	Vec3f bary_coord;

	// perspective correction terms
	float inv_w;
	Vec2f uv_over_w;
	Vec3f normal_over_w;
} Vertex;

Vertex vertex_create(Vec3f pos,Vec2f* uv, Vec3f* normal);
void prep_perspective_divide_terms(Vertex* v);
Vec3f vertex_calculate_bary_coords(float x, float y, Vertex* A, Vertex* B, Vertex* C);
#endif
