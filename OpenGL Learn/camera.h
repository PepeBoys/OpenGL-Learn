#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class Camera {
public:
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)width / (float)height, 0.1f, 100.f);
	glm::vec3 camPos = glm::vec3(0.f, 0.f, 10.f);
	bool firstMouse = true;

	Camera(int width, int height);

	void processInput(float deltaTime);

	void processMouse(double xPos, double yPos);

	glm::mat4 getView();
	
	void setProjection(int width, int height);

	void setWindow(GLFWwindow* window);

private:
	GLFWwindow* window;

	int width, height;
	float lastX = width / 2, lastY = height / 2;
	float yaw = 270.f, pitch = 0.f;

	
	glm::vec3 camTarget = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 camDir = glm::normalize(camTarget - camPos);
	glm::vec3 camRight = glm::cross(camDir, glm::vec3(0.f, 1.f, 0.f));
	glm::vec3 camUp = glm::cross(camRight, camDir);

};

#endif