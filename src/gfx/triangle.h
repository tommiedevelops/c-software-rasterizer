#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdbool.h>
#include <stdint.h>

#pragma once
#include "vec3f.h"
#include "matrix.h"
#include "bounds.h"

typedef struct Triangle Triangle;

void print_tri(struct Triangle tri);
Triangle triangle_create(Vertex* A, Vertex* B, Vertex* C);

struct Bounds get_bounds_from_tri(struct Triangle tri);
struct Vec3f calculate_normal(struct Triangle tri);
struct Triangle apply_transformation(struct Mat4 tr, struct Triangle tri);
struct Triangle tri_perspective_divide(struct Triangle tri); 
struct Triangle apply_perspective_projection(bool* clipped, struct Mat4 m, struct Triangle tri);

#endif
