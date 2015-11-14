#include "Render.h"
#include <stdio.h>
#include "Terrain.h"
#define GLM_FORCE_RADIANS

//glm::mat4 globalMatrix;
glm::mat4 projectionMatrix = glm::perspective<float>(1.52f, 16.f / 9.f, 0.1f, 10000.f);
glm::mat4 viewMatrix;
void Render::renderScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.25882352941176470588235294117647, 0.38431372549019607843137254901961, 1.0, 1.0);
	glUseProgram(Main::program);
	viewMatrix = glm::translate(Player::playerView.rotationMatrix, glm::vec3 (Player::playerView.position.x, Player::playerView.position.y * -1, Player::playerView.position.z));
	Main::bodyManager.renderCubes();
	
	Terrain::renderTerrain(projectionMatrix * viewMatrix);
	glfwSwapBuffers(GW::window);

}

void Render::renderModel(std::string modelName, std::string textureName, glm::mat4x4 modelMatrix, bool staticLocation) {
	Mod::Model m = Mod::models[modelName];
	glBindVertexArray(Mod::models[modelName].vao);
	glBindTexture(GL_TEXTURE_2D,Texture::textures[textureName]);
	glUniformMatrix4fv(glGetUniformLocation(Main::program, "matrix"), 1, false, &((projectionMatrix * (staticLocation ? modelMatrix : viewMatrix * modelMatrix))[0][0]));
	glDrawArrays(m.drawType, 0, m.nVerticies);
}

glm::mat4 Render::createModelMatrix(glm::vec3 translate, glm::vec3 rotation, glm::vec3 scale){
	return glm::scale(glm::translate(glm::mat4(1), translate) * glm::rotate(glm::rotate(glm::rotate(glm::mat4(1), rotation.x, glm::vec3(1, 0, 0)), rotation.y, glm::vec3(0, 1, 0)), rotation.z, glm::vec3(0, 0, 1)) , scale);
	
}
glm::mat4 Render::createRotationMatrix(glm::vec3 rotation){
	return glm::rotate(glm::rotate(glm::rotate(glm::mat4(1), rotation.x, glm::vec3(1, 0, 0)), rotation.y, glm::vec3(0, 1, 0)), rotation.z, glm::vec3(0, 0, 1));
}