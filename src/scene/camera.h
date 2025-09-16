#ifndef CAMERA_H
#define CAMERA_H

#include "transform.h"

typedef struct Camera { 
	Transform transform;
	int width, height;
	float fov;
	float near;
	float far;
} Camera;


// Camera
Camera camera_create(Transform tr, float fov, float near, float far);
void camera_set_transform(Camera* cam, Transform tr); 
void camera_set_fov(Camera* cam, float fov);
void camera_set_near(Camera* cam, float near);
void camera_set_far(Camera* cam, float far);


#endif
