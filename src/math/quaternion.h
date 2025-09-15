#ifndef QUATERNION_H
#define QUATERNION_H
#include <stdbool.h>
#include "matrix.h"

#define QUAT_IDENTITY (struct Quaternion){1.0f, 0.0f, 0.0f, 0.0f}

typedef struct Quaternion {
	float q0; // real
	float q1; // i
	float q2; // j
	float q3; // k
} Quaternion;

Vec3f quat_get_forward(Quaternion q);
Vec3f quat_get_right(Quaternion q);
void print_quat(Quaternion q);
bool quat_are_about_equal(Quaternion q0, Quaternion q1, float epsilon);
Quaternion quat_angle_axis(float angle, Vec3f axis); 
bool quat_are_equal(Quaternion q0, Quaternion q1);
Quaternion quat_mul(Quaternion q0, Quaternion q1);
Quaternion quat_conjugate(Quaternion q);
Quaternion quat_normalize(Quaternion q);
float quat_norm(Quaternion q);
Quaternion quat_inverse(Quaternion q);
Mat4 quat_to_mat4(Quaternion q);
Quaternion euler_to_quat(Vec3f euler_rotation);
#endif

