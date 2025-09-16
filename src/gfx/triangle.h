#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdbool.h>
#include <stdint.h>

#include "vertex.h"
#include "matrix.h"
#include "bounds.h"

typedef struct Triangle {
	Vertex* A;
	Vertex* B;
	Vertex* C;
} Triangle;

Triangle triangle_create(Vertex* A, Vertex* B, Vertex* C);
Bounds triangle_get_bounds(Triangle tri);

#endif
