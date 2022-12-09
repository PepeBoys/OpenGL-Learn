#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVector4(const std::string& name, float value1, float value2, float value3, float value4) const;
	void setVector3(const std::string& name, float value1, float value2, float value3) const;
	void setMatrix4(const std::string& name, glm::mat4 mat4) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};
#endif