#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

// Vec3f
#define VEC3F_X ((Vec3f){1.0f, 0.0f, 0.0f})
#define VEC3F_Y ((Vec3f){0.0f, 1.0f, 0.0f})
#define VEC3F_Z ((Vec3f){0.0f, 0.0f, 1.0f})
#define VEC3F_0 ((Vec3f){0.0f, 0.0f, 0.0f})
#define VEC3F_1 ((Vec3f){1.0f, 1.0f, 1.0f})

typedef struct Vec3f {
	float x, y, z;
} Vec3f;

float dot_product(Vec3f a, Vec3f b);
Vec3f vec3f_cross(Vec3f a, Vec3f b);
void print_vec3f(Vec3f v);
Vec3f vec3f_normalize(Vec3f v);
float vec3f_magnitude(Vec3f v);
Vec3f vec3f_add(Vec3f a, Vec3f b);
Vec3f vec3f_scale(Vec3f v, float value);
void convert_vec3f_to_int_values(Vec3f* vertex);
void scale_vector(Vec3f* vec3f, float scalar);
void translate_vector(Vec3f* vec3f, float dx, float dy, float dz);
bool vectors_are_equal(Vec3f a, Vec3f b);

// Vec4f

#define VEC4F_X ((Vec4f){1.0f, 0.0f, 0.0f, 0.0f})
#define VEC4F_Y ((Vec4f){0.0f, 1.0f, 0.0f, 0.0f},)
#define VEC4F_Z ((Vec4f){0.0f, 0.0f, 1.0f, 0.0f})
#define VEC4F_W ((Vec4f){0.0f, 0.0f, 0.0f, 1.0f})
#define VEC4F_0 ((Vec4f){0.0f, 0.0f, 0.0f, 0.0f})
#define VEC4F_1 ((Vec4f){1.0f, 1.0f, 1.0f, 1.0f})

typedef struct  Vec4f {
	float x, y, z, w;
} Vec4f;

float vec4f_dot(Vec4f a, Vec4f b);
Vec4f vec4f_normalize(Vec4f v);
float vec4f_magnitude(Vec4f v);
Vec4f vec4f_add(Vec4f a, Vec4f b);
Vec4f vec4f_scale(Vec4f v, float value);
Vec4f vec4f_translate(Vec4f v, float dx, float dy, float dz, float dw);
bool vec4f_are_equal(Vec4f a, Vec4f b);
void print_vec4f(Vec4f v);
bool vec4f_are_about_equal(Vec4f a, Vec4f b, float allowance); 

typedef struct Vec2f {
	float x, y;
} Vec2f;
#endif
