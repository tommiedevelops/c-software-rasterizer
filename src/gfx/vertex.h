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

#endif
