#include "vertex.h"

#include <stdio.h>

#include "triangle.h"
#include "vector.h"


Vec3f vertex_calculate_bary_coords(float x, float y, Vertex* A, Vertex* B, Vertex* C) {

	Vec3f result;

	Vec4f a = A->pos;
	Vec4f b = B->pos;
	Vec4f c = C->pos;

	result.x = (a.x*(c.y-a.y)+(y-a.y)*(c.x-a.x)-x*(c.y-a.y))
			/((b.y-a.y)*(c.x-a.x)-(b.x-a.x)*(c.y-a.y));

	result.y = ((y-a.y) - result.x*(b.y-a.y))/(c.y-a.y);
	result.z = 1 - result.x - result.y;

	return result;
}

Vertex vertex_create(Vec3f pos, Vec2f* uv, Vec3f* normal){
	
	Vertex v = {0};
	v.pos.x = pos.x;
	v.pos.y = pos.y;
	v.pos.z = pos.z;
	v.pos.w = 1.0f;

	if(uv != NULL) v.uv = *uv;
	if(normal != NULL) v.normal = *normal;
	return v;
}


void vertex_prep_perspective_correct_terms(Vertex* vertex) {
	//TODO
	return;
}

