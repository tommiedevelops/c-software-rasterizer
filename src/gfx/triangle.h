#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdbool.h>
#include <stdint.h>

#pragma once
#include "vec3f.h"
#include "matrix.h"
#include "bounds.h"

struct Vec3f;

struct Triangle {
	// no order is assumed here
	struct Vec3f v0;
	struct Vec3f v1;
	struct Vec3f v2;
};
void print_tri(struct Triangle tri);

struct Triangle create_triangle(
	struct Vec3f a,
	struct Vec3f b,
	struct Vec3f c
);

struct Bounds get_bounds_from_tri(struct Triangle tri);
struct Vec3f calculate_normal(struct Triangle tri);
struct Triangle apply_transformation(struct Mat4 tr, struct Triangle tri);
struct Triangle tri_perspective_divide(struct Triangle tri); 
struct Triangle apply_perspective_projection(bool* clipped, struct Mat4 m, struct Triangle tri);

#endif
