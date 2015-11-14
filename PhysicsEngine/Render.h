#pragma once
#include "Main.h"
#include "Model.h"
#include "GLFW/glfw3.h"

namespace Render{
	void renderScene();
	void initRender();
	void renderModel(std::string modelName, std::string textureName = "brick", glm::mat4x4 modelMatrix = glm::mat4(1), bool staticLocation = false);
	glm::mat4 createModelMatrix(glm::vec3 translate = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
	glm::mat4 createRotationMatrix(glm::vec3 rotation);
	std::vector<glm::vec3> farClip();
}