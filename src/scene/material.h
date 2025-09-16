#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct Material {
	Vec3f color; // fallback color if no texture
	Texture *albedo; // for base color
} Material;


Material create_material();
#endif
