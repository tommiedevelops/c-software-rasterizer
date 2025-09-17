#include "scene_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "matrix.h"
#include "bounds.h"

#define LOG_ERROR(msg) \
    fprintf(stderr, "[ERROR] %s:%d %s(): %s\n", __FILE__, __LINE__, __func__, msg)

#define SCENE_MANAGER_NOT_SET (-1)

typedef struct SceneRoot;

struct SceneRoot {
	SceneNode* root;	
	SceneRoot* next;
};

struct SceneNode {
	enum SceneNodeType type;

	// SceneGraph Relations
	SceneNode* parent;
	SceneNode* children;
	int num_children;

	// Components
	Transform transform;
	Mesh* mesh;
	Material* material;
};

typedef struct Scene {
	// Camera & Properties
       	SceneNode* cam; 
	float fov, near, far;
	bool orthographic;

	SceneRoot* root; // Start of SLL & root of tree
	int scene_index;
} Scene;

typedef struct SceneManager  {
	// Simple array. Number of scenes should be known at compile time.
	Scene* scenes;
	int num_scenes;
} SceneManager;

void transform_set(Transform* tr, Vec3f pos, Quaternion rot, Vec3f scale){
	if(tr == NULL) {
		LOG_ERROR("transform is NULL");
		return;
	}

	tr.posisition = pos;
	tr.rotation = rot;
	tr.scale = scale;
}

Scene* scene_manager_create_scene() {
	Scene* scene = malloc(sizeof(Scene));	
	if(!scene) LOG_ERROR("scene->malloc failed");

	scene->cam = NULL;
	scene->fov = SCENE_MANAGER_NOT_SET;
	scene->far = SCENE_MANAGER_NOT_SET;
	scene->near = SCENE_MANAGER_NOT_SET;

	scene->orthographic = false;
	scene->scene_index = SCENE_MANAGER_NOT_SET;

	return scene;
}

SceneNode* scene_node_create(SceneNode* parent, SceneNodeType type) {
	// TODO	
	return NULL;
}


Transform transform_default(){
	Transform tr;
	tr.scale = VEC3F_1;
	tr.rotation = QUAT_IDENTITY;
	tr.position = VEC3F_0;
	return tr;
}

SceneNode* scene_manager_create_camera(float fov, float near, float far) {
	SceneNode* cam_node = scene_node_create(NULL, transform_default());
		
}



















// Life Cycle
SceneManager* scene_manager_create() {
	// TODO
	return NULL;
}

void scene_manager_destroy(SceneManager* scene){
	if(!scene){
		LOG_ERROR("provided scene is NULL");
		return;
	}
}

Mat4 get_rotation_matrix(Transform tr) {
	return quat_to_mat4(quat_normalize(tr.rotation));
}

Mat4 get_scale_matrix(Transform tr) {
	Vec3f scale = tr.scale;
	Mat4 scale_matrix = {{
		{scale.x, 0,       0,       0},
		{0,       scale.y, 0,       0},
		{0,       0,       scale.z, 0},
		{0,       0,       0,       1.0f},
	}};
	return scale_matrix;
}

Mat4 get_translation_matrix(Transform tr) {
	Vec3f pos = tr.position;
    	Mat4 translation_matrix = {{
       		{1.0f, 0, 0, pos.x},
        	{0, 1.0f, 0, pos.y},
        	{0, 0, 1.0f, pos.z},
        	{0, 0, 0, 1.0f    },
    	}};
    	return translation_matrix;	
}


Mat4 get_model_matrix(Transform tr){
	Mat4 result;
	result = get_scale_matrix(tr);
	result = mat4_mul_mat4(get_rotation_matrix(tr), result);
	result = mat4_mul_mat4(get_translation_matrix(tr), result);
	return result;
}

Mat4 get_view_matrix(Camera cam){
	// i guess you'd just apply the inverse model matrix of the camera
	return mat4_affine_orthonormal_inverse(get_model_matrix(cam.transform));
}

Mat4 get_projection_matrix(Camera cam) {

	float fov = cam.fov;
	float aspect = (float) cam.height / cam.width;
	float zn = cam.near;
	float zf = cam.far;

	Mat4 P = {0};
	P.m[0][0] = aspect/tan(0.5f*fov);
	P.m[1][1] = 1/tan(0.5f*fov);
	P.m[2][2] = (float)1.0f/ (zf - zn);
	P.m[2][3] = (float)(-zn)/(zf-zn); 
	P.m[3][2] = 1.0f;
	return P;
}

Vec4f perspective_divide(Vec4f v){
	Vec4f result = {0};
	
	if(v.w != 0){
		result.x = v.x/v.w;
		result.y = v.y/v.w;
		result.z = v.z/v.w;		
		result.w = 1.0f;
	}
	
	return result;
}

Mat4 get_viewport_matrix(Camera cam){

	float near = cam.near;
	float far = cam.far;
	float width = cam.width;
	float height = cam.height;

	Mat4 P = {0};
	P.m[0][0] = width/2;
	P.m[1][1] = height/2;
	P.m[0][3] = width/2;
	P.m[1][3] = height/2;
	P.m[2][2] = (far - near);
	P.m[2][3] = near;
	P.m[3][3] = 1.0f;
	return P;
}


/* vector array methods */

/* Shifts coordinates on all three axes to [0, imax - imin] */
static void shift_to_origin(Bounds bounds, Vec3f* vectors, int num_vectors) {
        for(int i = 0; i < num_vectors; i++){
                vectors[i].x -= bounds.xmin;
                vectors[i].y -= bounds.ymin;
                vectors[i].z -= bounds.zmin;
        }
}

/* Normalizes values to between [-1,1] - assumes min = 0 for all axes */
static void normalize_lengths(Bounds bounds, Vec3f* vectors, int num_vectors) {

        // normalizes between [0,1]
	float max = fmax(fmax(bounds.xmax, bounds.ymax), bounds.zmax);
        for(int i = 0; i < num_vectors; i++){
                vectors[i].x = (float)vectors[i].x / max;
                vectors[i].y = (float)vectors[i].y / max;
                vectors[i].z = (float)vectors[i].z / max;
        }

        // scale and translate to [-1,1]
        for(int i = 0; i < num_vectors; i++){
                scale_vector(vectors + i, 2);
                translate_vector(vectors + i, -1.0f,-1.0f,-1.0f);
        }
}

/* Takes normalized vectors between [-1,1] and scales them to [-target_length/2, target_length/2] */
static void scale_lengths(float target_length, Bounds bounds, Vec3f* vectors, int num_vectors){
        for(int i = 0; i < num_vectors; i++){
                scale_vector(vectors + i, (float)target_length/2.0f);
        }
}

/*
   normalize vectors to fit in box, side length s that is centered
   on the origin all axes scaled equally.
*/
void normalize_vertices(
			float sidelength,
			Vec3f* vertices,
			int num_vertices
){
        Bounds bounds = get_bounds(vertices, num_vertices);

        shift_to_origin(bounds, vertices, num_vertices);
	bounds = get_bounds(vertices, num_vertices);

        normalize_lengths(bounds, vertices, num_vertices);
	bounds = get_bounds(vertices, num_vertices);

        scale_lengths(sidelength, bounds, vertices, num_vertices);
}
