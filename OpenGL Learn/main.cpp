#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "camera.h"
#include "object.h"
#include "shader.h"
#include "texture.h"
#include "stb_image.h"

#include <iostream>
#include <vector>

void init();
void killSwitch(std::string error);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void processInput();

GLFWwindow* window;

#define WIDTH 900
#define HEIGHT 600

float deltaTime = 0.f;

bool escapeFirstPress = true;

Camera camera(WIDTH, HEIGHT);


int main() {
	float cubeVertices[] = {
	// Position            // Normal             // Tex Cord
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.25f, 0.36f,
     0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.5f, 0.36f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.5f, 0.65f,
     0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.5f, 0.65f,
    -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.25f, 0.65f,
    -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.25f, 0.36f,
 						   						 
    -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.36f,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.75f, 0.36f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.75f, 0.65f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.75f, 0.65f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.65f,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.36f,
 						   						 
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.65f,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.25f, 0.65f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.25f, 0.36f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.25f, 0.36f,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.36f,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.65f,
 						   						 
     0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.75f, 0.65f,
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.5f, 0.65f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.5f, 0.36f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.5f, 0.36f,
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.75f, 0.36f,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.75f, 0.65f,
 						   						 
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.26f, 0.36f,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.49f, 0.36f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.49f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.49f, 0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.26f, 0.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.26f, 0.36f,
 						   						 
    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.25f, 0.65f,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.5f, 0.65f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.25f, 1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.25f, 0.65f,
	};
	float skyboxVertices[] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
	};
	unsigned int cubeIndices[] = {
		0, 1, 2,
		0, 2, 3,
		
		4, 5, 6,
		4, 6, 7,

		0, 1, 5,
		4, 5, 0,
		
		1, 2, 6,
		5, 6, 1,

		2, 3, 6,
		6, 7, 3,

		0, 3, 4,
		4, 7, 3, 
	};
	glm::vec3 lightPos = glm::vec3(0.f, 3.f, 0.f);

	init();

	camera.setWindow(window);

	Object CubeObj(cubeVertices, sizeof(cubeVertices));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Object SkyBoxObj(skyboxVertices, sizeof(skyboxVertices));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader CubeShaderProgram("../Resources/Shaders/shader.vs", "../Resources/Shaders/shader.fs");
	Shader SkyBoxShaderProgram("../Resources/Shaders/skybox.vs", "../Resources/Shaders/skybox.fs");
	Shader LightShaderProgram("../Resources/Shaders/shader.vs", "../Resources/Shaders/light shader.fs");

	CubeShaderProgram.use();
	CubeShaderProgram.setVector3("objectColor", 1.0f, 0.5f, 0.2f);
	CubeShaderProgram.setVector3("lightColor", 1.0f, 1.0f, 1.0f);

	LightShaderProgram.use();
	LightShaderProgram.setVector4("objectColor", 1.0f, 1.0f, 1.0f, 1.0f);

	// Cube map
	unsigned int cubeMapID;
	glGenTextures(1, &cubeMapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	int width, height, nrChannels;
	unsigned char* data;
	std::vector<std::string> faces = { "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"};
	for (unsigned int i = 0; i < faces.size(); i++) 
	{
		data = stbi_load(("../Resources/Textures/skybox/" + faces[i]).c_str(), &width, &height, &nrChannels, 0);
		if (data) 
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
		}
		else
		{
			std::cout << "Failed to load [Cube Map Texture] ->" << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}




	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		float lastTime = glfwGetTime();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Sky Box
		glDepthMask(GL_FALSE);
		SkyBoxShaderProgram.use();
		SkyBoxShaderProgram.setMatrix4("projection", camera.projection);
		SkyBoxShaderProgram.setMatrix4("view", glm::mat4(glm::mat3(camera.getView())));

		SkyBoxObj.use();
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);

		// Cube
		CubeObj.use();
		CubeShaderProgram.use();

		CubeShaderProgram.setVector3("lightPos", lightPos.x, lightPos.y, lightPos.z);
		CubeShaderProgram.setMatrix4("model", glm::rotate(glm::mat4(1.f), glm::radians((float)glfwGetTime() * 10), glm::vec3(0.f, -1.f, 0.f)));
		CubeShaderProgram.setMatrix4("view", camera.getView());
		CubeShaderProgram.setMatrix4("projection", camera.projection);
		CubeShaderProgram.setVector3("viewPos", camera.camPos.x, camera.camPos.y, camera.camPos.z);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Light
		LightShaderProgram.use();

		float radius = 5.f;
		float camX = sin(glfwGetTime() / 5) * radius;
		float camZ = cos(glfwGetTime() / 5) * radius;
		lightPos = glm::vec3(camX, 5.f, camZ);

		LightShaderProgram.setMatrix4("model", glm::scale(glm::translate(glm::mat4(1.f), lightPos), glm::vec3(0.2f, 0.2f, 0.2f)));
		LightShaderProgram.setMatrix4("view", camera.getView());
		LightShaderProgram.setMatrix4("projection", camera.projection);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwSwapBuffers(window);
		glfwPollEvents();

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		processInput();
	}

	glfwTerminate();
	return 0;
}

void processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && escapeFirstPress) {
		escapeFirstPress = false;
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			camera.firstMouse = true;
		}
		else
			glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		escapeFirstPress = true;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	camera.processInput(deltaTime);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	camera.processMouse(xPos, yPos);
}

void init() {
	if (glfwInit() == GLFW_FALSE) killSwitch("Failed to initialize [GLFW]\n");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle Bitches", nullptr, nullptr);
	if (window == NULL) killSwitch("Failed to create [Window]\n");
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) killSwitch("Failed to initialize [GLAD]");
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	framebufferSizeCallback(window, WIDTH, HEIGHT);
	glfwSetCursorPosCallback(window, mouseCallback);
}

void killSwitch(std::string error) {
	std::cout << error;
	exit(EXIT_FAILURE);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	camera.setProjection(width, height);
}

