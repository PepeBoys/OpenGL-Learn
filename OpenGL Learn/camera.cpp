#include "camera.h"

Camera::Camera(int width, int height) {
	this->window = window;
	this->width = width;
	this->height = height;
}

void Camera::processInput(float deltaTime) {
	float speed = 3.0f;
	glm::vec3 camDeltaPos = glm::vec3(0.f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camDeltaPos += camDir;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camDeltaPos -= camDir;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camDeltaPos += camRight;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camDeltaPos -= camRight;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camDeltaPos += glm::vec3(0.f, 1.f, 0.f);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camDeltaPos -= glm::vec3(0.f, 1.f, 0.f);

	if (camDeltaPos != glm::vec3(0.f))
		camPos += glm::normalize(camDeltaPos) * speed * deltaTime;
}

void Camera::processMouse(double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float sensitivity = 0.05f;

	float xOffset = (xPos - lastX) * sensitivity;
	float yOffset = (lastY - yPos) * sensitivity;
	lastX = xPos;
	lastY = yPos;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch >= 89.f)
		pitch = 89.f;
	else if (pitch <= -89.f)
		pitch = -89.f;

	camDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	camDir.y = sin(glm::radians(pitch));
	camDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camDir = glm::normalize(camDir);
	camRight = glm::cross(camDir, glm::vec3(0.f, 1.f, 0.f));
	camUp = glm::cross(camRight, camDir);
}

glm::mat4 Camera::getView() {
	return glm::lookAt(camPos, camPos + camDir, camUp);
}

void Camera::setProjection(int width, int height) {
	projection = glm::perspective(glm::radians(45.f), (float)width / (float)height, 0.1f, 100.f);
}

void Camera::setWindow(GLFWwindow* window) {
	this->window = window;
}