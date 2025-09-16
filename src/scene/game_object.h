#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "transform.h"
#include "mesh.h"
#include "material.h"

typedef struct GameObject {
	 Transform transform;
	 Mesh* mesh;
	 Material* material;
} GameObject;


// GameObject
GameObject game_object_create(Transform transform, Mesh* mesh, Material* mat);
void game_object_set_transform(GameObject* go, Transform transform);
void game_object_set_mesh(GameObject* go, Mesh* mesh);
void game_object_set_material(GameObject* go, Material* mat);


#endif
