#ifndef TEXTURE_H
#define TEXTURE_H


typedef struct Texture {
	int width;
	int height;
	struct Color* map;
} Texture;

Texture load_texture(char* filename);

void free_texture(Texture tex);
#endif
