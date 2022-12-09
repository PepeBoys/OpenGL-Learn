#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include "stb_image.h"

#include <iostream>

#define TEXTURE_JPG 1
#define TEXTURE_PNG 2

class Texture {
public:
	unsigned int texture;

	Texture(const char* path, int type);

	void use();
};

#endif