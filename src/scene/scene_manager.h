#ifndef SCENE_MANAGER_H 
#define SCENE_MANAGER_H

#include "vec3f.h"
#include "bounds.h"
#include "quaternion.h"

#include "mesh.h"
#include "obj_parser.h"

// --- STRUCT DEFINITIONS --- 

typedef struct SceneManager SceneManager;

typedef struct Transform {
	struct Vec3f position;  // in world coords
	struct Quaternion rotation;  
	struct Vec3f scale;
} Transform;

typedef struct Camera { 
	struct Transform transform;
	float fov;
	float near;
	float far;
} Camera;


typedef struct Material {
	struct Vec3f color; // fallback color if no texture
	struct Texture *albedo; // for base color
} Material;

typedef struct GameObject {
	struct Transform transform;
	struct Mesh* mesh;
	struct Material* material;
} GameObject;

typedef struct Light {
	struct Vec3f direction;
} Light;

typedef struct Scene {
	struct Camera *cam;
	struct GameObject **gameObjects;
	int num_gameObjects;
	struct LightSource light;
} Scene;

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
void camera_set_far(Camera* cam float, far);

// GameObject
GameObject game_object_create(Transform transform, Mesh* mesh, Material* mat);
void game_object_set_transform(GameObject* go, Transform transform);
void game_object_set_mesh(GameObject* go, Mesh* mesh);
void game_object_set_material(GameObject* go, Material* mat);

// Material
Material create_material()

// Matrices 
struct Mat3 get_screen_space_matrix();

struct Mat4 get_scale_matrix(struct Transform tr); 

struct Mat4 get_translation_matrix(struct Transform tr); 

struct Mat4 get_rotation_matrix(struct Transform tr);

struct Mat4 get_model_matrix(struct Transform tr);

struct Mat4 get_view_matrix(struct Camera cam);

struct Mat4 get_projection_matrix(struct Camera cam);

void normalize_vertices(float sidelength, struct Vec3f* vertices, int num_vertices);

struct Vec4f perspective_divide(struct Vec4f v);

struct Mat4 get_viewport_matrix(struct Camera cam);

#endif
