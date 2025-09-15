#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdbool.h>
#include <stdint.h>

#pragma once
#include "vector.h"
#include "matrix.h"
#include "bounds.h"
#include "vertex.h"

typedef struct Triangle Triangle;

void print_tri(Triangle tri);
Triangle triangle_create(Vertex* A, Vertex* B, Vertex* C);

Bounds get_bounds_from_tri(Triangle tri);
Vec3f calculate_normal(Triangle tri);
Triangle apply_transformation(Mat4 tr, Triangle tri);
Triangle tri_perspective_divide(Triangle tri); 
Triangle apply_perspective_projection(bool* clipped, Mat4 m, Triangle tri);

#endif
