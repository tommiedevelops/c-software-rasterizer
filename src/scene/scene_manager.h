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

enum SceneNodeType {
	CAMERA,
	LIGHT,
	GAMEOBJECT
};

typedef struct SceneNode SceneNode;
struct SceneNode {

	enum SceneNodeType type;

	// SceneGraph Relations
	SceneNode* parent;
	SceneNode* children;
	int num_children;

	// Reference to next SceneNode
	SceneNode* next_root;
	int root_id;

	// Components
	Transform tr;
	Mesh* mesh;
	Material* material;

};

typedef struct SceneGraph {
	// Camera & Properties
       	SceneNode* cam; 
	float fov, near, far;
	bool is_orthographic;

	SceneNode* root; // Start of SLL
} SceneGraph;

typedef struct SceneManager  {
	// Simple array. Number of scenes should be known at compile time.
	SceneGraph* scenes;
	int num_scenes;
} SceneManager;

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
