#ifndef BOUNDS_H
#define BOUNDS_H

#include <float.h>
#include <stdbool.h>

#include "vector.h"

typedef struct Bounds {
	float xmin, xmax;
	float ymin, ymax;
	float zmin, zmax;
} Bounds;

#define BOUNDS_DEFAULT (Bounds) { 	\
	.xmin = FLT_MAX, .xmax = -FLT_MAX, 	\
	.ymin = FLT_MAX, .ymax = -FLT_MAX, 	\
	.zmin = FLT_MAX, .zmax = -FLT_MAX 	\
	}

void print_bounds(Bounds bounds);
bool bounds_are_equal(Bounds a, Bounds b);
Bounds get_bounds(Vec3f* vertices, int num_vertices);
void update_bounds(Bounds* bounds, Vec3f* vertices, int num_vertices);

#endif
