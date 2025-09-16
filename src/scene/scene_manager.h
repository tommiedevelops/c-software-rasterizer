#ifndef SCENE_MANAGER_H 
#define SCENE_MANAGER_H

#include "quaternion.h"
#include "vector.h"
#include "mesh.h"
#include "matrix.h"
#include "texture.h"

// --- STRUCT DEFINITIONS --- 
typedef struct Transform {
	Vec3f position;  // in world coords
	Quaternion rotation;  
	Vec3f scale;
} Transform;

typedef struct Camera { 
	Transform transform;
	int width, height;
	float fov;
	float near;
	float far;
} Camera;

typedef struct Material {
	Vec3f color; // fallback color if no texture
	Texture *albedo; // for base color
} Material;

typedef struct GameObject {
	 Transform transform;
	 Mesh* mesh;
	 Material* material;
} GameObject;

typedef struct Light {
	Vec3f direction;
} Light;

typedef struct Scene {
	Camera *cam;
	GameObject **gameObjects;
	int num_gameObjects;
	Light light;
} Scene;

typedef struct SceneManager  {
	Scene scene;
} SceneManager;

SceneManager* scene_manager_create();

// Transform 
Transform create_transform(Vec3f rotation, Vec3f position, Vec3f scale);
void transform_set_rotation(Transform* tr, Vec3f new_rotation);
void transform_set_position(Transform* tr, Vec3f new_position);
void transform_set_scale(Transform* tr, Vec3f new_scale);

// Camera
Camera camera_create(Transform tr, float fov, float near, float far);
void camera_set_transform(Camera* cam, Transform tr); 
void camera_set_fov(Camera* cam, float fov);
void camera_set_near(Camera* cam, float near);
void camera_set_far(Camera* cam, float far);

// GameObject
GameObject game_object_create(Transform transform, Mesh* mesh, Material* mat);
void game_object_set_transform(GameObject* go, Transform transform);
void game_object_set_mesh(GameObject* go, Mesh* mesh);
void game_object_set_material(GameObject* go, Material* mat);

// Material
Material create_material();

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
