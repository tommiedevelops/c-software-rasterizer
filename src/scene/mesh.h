#ifndef MESH_H
#define MESH_H

#include "vector.h"
typedef struct Mesh {
	Vec3f* vertices;
	int num_vertices;
	int* triangles;
	int num_triangles;
} Mesh;

Mesh create_mesh_from_obj();
Mesh create_plane_mesh();

#endif
