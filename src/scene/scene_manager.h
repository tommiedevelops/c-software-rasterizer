#ifndef SCENE_MANAGER_H 
#define SCENE_MANAGER_H

#include "quaternion.h"
#include "vector.h"
#include "mesh.h"
#include "matrix.h"
#include "texture.h"

#include "camera.h"
#include "light.h"
#include "transform.h"
#include "game_object.h"

#define LOG_ERROR(msg) \
    fprintf(stderr, "[ERROR] %s:%d %s(): %s\n", __FILE__, __LINE__, __func__, msg)
typedef struct SceneNode SceneNode;
typedef struct SceneManager SceneManager;
typedef struct Scene Scene;

void transform_set(Transform* tr, Vec3f pos, Quaternion rot, Vec3f scale);
Transform transform_default();
SceneNode* scene_node_create(SceneNode* parent);
SceneManager* scene_manager_create();
int scene_manager_create_new_scene(SceneManager* manager);
void scene_manager_delete_scene(SceneManager* manager, int scene_index);

// Matrices 
Mat3 get_screen_space_matrix();

Mat4 get_scale_matrix(Transform tr); 

Mat4 get_translation_matrix(Transform tr); 

Mat4 get_rotation_matrix(Transform tr);

Mat4 get_model_matrix(Transform tr);

Mat4 get_view_matrix(Camera cam);

Mat4 get_projection_matrix(Camera cam);

void normalize_vertices(float sidelength, Vec3f* vertices, int num_vertices);

Vec4f perspective_divide(Vec4f v);

Mat4 get_viewport_matrix(Camera cam);

#endif
