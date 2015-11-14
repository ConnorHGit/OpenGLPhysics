#include "Model.h"

using namespace Mod;

std::map<std::string, Model> Mod::models = std::map<std::string, Model>();

void Mod::createModel(GLenum drawType,unsigned int nVerticies, glm::vec3 verticies[],unsigned int nUv,glm::vec2 uvCoords[],std::string modelName){
	unsigned int vao, vbo, vbo2;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * nVerticies, &verticies[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	

	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * nUv, &uvCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	Model createdModel;
	createdModel.vao = vao;
	createdModel.vbos.push_back(vbo);
	createdModel.vbos.push_back(vbo2);
	createdModel.nVerticies = nVerticies;
	createdModel.drawType = drawType;
	
	models[modelName] = createdModel;
}
void Mod::createSquareModel(std::string modelName){
	glm::vec3 verticies[] = {
		glm::vec3(-0.5f, 0.5f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(-0.5f, -0.5f, 0.f)
	};
	glm::vec2 uv[] = {
		glm::vec2(0,1),
		glm::vec2(1,1),
		glm::vec2(1,0),
		glm::vec2(0,0)
	};
	Mod::createModel(GL_QUADS, 4, verticies, 4, uv, modelName);
}
void Mod::createCubeModel(std::string modelName){

	glm::vec3 verticies[] = {
			glm::vec3(-0.5f, 0.5f, 0.5f),//1
			glm::vec3(0.5f, 0.5f, 0.5f),//2
			glm::vec3(0.5f, -0.5f, 0.5f),//3
			glm::vec3(-0.5f, -0.5f, 0.5f),//4
			glm::vec3(0.5f, 0.5f, 0.5f),//2
			glm::vec3(0.5f, 0.5f, -0.5f),//6
			glm::vec3(0.5f, -0.5f, -0.5f),//7
			glm::vec3(0.5f, -0.5f, 0.5f),//3
			glm::vec3(-0.5f, 0.5f, -0.5f),//5
			glm::vec3(0.5f, 0.5f, -0.5f),//6
			glm::vec3(0.5f, -0.5f, -0.5f),//7
			glm::vec3(-0.5f, -0.5f, -0.5f),//8
			glm::vec3(-0.5f, 0.5f, 0.5f),//1
			glm::vec3(-0.5f, 0.5f, -0.5f),//5
			glm::vec3(-0.5f, -0.5f, -0.5f),//8
			glm::vec3(-0.5f, -0.5f, 0.5f),//4
			glm::vec3(-0.5f, 0.5f, 0.5f),//1
			glm::vec3(0.5f, 0.5f, 0.5f),//2
			glm::vec3(0.5f, 0.5f, -0.5f),//6
			glm::vec3(-0.5f, 0.5f, -0.5f),//5
			glm::vec3(-0.5f, -0.5f, 0.5f),//4
			glm::vec3(0.5f, -0.5f, 0.5f),//3
			glm::vec3(0.5f, -0.5f, -0.5f),//7
			glm::vec3(-0.5f, -0.5f, -0.5f),//8
	};

	glm::vec2 uv[] = {
		glm::vec2(0,0),
		glm::vec2(0.3333333333333,0),
		glm::vec2(0.3333333333333,0.5),
		glm::vec2(0,0.5),

		glm::vec2(0.3333333333333, 0),
		glm::vec2(0.6666666666666, 0),
		glm::vec2(0.6666666666666, 0.5),
		glm::vec2(0.3333333333333, 0.5),

		glm::vec2(0.6666666666666, 0),
		glm::vec2(1,0),
		glm::vec2(1,0.5),
		glm::vec2(0.6666666666666, 0.5),

		glm::vec2(0,0.5),
		glm::vec2(0.33333333333, 0.5),
		glm::vec2(0.33333333333, 1),
		glm::vec2(0,1),

		glm::vec2(0.3333333333,0.5),
		glm::vec2(0.666666666, 0.5),
		glm::vec2(0.6666666666, 1),
		glm::vec2(0.3333333333,1),

		glm::vec2(0.6666666666, 0.5),
		glm::vec2(1, 0.5),
		glm::vec2(1,1),
		glm::vec2(0.6666666666666,1)
	};

	Mod::createModel(GL_QUADS, 24, verticies, 24, uv, modelName);
}