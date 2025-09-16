#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector.h"
#include "quaternion.h"

typedef struct Transform {
	Vec3f position;  // in world coords
	Quaternion rotation;  
	Vec3f scale;
} Transform;


// Transform 
Transform create_transform(Vec3f rotation, Vec3f position, Vec3f scale);
void transform_set_rotation(Transform* tr, Vec3f new_rotation);
void transform_set_position(Transform* tr, Vec3f new_position);
void transform_set_scale(Transform* tr, Vec3f new_scale);


#endif
