#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>

class Object {
public:
	unsigned int VBO, VAO;

	Object(float* vertices, unsigned int sizeofVertices);

	void changeVBO(float* vertices, unsigned int sizeofVertices);

	void use();
};

#endif